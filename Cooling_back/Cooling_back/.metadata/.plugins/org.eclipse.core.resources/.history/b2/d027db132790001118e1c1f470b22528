/**
 * @file MY_driver_fan.h
 * @brief Driver for controlling cooling fans via PWM timer channels and CAN bus reporting.
 * @author AGH EKO-ENERGIA
 * @author Karol
 */

#ifndef INC_MY_LIB_MY_DRIVER_FAN_H_
#define INC_MY_LIB_MY_DRIVER_FAN_H_

#include "MY_driver_can.h"
#include "can_driver.h"
#include "main.h"
#include "stdbool.h"
#include "MY_driver_can.h"

/* CAN transmission period for fan pulse feedback [ms] */
#define PERIOD_PULSE_SEND       (100)

/* Number of bytes in the fan pulse CAN frame payload */
#define BYTE_SIZE_PULSE         (2)

/* CAN ID for the left cooling fan (0x502) */
#define ID_COOLING_LEFT_FAN     (1249)

#define NUMBER_OF_PACKET (9)

#define TEMP_FACTOR 	(0.39216)

#define TEMP_OFFSET 	(49.8039)


#define TEMP_REF        (50)

#define DT				(500) // ms

#define DUTY_STABLE		(0.8133)

#define K				(0.2589)

#define I				(0.0086)


typedef enum
{
    FAN_ON_1,
    FAN_OFF_1,
    FAN_ON_2,
    FAN_OFF_2,
    FAN_ON_BOTH,
    FAN_OFF_BOTH,
} fan_state_e;

/* ================= API ================= */

/**
 * @brief Populates the CAN data buffer with the current pulse values of both fans.
 *
 * @param data  Pointer to a byte array of at least 2 bytes; filled with fan 1 and fan 2 pulse values.
 */
void FAN_FetcherPulse(uint8_t *data);

/**
 * @brief Sets PWM pulse widths for both fan channels and schedules a CAN status frame.
 *
 * Removes any previously scheduled CAN message for the left cooling fan, updates the
 * internal pulse state, applies the new compare values to TIM_CHANNEL_1 and TIM_CHANNEL_2,
 * then re-registers a periodic CAN frame.
 *
 * @param htim          Pointer to the timer handle controlling the fan PWM output.
 * @param CAN_Buffer_TX Pointer to the CAN scheduled message list used for TX.
 * @param pulse_ch1     Desired pulse value for fan 1 (TIM_CHANNEL_1), range 0–100.
 * @param pulse_ch2     Desired pulse value for fan 2 (TIM_CHANNEL_2), range 0–100.
 */
void FAN_SetPulseExternCabin(uint8_t* pulseTable);

/**
 * @brief Switches individual fans or both fans on or off via GPIO.
 *
 * @param setter    Desired fan state from fan_state_e.
 */
void FAN_SetOnOff(fan_state_e setter);

/**
 * @brief Resets the pulse values of both fans to zero.
 */
void FAN_PulseReset();

/**
 * @brief Updates the battery temperature packet buffer and recalculates the maximum battery temperature.
 *
 * Stores the incoming CAN frame's converted temperature value at the index given by
 * frame->name, then scans the whole packet buffer to find and store the highest
 * temperature value in the global batteryMaxTemp.
 *
 * @param frame  Pointer to the received CAN buffer frame containing the raw temperature data.
 */
void FAN_SetMaxTemp(struct CAN_bufferFrame *frame);		// wybiera z ramki temperatury największą wartość i zapisuje


/**
 * @brief Regulates fan 1 PWM duty cycle based on the current battery temperature.
 *
 * Runs periodically (every DT ms). Duty cycle scales linearly with batteryMaxTemp
 * above 30°C, is forced to 0 below 30°C, and is clamped to a maximum of 100.
 */
void FAN_BatteryController();	// steruje wentylatorem do baterii jako pomiar temperatura uzyskana przez FAN_Set_MaxTemp()


/**
 * @brief Regulates fan 2 PWM duty cycle based on the cabin temperature read from the AM2320 sensor.
 *
 * Runs periodically (every DT ms). Reads temperature and humidity from the AM2320 sensor,
 * then scales the duty cycle linearly with temperature above 20.0°C, forces it to 0 below
 * that threshold, and clamps it to a maximum of 100.
 */
void FAN_CabinController();     // Będzie podawał wypełenie z ramki która przyjdzie

/**
 * @brief Applies current fan pulse values to the PWM timer channels and schedules a CAN status frame.
 *
 * Removes any previously scheduled CAN message for the left cooling fan, applies the
 * stored fan 1 and fan 2 pulse values to TIM_CHANNEL_1 and TIM_CHANNEL_2, then
 * re-registers a periodic CAN frame reporting both pulse values.
 *
 * @param htim          Pointer to the timer handle controlling the fan PWM output.
 * @param CAN_Buffer_TX Pointer to the CAN scheduled message list used for TX.
 */
void FAN_SetPulseInternal(TIM_HandleTypeDef *htim, struct CAN_scheduledMsgList *CAN_Buffer_TX);


#endif /* INC_MY_LIB_MY_DRIVER_FAN_H_ */
