/**
 * @file driver_i2c.c
 * @brief AM2320 temperature and humidity sensor driver over I2C with DMA support.
 * @author AGH EKO-ENERGIA
 * @author Karol
 */

#include "my_driver_i2c.h"
#include "main.h"
#include "my_driver_can.h"
#include <string.h>
#include <stdbool.h>

/* ================= EXTERNAL ================= */

extern I2C_HandleTypeDef hi2c1;
extern struct CAN_scheduledMsgList canBufferTx;

/* ================= STATE ================= */

static AM2320_state_e am2320State;
static int16_t am2320TempX10 = 0;
static uint16_t am2320RhX10 = 0;

/* ================= FRAMES ================= */

static struct I2C_frame am2320WakeUp;
static struct I2C_frame am2320Measure;
static struct I2C_frame am2320Read;

/* ================= PRIVATE FUNCTION DECLARATIONS ================= */

static void AM2320_PrepareData(void);

static bool AM2320_IsTime(const struct I2C_frame* frame);

static void AM2320_FetchTempRh(uint8_t* const data);

static HAL_StatusTypeDef I2C_TransmitMessage(struct I2C_frame* Tx_frame);

static HAL_StatusTypeDef I2C_ReceiveMessage(struct I2C_frame* const Rx_frame);


/* ================= CALLBACK ================= */

/**
 * @brief HAL callback triggered when I2C DMA reception completes.
 *
 * Parses the received raw bytes and schedules a CAN update.
 * Only handles I2C1 — returns early for any other instance.
 *
 * @param hi2c  pointer to the I2C handle that triggered the callback
 */
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    if (hi2c->Instance != I2C1)
    {
        return;
    }

    AM2320_PrepareData();
    am2320State = AM2320_UPDATE_CAN;
}

/**
 * @brief HAL callback triggered when I2C DMA transmission completes.
 *
 * @param hi2c  pointer to the I2C handle that triggered the callback
 */
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    return;
}

/* ================= API ================= */

/**
 * @brief Initializes the AM2320 sensor frames and sets the state machine to IDLE.
 *
 * Prepares three I2C frames: wake-up (empty write), measure command (0x03 0x00 0x04),
 * and read (8-byte receive buffer).
 */
void AM2320_Init(void)
{
    am2320State = AM2320_IDLE;

    uint8_t measureCmd[3] = {0x03, 0x00, 0x04};
    uint8_t empty[1] = {0};

    am2320WakeUp.hi2c = &hi2c1;
    am2320WakeUp.address = 0xB8;
    am2320WakeUp.sizeData = 0;
    am2320WakeUp.delayMs = 3;
    memcpy(am2320WakeUp.data, empty, 1);

    am2320Measure.hi2c = &hi2c1;
    am2320Measure.address = 0xB8;
    am2320Measure.sizeData = 3;
    am2320Measure.delayMs = 3;
    memcpy(am2320Measure.data, measureCmd, 3);

    am2320Read.hi2c = &hi2c1;
    am2320Read.address = 0xB8;
    am2320Read.sizeData = 8;
    am2320Read.delayMs = 2;
}

/**
 * @brief Returns the current state of the AM2320 state machine.
 *
 * @retval Current AM2320_state_e value
 */
AM2320_state_e AM2320_GetState(void)
{
    return am2320State;
}

/**
 * @brief Requests a new measurement if the sensor is idle and I2C is ready.
 *
 * Does nothing if a measurement is already in progress.
 */
void AM2320_StartMeasure(void)
{
    if (am2320State == AM2320_IDLE &&
        HAL_I2C_GetState(&hi2c1) == HAL_I2C_STATE_READY)
    {
        am2320State = AM2320_START;
    }
}

/**
 * @brief Returns the last measured temperature and humidity.
 *
 * Values are scaled by 10 (e.g. 253 means 25.3).
 *
 * @param tempX10   pointer to store temperature * 10 (signed, degrees Celsius)
 * @param humX10    pointer to store relative humidity * 10 (unsigned, percent)
 */
void AM2320_GetTempHum(int16_t* tempX10, uint16_t* humX10)
{
    *tempX10 = am2320TempX10;
    *humX10 = am2320RhX10;
}

/**
 * @brief Advances the AM2320 state machine. Should be called periodically from the main loop.
 *
 * Drives the full measurement sequence: wake-up → measure command → data read → CAN update.
 */
