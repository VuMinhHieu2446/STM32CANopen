#ifndef SDO_CMD_H_H
#define SDO_CMD_H_H

#include "CO_app_STM32.h"
#include "CANopen.h"
#include "../CANopenNode/301/CO_driver.h"
//#include "301/CO_NMT_Heartbeat.h"
#include "OD.h"
//#include "CO_app_user.h"

typedef enum {
	NOP_MODE = 0x00U,
	PROFILE_POSITION_MODE = 0x01U,
	PROFILE_VELOCITY_MODE = 0x03U,
	PROFILE_TORQUE_MODE = 0x04U,
	HOMING_MODE = 0x06U,
	INTERPOLATION_POSITION_MODE = 0x07U
} OPERATION_MODE;



CO_SDO_abortCode_t read_SDO(CO_SDOclient_t *SDO_C, uint8_t nodeId,
                            uint16_t index, uint8_t subIndex,
                            uint8_t *buf, size_t bufSize, size_t *readSize);

CO_SDO_abortCode_t write_SDO(CO_SDOclient_t *SDO_C, uint8_t nodeId,
                             uint16_t index, uint8_t subIndex,
                             uint8_t *data, size_t dataSize);

void PDS_execute(CANopenNodeSTM32* __canopenNode_1, uint8_t node_id);
void CO_mapping_user(CANopenNodeSTM32* canopenNode);
uint32_t SDO_user_read(CANopenNodeSTM32* canopenNode, uint8_t node_id, uint16_t index, uint8_t subIndex);
void SDO_SetParam(CANopenNodeSTM32* canopenNode, uint8_t node_id, OPERATION_MODE mode);
#endif	/*	SDO_CMD_H_H	*/
