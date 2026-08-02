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
#define ID_COOLING_FAN     (1346)

typedef enum
{
    FAN_ON_LEFT,
    FAN_OFF_LEFT,
    FAN_ON_RIGHT,
    FAN_OFF_RIGHT,
} fan_state_e;

/* ================= API ================= */



void FAN_GetTempEngineLeft(uint8_t* data);


void FAN_GetTempEngineRight(uint8_t* data);
/**
 * @brief Populates the CAN data buffer with the current pulse values of both fans.
 *
 * @param data  Pointer to a byte array of at least 2 bytes; filled with fan 1 and fan 2 pulse values.
 */
void FAN_FetcherPulse(uint8_t *data);


/**
 * @brief Switches individual fans or both fans on or off via GPIO.
 *
 * @param setter    Desired fan state from fan_state_e.
 */
void FAN_SetOnOff(fan_state_e setter);


/**
 * @brief Regulates fan 2 PWM duty cycle based on the cabin temperature read from the AM2320 sensor.
 *
 * Runs periodically (every DT ms). Reads temperature and humidity from the AM2320 sensor,
 * then scales the duty cycle linearly with temperature above 20.0°C, forces it to 0 below
 * that threshold, and clamps it to a maximum of 100.
 */
void FAN_EngineController();     // Będzie podawał wypełenie z ramki która przyjdzie

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
