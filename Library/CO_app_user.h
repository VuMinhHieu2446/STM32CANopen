#ifndef CO_app_user_H_H
#define CO_app_user_H_H

#include "CO_app_STM32.h"
#include "PDO_cmd_user.h"
#include "SDO_cmd_user.h"

void canopen_app_user_init(CANopenNodeSTM32* __canopenNode_1,
							FDCAN_HandleTypeDef* __CANHandle,
							void (*__HWInitFunction)(void),
							TIM_HandleTypeDef* __timerHandle);

void canopen_app_user_config(CANopenNodeSTM32* canopenNode);
#endif	/*	CO_app_user_H_H	*/
