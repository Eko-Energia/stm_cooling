/**
 * @file driver_i2c.h
 * @brief AM2320 temperature and humidity sensor driver over I2C with DMA support.
 * @author AGH EKO-ENERGIA
 * @author Karol
 */

#ifndef INC_MY_LIB_MY_DRIVER_I2C_H_
#define INC_MY_LIB_MY_DRIVER_I2C_H_

#include "main.h"
#include <stdbool.h>
#include <stdint.h>

/* ================= CONFIG ================= */

#define MAX_FRAME_LENGTH (32)
#define AM2320_CAN_ID_SENSOR (1313)
#define AM2320_TEMP_RH_BYTES (4)
#define AM2320_MEASURE_PERIOD_MS (500)

/* ================= STATE MACHINE ================= */

typedef enum
{
    AM2320_IDLE,
    AM2320_START,
    AM2320_DMA_END,
    AM2320_WAKE_UP,
    AM2320_MEASURE,
    AM2320_DATA_READY,
    AM2320_UPDATE_CAN
} AM2320_state_e;

/* ================= FRAME STRUCT ================= */

struct I2C_frame
{
    I2C_HandleTypeDef* hi2c;
    uint16_t address;
    uint8_t data[MAX_FRAME_LENGTH];
    uint8_t sizeData;
    uint32_t lastTick;
    uint8_t delayMs;
};

/* ================= PUBLIC API ================= */

/**
 * @brief Initializes the AM2320 sensor frames and sets the state machine to IDLE.
 */
void AM2320_Init(void);

/**
 * @brief Advances the AM2320 state machine. Should be called periodically from the main loop.
 */
void AM2320_StateMachine(void);

/**
 * @brief Returns the current state of the AM2320 state machine.
 *
 * @retval Current AM2320_state_e value
 */
AM2320_state_e AM2320_GetState(void);

/**
 * @brief Requests a new measurement if the sensor is idle and I2C is ready.
 */
void AM2320_StartMeasure(void);

/**
 * @brief Returns the last measured temperature and humidity.
 *
 * Values are scaled by 10 (e.g. 253 means 25.3).
 *
 * @param tempX10   pointer to store temperature * 10 (signed, degrees Celsius)
 * @param humX10    pointer to store relative humidity * 10 (unsigned, percent)
 */
void AM2320_GetTempHum(int16_t* tempX10, uint16_t* humX10);

#endif /* INC_MY_LIB_MY_DRIVER_I2C_H_ */