void AM2320_StateMachine(void)
{
    switch (am2320State)
    {
        case AM2320_START:
            I2C_TransmitMessage(&am2320WakeUp);
            am2320State = AM2320_DMA_END;
            break;

        case AM2320_DMA_END:
        	if(HAL_I2C_GetState(&hi2c1) == HAL_I2C_STATE_READY)
        	{
        		am2320WakeUp.lastTick = HAL_GetTick();
        		am2320State = AM2320_WAKE_UP;
        	}
        	break;

        case AM2320_WAKE_UP:
            if (AM2320_IsTime(&am2320WakeUp))
            {
                I2C_TransmitMessage(&am2320Measure);
                am2320State = AM2320_MEASURE;
            }
            break;

        case AM2320_MEASURE:
            if (HAL_I2C_GetState(&hi2c1) == HAL_I2C_STATE_READY)
            {
                am2320Measure.lastTick = HAL_GetTick();
                am2320State = AM2320_DATA_READY;
            }
            break;

        case AM2320_DATA_READY:
            if (AM2320_IsTime(&am2320Measure))
            {
                am2320Read.lastTick = HAL_GetTick();
                I2C_ReceiveMessage(&am2320Read);
            }
            break;

        case AM2320_UPDATE_CAN:
        	CAN_RemoveScheduledMsg(AM2320_CAN_ID_SENSOR, &canBufferTx);             /* Remove stale entry before re-adding with fresh data */

        	CAN_WriteFrame(&canBufferTx,
            				AM2320_CAN_ID_SENSOR,
                            AM2320_TEMP_RH_BYTES,
                            AM2320_FetchTempRh,
                            AM2320_MEASURE_PERIOD_MS);

            am2320State = AM2320_IDLE;
            break;
    }
}

/* ================= PRIVATE ================= */

/**
 * @brief Parses raw DMA receive buffer into temperature and humidity values.
 *
 * AM2320 response layout (bytes 2-5 of 8-byte frame):
 * - byte 2-3: raw temperature (MSB first, bit 15 = sign)
 * - byte 4-5: raw humidity (MSB first)
 */
static void AM2320_PrepareData(void)
{
    uint8_t* data = am2320Read.data;

    am2320RhX10 = (uint16_t)(data[2] << 8 | data[3]);

    uint16_t rawTemp = (uint16_t)(data[4] << 8 | data[5]);

    if (rawTemp & 0x8000)
    {
        rawTemp &= 0x7FFF;
        am2320TempX10 = -(int16_t)rawTemp;
    }
    else
    {
        am2320TempX10 = (int16_t)rawTemp;
    }
}

/**
 * @brief Checks whether the required delay for an I2C frame has elapsed.
 *
 * @param frame     pointer to the frame whose delayMs and lastTick are checked
 * @retval true if enough time has passed, false otherwise
 */
static bool AM2320_IsTime(const struct I2C_frame* frame)
{
    return (HAL_GetTick() - frame->lastTick) >= frame->delayMs;
}

/**
 * @brief CAN data-fetching callback that packs temperature and humidity into a 4-byte payload.
 *
 * Byte layout: [tempHigh, tempLow, humHigh, humLow]
 *
 * @param data  pointer to the 4-byte output buffer
 */
static void AM2320_FetchTempRh(uint8_t* const data)
{
    data[0] = (uint8_t)(am2320TempX10 >> 8);
    data[1] = (uint8_t)(am2320TempX10);

    data[2] = (uint8_t)(am2320RhX10 >> 8);
    data[3] = (uint8_t)(am2320RhX10);
}

/* ================= I2C LOW LEVEL ================= */

/**
 * @brief Transmits an I2C frame via DMA.
 *
 * Returns HAL_ERROR immediately if the address is 7-bit (≤ 0x7F),
 * since the AM2320 uses an 8-bit address.
 *
 * @param frame     pointer to the I2C frame to transmit
 * @retval HAL_StatusTypeDef result of the DMA transmit call
 */
static HAL_StatusTypeDef I2C_TransmitMessage(struct I2C_frame* frame)
{
    if (frame->address <= 0x7F)
    {
        return HAL_ERROR;
    }

    return HAL_I2C_Master_Transmit_DMA(
        frame->hi2c,
        frame->address,
        frame->data,
        frame->sizeData
    );
}

/**
 * @brief Receives data into an I2C frame buffer via DMA.
 *
 * Returns HAL_ERROR immediately if the address is 7-bit (≤ 0x7F),
 * since the AM2320 uses an 8-bit address.
 *
 * @param frame     pointer to the I2C frame whose buffer will be filled
 * @retval HAL_StatusTypeDef result of the DMA receive call
 */
static HAL_StatusTypeDef I2C_ReceiveMessage(struct I2C_frame* frame)
{
    if (frame->address <= 0x7F)
    {
        return HAL_ERROR;
    }

    return HAL_I2C_Master_Receive_DMA(
        frame->hi2c,
        frame->address,
        frame->data,
        frame->sizeData
    );
}
