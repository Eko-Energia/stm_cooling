/*
 * cooler_left_app.c
 *
 *  Created on: 8 kwi 2026
 *      Author: Karol
 */
# include "main.h"
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

/* ================= PRIVATE VARIABLE ================= */
static struct CAN_bufferFrame msg = {0};

extern volatile struct CAN_fifoBuffer canBufferRx;
extern struct CAN_scheduledMsgList canBufferTx;

/* ================= CALLBACK ================= */

/**
 * @brief HAL timer period-elapsed callback, dispatched for TIM6 and TIM7.
 *
 * On TIM7: toggles the red status LED and triggers handling of any scheduled
 * CAN messages that are due for transmission.
 * On TIM6: starts a new AM2320 temperature/humidity measurement cycle.
 *
 * @param htim  Pointer to the timer handle that triggered the callback.
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM7)
	{
		//HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		CAN_HandleScheduled(&hcan, &canBufferTx);  // CHANGE IT; USE FLAG INSTEAD CALL
	}
}

/* ================= HELPER FUNCTION ================= */

/**
 * @brief Periodically applies the current fan and servo pulse values to their PWM timers.
 *
 * Runs at most once every 500 ms; when due, pushes the internally stored fan
 * pulses to TIM2 and servo pulses to TIM3 (also scheduling their CAN status frames).
 */
void COOLER_refresh_pulse()
{
	static uint16_t lastTick = 0;

	if(HAL_GetTick() - lastTick  > 500)
	{
		lastTick = HAL_GetTick();
		FAN_SetPulseInternal(&htim2, &canBufferTx);
	}

}


/**
 * @brief Initializes all peripherals used by the cooler application.
 *
 * Sets up the CAN driver and its RX ring buffer, starts the periodic TIM6/TIM7
 * interrupt timers, initializes the AM2320 sensor over I2C, and starts the PWM
 * channels used for the servos (TIM3) and fans (TIM2).
 */
void Init_Cooler()
{
	  // 			INIT CAN
	  CAN_Init(&hcan);
	  canBufferRx.readIndex = 0;
	  canBufferRx.writeIndex = 0;
	  canBufferRx.ReadData = CAN_ReadData;
	  canBufferRx.WriteData = CAN_WriteData;
	  canBufferRx.IsEmpty = IsEmpty;
	  HAL_TIM_Base_Start_IT(&htim7);

	  // 			INIT FAN
	  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);

}
/* ================= DEBUG VAR ================ */


/* ================= MAIN APP ================= */

/**
 * @brief Main application entry point / superloop for the left cooler controller.
 *
 * Initializes the cooler hardware, turns both fans.
 * then continuously: processes any incoming CAN frames
 * (battery temperature packets update the max-temperature and battery fan control;
 * other frames update externally-commanded fan pulses), and periodically
 * refreshes the PWM outputs and CAN status frames.
 */
void COOLER_app()
{
  Init_Cooler();
  FAN_SetOnOff(FAN_ON_BOTH);

  while (1)
  {
	  // STATE: DRIVING / CHARGING

	  if(!canBufferRx.IsEmpty(&canBufferRx))
	  {
		  canBufferRx.ReadData(&canBufferRx, &msg);

		  if((CAN_FRAME_BMS_TEMP_1 <= msg.name) && (msg.name <= CAN_FRAME_BMS_TEMP_9))
		  {
			  FAN_SetMaxTemp(&msg);
			  FAN_BatteryController();
		  }
	  }
	  COOLER_refresh_pulse();
  }
}
