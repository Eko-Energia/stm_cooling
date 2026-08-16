/**
 * @file MY_driver_fan.c
 * @brief Driver for controlling cooling fans via PWM timer channels and CAN bus reporting.
 * @author AGH EKO-ENERGIA
 * @author Karol
 */

#include "MY_driver_fan.h"
#include "MY_driver_can.h"
#include "MY_driver_i2c.h"
/* ================= PRIVATE VARIABLE ================= */

static uint8_t fanStateLeft= 0;
static uint8_t fanStateRight = 0;
static uint16_t tempLeft = 0;     // left
static uint16_t tempRight = 0;     //right


/* ================= API ================= */

/**
 * @brief Switches individual fans or both fans on or off via GPIO.
 *
 * @param setter    Desired fan state from fan_state_e.
 */
void FAN_SetOnOff(fan_state_e setter)
{
	switch (setter)
	{
	case FAN_ON_LEFT:
		HAL_GPIO_WritePin(FAN1_ON_GPIO_Port, FAN1_ON_Pin, GPIO_PIN_SET);
		break;

	case FAN_OFF_LEFT:
		HAL_GPIO_WritePin(FAN1_ON_GPIO_Port, FAN1_ON_Pin, GPIO_PIN_RESET);
		break;

	case FAN_ON_RIGHT:
		HAL_GPIO_WritePin(FAN2_ON_GPIO_Port, FAN2_ON_Pin, GPIO_PIN_SET);
		break;

	case FAN_OFF_RIGHT:
		HAL_GPIO_WritePin(FAN2_ON_GPIO_Port, FAN2_ON_Pin, GPIO_PIN_RESET);
		break;
	}
}

/**
 * @brief Populates the CAN data buffer with the current pulse values of both fans.
 *
 * @param data  Pointer to a byte array of at least 2 bytes; filled with fan 1 and fan 2 pulse values.
 */
void FAN_FetcherPulse(uint8_t *data)
{
	data[0] = fanStateLeft;
	data[1] = fanStateRight;
}


void FAN_GetTempEngineLeft(uint8_t* data)
{
	tempLeft = (uint16_t)(data[0]| (data[1] << 8 )) * 0.1;
}


void FAN_GetTempEngineRight(uint8_t* data)
{
	tempRight = (uint16_t)(data[0]| (data[1] << 8)) * 0.1;
}


void FAN_EngineController()
{

	if(tempLeft < 50)
	{
		fanStateLeft = 0;
		FAN_SetOnOff(FAN_OFF_LEFT);
	}
	else if(tempLeft > 60)
	{
		fanStateLeft = 100;
		FAN_SetOnOff(FAN_ON_LEFT);
	}

	if(tempRight < 50)
	{
		fanStateRight = 0;
		FAN_SetOnOff(FAN_OFF_RIGHT);
	}
	else if(tempRight > 60)
	{
		fanStateRight = 100;
		FAN_SetOnOff(FAN_ON_RIGHT);
	}
}


// CHANGE IT BELOW:

/**
 * @brief Applies current fan pulse values to the PWM timer channels and schedules a CAN status frame.
 *
 * Removes any previously scheduled CAN message for the left cooling fan, applies the
 * stored @ref fan1Pulse and @ref fan2Pulse values to TIM_CHANNEL_1 and TIM_CHANNEL_2,
 * then re-registers a periodic CAN frame reporting both pulse values.
 *
 * @param htim          Pointer to the timer handle controlling the fan PWM output.
 * @param CAN_Buffer_TX Pointer to the CAN scheduled message list used for TX.
 */
void FAN_SetPulseInternal(TIM_HandleTypeDef *htim, struct CAN_scheduledMsgList *CAN_Buffer_TX)
{
	CAN_RemoveScheduledMsg(ID_COOLING_FAN, CAN_Buffer_TX);

	CAN_WriteFrame(CAN_Buffer_TX, ID_COOLING_FAN, BYTE_SIZE_PULSE, FAN_FetcherPulse, PERIOD_PULSE_SEND);
}

