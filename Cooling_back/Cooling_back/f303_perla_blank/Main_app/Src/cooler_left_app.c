/*
 * cooler_left_app.c
 *
 *  Created on: 8 kwi 2026
 *      Author: Karol
 */
# include "main.h"
# include "cooler_left_app.h"
# include "can_driver.h"
# include "MY_driver_can.h"
# include "MY_driver_serwo.h"
# include "MY_driver_fan.h"
# include "MY_driver_i2c.h"

/* ================= EXTERNAL ================= */

extern CAN_HandleTypeDef hcan;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern I2C_HandleTypeDef hi2c1;
extern struct CAN_scheduledMsgList canBufferTx;

/* ================= PRIVATE VARIABLE ================= */
static struct CAN_bufferFrame msg = {0};
volatile uint8_t interuptCanFlag = CAN_WAIT_TO_SEND_MSG;
/* ================= CALLBACK ================= */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM7)
	{
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		interuptCanFlag = CAN_TIME_TO_SEND_MSG;
	}
	else if(htim->Instance == TIM6)
	{
		AM2320_StartMeasure();

	}
}

/* ================= HELPER FUNCTION ================= */

void COOLER_refresh_pulse()
{
	static uint32_t lastTick = 0;
	uint32_t ticks = HAL_GetTick();
	if(ticks - lastTick  > 500)
	{
		lastTick = HAL_GetTick();
		FAN_SetPulseInternal(&htim2, &canBufferTx);
	}
}


void COOLER_IsTimeSendMsg(volatile uint8_t* interuptCanFlag)
{
	if(*interuptCanFlag == CAN_TIME_TO_SEND_MSG)
	{
		*interuptCanFlag = CAN_WAIT_TO_SEND_MSG;
		CAN_HandleScheduled(&hcan, &canBufferTx);
	}
}


void Init_Cooler()
{
	  // 			INIT CAN
	  CAN_Init(&hcan);
	  HAL_TIM_Base_Start_IT(&htim7);
	  HAL_TIM_Base_Start_IT(&htim6);


	  // 			INIT AM2320 - I2C
	  AM2320_Init();

	  // 			INIT SERWO
	  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

	  // 			INIT FAN
	  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);

}
/* ================= DEBUG VAR ================ */


/* ================= MAIN APP ================= */

void COOLER_app()
{
  Init_Cooler();
  FAN_SetOnOff(FAN_ON_BOTH);

  while (1)
  {
	  // STATE: DRIVING / CHARGING
	  COOLER_IsTimeSendMsg(&interuptCanFlag);

	  if(CAN_GetFrame(&msg) == HAL_OK)
	  {
		  if((CAN_FRAME_BMS_TEMP_1 <= msg.name) && (msg.name <= CAN_FRAME_BMS_TEMP_9))
		  {
			  FAN_SetMaxTemp(&msg);
			  FAN_BatteryController();
		  }
	  }
	  COOLER_refresh_pulse();
  }
}
