/**
 * @file driver_can.c
 * @brief CAN driver for receiving and transmitting CAN frames using a FIFO buffer and scheduled messages.
 * @author AGH EKO-ENERGIA
 * @author Karol
 */

#include "MY_driver_can.h"
#include "can_driver.h"
#include "main.h"


/* ================= EXTERNAL ================= */
extern CAN_HandleTypeDef hcan;


/* ================= BUFFERS ================= */
volatile struct CAN_fifoBuffer canBufferRx = {0};
struct CAN_scheduledMsgList canBufferTx = {0};


/* ================= PRIVATE FUNCTION DECLARATIONS ================= */
static CAN_frameType_e MapIdToFrameEnum(uint16_t id);


/* ================= CALLBACK ================= */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
	CAN_ReadFrame(hcan);
}


/* ================= API ================= */
bool IsEmpty(volatile struct CAN_fifoBuffer *self)
{
	if (self->readIndex == self->writeIndex)
	{
		return true; 	/* Buffer empty */
	}
	return false;
}


/**
 * @brief Writes a frame to the FIFO buffer.
 *
 * @param self      pointer to the FIFO buffer instance
 * @param frame     pointer to the frame to write
 * @retval HAL_OK if write was successful, HAL_ERROR if buffer is full
 */
HAL_StatusTypeDef CAN_WriteData(volatile struct CAN_fifoBuffer *self, struct CAN_bufferFrame *frame)
{
	uint8_t nextIndex = (self->writeIndex + 1) % CAN_BUFFER_SIZE;

	if (self->readIndex == nextIndex)
	{
		return HAL_ERROR; /* Buffer full */
	}

	self->tableBuff[self->writeIndex] = *frame;
	self->writeIndex = nextIndex;

	return HAL_OK;
}

/**
 * @brief Reads a frame from the FIFO buffer.
 *
 * @param self      pointer to the FIFO buffer instance
 * @param frame     pointer to the frame to read into
 * @retval HAL_OK if read was successful, HAL_ERROR if buffer is empty
 */
HAL_StatusTypeDef CAN_ReadData(volatile struct CAN_fifoBuffer *self, struct CAN_bufferFrame *frame)
{
	if (IsEmpty(self))
	{
		return HAL_ERROR; /* Buffer empty */
	}

	*frame = self->tableBuff[self->readIndex];
	self->readIndex = (self->readIndex + 1) % CAN_BUFFER_SIZE;

	return HAL_OK;
}

/**
 * @brief Reads an incoming CAN frame from hardware FIFO and writes it to the RX software buffer.
 *
 * If the RX buffer is full the incoming frame is silently dropped.
 * TODO: consider overwriting the oldest entry instead of dropping.
 *
 * @param hcan  pointer to the CAN peripheral handle
 */
void CAN_ReadFrame(CAN_HandleTypeDef *hcan)
{
	CAN_RxHeaderTypeDef rxHeader;
	struct CAN_bufferFrame msg = {0};

	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rxHeader, msg.data) != HAL_OK)
	{
		/* TODO: error handler */
		return;
	}

	msg.name = MapIdToFrameEnum(rxHeader.StdId);
	CAN_WriteData(&canBufferRx, &msg);
}

/**
 * @brief Adds a new periodic CAN message to the TX scheduled message list.
 *
 * @param canBufferTx   pointer to the scheduled message list
 * @param id            standard CAN ID of the message
 * @param size          data length code (DLC)
 * @param fetcher       function pointer to the data-fetching callback
 * @param period        transmission period in milliseconds
 */
void CAN_WriteFrame(struct CAN_scheduledMsgList *canBufferTx, uint16_t id, uint8_t size, void *fetcher, uint32_t period)
{
	struct CAN_scheduledMsg msg;

	msg.header.IDE   = CAN_ID_STD;
	msg.header.StdId = id;
	msg.header.RTR   = CAN_RTR_DATA;
	msg.header.DLC   = size;
	msg.header.ExtId = 0x00;

	msg.periodMs = period;
	msg.getData  = fetcher;
	msg.lastTick = 0;
	msg.context  = NULL;

	if (CAN_AddScheduledMsg(&msg, canBufferTx) != HAL_OK)
	{
		/* TODO: error handler */
	}
}

/**
 * @brief Example data-fetching callback that fills a CAN frame with incremental bytes.
 *
 * @param data      pointer to the data buffer to fill (8 bytes)
 * @param context   unused context pointer
 */
void CAN_ExampleFetchingFrame(uint8_t *data, void *context)
{
	for (uint8_t i = 0; i < CAN_DATA_SIZE; ++i)
	{
		data[i] = i;
	}
}


/* ================= PRIVATE ================= */

/**
 * @brief Maps a CAN standard ID to a known frame type enum.
 *
 * @param id    standard CAN ID to map
 * @retval corresponding CAN_frameType_e value
 */
static CAN_frameType_e MapIdToFrameEnum(uint16_t id)
{
	switch (id)
	{
	case 0x83: return CAN_FRAME_BMS_TEMP_1;
	case 0x84: return CAN_FRAME_BMS_TEMP_2;
	case 0x85: return CAN_FRAME_BMS_TEMP_3;
	case 0x86: return CAN_FRAME_BMS_TEMP_4;
	case 0x87: return CAN_FRAME_BMS_TEMP_5;
	case 0x88: return CAN_FRAME_BMS_TEMP_6;
	case 0x89: return CAN_FRAME_BMS_TEMP_7;
	case 0x8A: return CAN_FRAME_BMS_TEMP_8;
	case 0x8B: return CAN_FRAME_BMS_TEMP_9;
	case 0xFF: return CAN_FRAME_CABIN_SET_FAN;
	case 0xFFF: return CAN_FRAME_CABIN_SET_SERVO;
	case 0xFFFF: return CAN_FRAME_SAFE_STATE;
	case 0xFFFFF: return CAN_FRAME_BATTERY_SET_FAN;
	case 0xFFFFF: return CAN_FRAME_BATTERY_SET_SERVO;
	}
}
