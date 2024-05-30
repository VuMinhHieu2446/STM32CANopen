#include "CO_app_user.h"

void canopen_app_user_init(CANopenNodeSTM32* canopenNode,
							FDCAN_HandleTypeDef* __CANHandle,
							void (*HWInitFunction)(void),
							TIM_HandleTypeDef* __timerHandle)
{
	canopenNode->CANHandle = __CANHandle;
	canopenNode->HWInitFunction = HWInitFunction;
	canopenNode->timerHandle = __timerHandle;
	canopenNode->desiredNodeID = 0x02;
	canopenNode->baudrate = 1000;

	 canopen_app_init(canopenNode);
}

void canopen_app_user_config(CANopenNodeSTM32* canopenNode)
{
	CO_mapping_user(canopenNode);
	SDO_SetParam(canopenNode, 1, PROFILE_POSITION_MODE);
	SDO_SetParam(canopenNode, 2, PROFILE_POSITION_MODE);
	PDS_execute(canopenNode, 1);
	PDS_execute(canopenNode, 2);
}

