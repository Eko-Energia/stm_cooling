/*
 * cooler_left_app.h
 *
 *  Created on: 8 kwi 2026
 *      Author: Karol
 */

#ifndef INC_COOLER_LEFT_APP_H_
#define INC_COOLER_LEFT_APP_H_

#define CAN_TIME_TO_SEND_MSG (1)
#define CAN_WAIT_TO_SEND_MSG (0)


void COOLER_IsTimeSendMsg(uint8_t* interuptCanFlag);

void Init_Cooler();

void COOLER_app();

void COOLER_refresh_control();

#endif /* INC_COOLER_LEFT_APP_H_ */
