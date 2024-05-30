#include "SDO_cmd_user.h"


CO_SDO_abortCode_t read_SDO(CO_SDOclient_t *SDO_C, uint8_t nodeId,
                            uint16_t index, uint8_t subIndex,
                            uint8_t *buf, size_t bufSize, size_t *readSize)
{
    CO_SDO_return_t SDO_ret;

    // setup client (this can be skipped, if remote device don't change)
    SDO_ret = CO_SDOclient_setup(SDO_C,
                                 CO_CAN_ID_SDO_CLI + nodeId,
                                 CO_CAN_ID_SDO_SRV + nodeId,
                                 nodeId);
    if (SDO_ret != CO_SDO_RT_ok_communicationEnd) {
        return CO_SDO_AB_GENERAL;
    }

    // initiate upload
    SDO_ret = CO_SDOclientUploadInitiate(SDO_C, index, subIndex, 1000, false);
    if (SDO_ret != CO_SDO_RT_ok_communicationEnd) {
        return CO_SDO_AB_GENERAL;
    }

    // upload data
    do {
        uint32_t timeDifference_us = 10000;
        CO_SDO_abortCode_t abortCode = CO_SDO_AB_NONE;

        SDO_ret = CO_SDOclientUpload(SDO_C,
                                     timeDifference_us,
                                     false,
                                     &abortCode,
                                     NULL, NULL, NULL);
        if (SDO_ret < 0) {
            return abortCode;
        }

        HAL_Delay(1);
    } while(SDO_ret > 0);

    // copy data to the user buffer (for long data function must be called
    // several times inside the loop)
    *readSize = CO_SDOclientUploadBufRead(SDO_C, buf, bufSize);

    return CO_SDO_AB_NONE;
}

CO_SDO_abortCode_t write_SDO(CO_SDOclient_t *SDO_C, uint8_t nodeId,
                             uint16_t index, uint8_t subIndex,
                             uint8_t *data, size_t dataSize)
{
    CO_SDO_return_t SDO_ret;
    bool_t bufferPartial = false;

    // setup client (this can be skipped, if remote device is the same)
    SDO_ret = CO_SDOclient_setup(SDO_C,
                                 CO_CAN_ID_SDO_CLI + nodeId,
                                 CO_CAN_ID_SDO_SRV + nodeId,
                                 nodeId);
    if (SDO_ret != CO_SDO_RT_ok_communicationEnd) {
        return -1;
    }

    // initiate download
    SDO_ret = CO_SDOclientDownloadInitiate(SDO_C, index, subIndex,
                                           dataSize, 1000, false);
    if (SDO_ret != CO_SDO_RT_ok_communicationEnd) {
        return -1;
    }

    // fill data
    size_t nWritten = CO_SDOclientDownloadBufWrite(SDO_C, data, dataSize);
    if (nWritten < dataSize) {
        bufferPartial = true;
        // If SDO Fifo buffer is too small, data can be refilled in the loop.
    }

    //download data
    do {
        uint32_t timeDifference_us = 10000;
        CO_SDO_abortCode_t abortCode = CO_SDO_AB_NONE;

        SDO_ret = CO_SDOclientDownload(SDO_C,
                                       timeDifference_us,
                                       false,
                                       bufferPartial,
                                       &abortCode,
                                       NULL, NULL);
        if (SDO_ret < 0) {
            return abortCode;
        }

        HAL_Delay(1);
    } while(SDO_ret > 0);

    return CO_SDO_AB_NONE;
}

static uint8_t data[4];

void Switch_On_Disabled(CANopenNodeSTM32* ____canopenNode, uint8_t __node_id)
{
	data[0] = 0x00;
	data[1] = 0x00;
	data[2] = 0x00;
	data[3] = 0x00;
	write_SDO(____canopenNode->canOpenStack->SDOclient, __node_id, 0x6040, 0x00, data, 2);
}
void Ready_to_Switch_On(CANopenNodeSTM32* ____canopenNode, uint8_t __node_id)
	{
		data[0] = 0x06;
		data[1] = 0x00;
		data[2] = 0x00;
		data[3] = 0x00;
		write_SDO(____canopenNode->canOpenStack->SDOclient, __node_id, 0x6040, 0x00, data, 2);
	}
void Switch_On(CANopenNodeSTM32* ____canopenNode, uint8_t __node_id)
	{
		data[0] = 0x07;
		data[1] = 0x00;
		data[2] = 0x00;
		data[3] = 0x00;
		write_SDO(____canopenNode->canOpenStack->SDOclient, __node_id, 0x6040, 0x00, data, 2);
	}
void Operation_Enabled(CANopenNodeSTM32* ____canopenNode, uint8_t __node_id)
	{
		data[0] = 0x0F;
		data[1] = 0x00;
		data[2] = 0x00;
		data[3] = 0x00;
		write_SDO(____canopenNode->canOpenStack->SDOclient, __node_id, 0x6040, 0x00, data, 2);
	}

void PDS_execute(CANopenNodeSTM32* __canopenNode, uint8_t node_id)
{
	Switch_On_Disabled(__canopenNode, node_id);
	Ready_to_Switch_On(__canopenNode, node_id);
	Switch_On(__canopenNode, node_id);
	Operation_Enabled(__canopenNode, node_id);
}

void Disable_PDO(CANopenNodeSTM32* ____canopenNode, uint8_t __node_id, uint8_t number_PDO)
{
	 data[0] = 0x00;
	 data[1] = 0x00;
	 data[2] = 0x00;
	 data[3] = 0x80;
	write_SDO(____canopenNode->canOpenStack->SDOclient, __node_id, OD_H1400_RXPDO_1_PARAM+(number_PDO-1), 0x01, data, 4);
}
void set_COB_ID(CANopenNodeSTM32* ____canopenNode, uint8_t __node_id, uint8_t number_PDO)
{
	uint32_t COB_ID_PDO = CO_CAN_ID_RPDO_1 + (number_PDO-1)*0x100 + __node_id;
	data[0] = COB_ID_PDO 		& 0xFFU;
	data[1] = (COB_ID_PDO>>8) 	& 0xFFU;
	data[2] = 0x00;
	data[3] = 0x80;
	write_SDO(____canopenNode->canOpenStack->SDOclient, __node_id, OD_H1400_RXPDO_1_PARAM+(number_PDO-1), 0x01, data, 4);
}
void set_transmission_type(CANopenNodeSTM32* ____canopenNode, uint8_t __node_id, uint8_t number_PDO)
{
	data[0] = CO_PDO_TRANSM_TYPE_SYNC_ACYCLIC 		& 0xFFU;
	data[1] = 0x00;
	data[2] = 0x00;
	data[3] = 0x00;
	write_SDO(____canopenNode->canOpenStack->SDOclient, __node_id, OD_H1400_RXPDO_1_PARAM+(number_PDO-1), 0x02, data, 2);
}
void deactivating_mapping(CANopenNodeSTM32* ____canopenNode, uint8_t __node_id, uint8_t number_PDO)
{
	data[0] = 0x00;
	data[1] = 0x00;
	data[2] = 0x00;
	data[3] = 0x00;
	write_SDO(____canopenNode->canOpenStack->SDOclient, __node_id, OD_H1600_RXPDO_1_MAPPING+(number_PDO-1), 0x00, data, 2);
}
void mapping_object(CANopenNodeSTM32* ____canopenNode, uint8_t __node_id, uint8_t number_PDO, uint32_t __ObjectToMapping, uint8_t __subIndexToMapping)
{
	data[0] = __ObjectToMapping			& 0xFFU;
	data[1] = (__ObjectToMapping>>8)	& 0xFFU;
	data[2] = (__ObjectToMapping>>16)	& 0xFFU;
	data[3] = (__ObjectToMapping>>24)	& 0xFFU;
	write_SDO(____canopenNode->canOpenStack->SDOclient, __node_id, OD_H1600_RXPDO_1_MAPPING+(number_PDO-1), __subIndexToMapping, data, 4);
}
void Active_mapping(CANopenNodeSTM32* ____canopenNode, uint8_t __node_id, uint8_t number_PDO)
{
	data[0] = 0x01;
	data[1] = 0x00;
	data[2] = 0x00;
	data[3] = 0x00;
	write_SDO(____canopenNode->canOpenStack->SDOclient, __node_id, OD_H1600_RXPDO_1_MAPPING+(number_PDO-1), 0x00, data, 2);
}
void Enable_PDO(CANopenNodeSTM32* ____canopenNode, uint8_t __node_id, uint8_t number_PDO)
{
	uint32_t COB_ID_PDO = CO_CAN_ID_RPDO_1 + (number_PDO-1)*0x100 + __node_id;
	data[0] = COB_ID_PDO 		& 0xFFU;
	data[1] = (COB_ID_PDO>>8) 	& 0xFFU;
	data[2] = 0x00;
	data[3] = 0x00;
	write_SDO(____canopenNode->canOpenStack->SDOclient, __node_id, OD_H1400_RXPDO_1_PARAM+(number_PDO-1), 0x01, data, 4);
}

void PDO_mapping(CANopenNodeSTM32* __canopenNode, uint8_t node_id, uint8_t NumberOfPDO, uint32_t ObjectToMapping, uint8_t subIndexToMapping)
{
//	CO_NMT_sendCommand(__canopenNode->canOpenStack->NMT, CO_NMT_RESET_NODE, node_id);
//	HAL_Delay(1000);
//	CO_NMT_sendCommand(__canopenNode->canOpenStack->NMT, CO_NMT_ENTER_PRE_OPERATIONAL, node_id);
//	HAL_Delay(50);

	Disable_PDO(__canopenNode, node_id, NumberOfPDO);
	set_COB_ID(__canopenNode, node_id, NumberOfPDO);
	set_transmission_type(__canopenNode, node_id, NumberOfPDO);
	deactivating_mapping(__canopenNode, node_id, NumberOfPDO);
	mapping_object(__canopenNode, node_id, NumberOfPDO, ObjectToMapping, subIndexToMapping);
	Active_mapping(__canopenNode, node_id, NumberOfPDO);
	Enable_PDO(__canopenNode, node_id, NumberOfPDO);

//	CO_NMT_sendCommand(__canopenNode->canOpenStack->NMT, CO_NMT_ENTER_OPERATIONAL, node_id);
//	HAL_Delay(50);
}

void CO_mapping_user(CANopenNodeSTM32* canopenNode)
{
	CO_NMT_sendCommand(canopenNode->canOpenStack->NMT, CO_NMT_RESET_NODE, 1);
	HAL_Delay(1000);
	CO_NMT_sendCommand(canopenNode->canOpenStack->NMT, CO_NMT_RESET_NODE, 2);
	HAL_Delay(1000);
	CO_NMT_sendCommand(canopenNode->canOpenStack->NMT, CO_NMT_ENTER_PRE_OPERATIONAL, 1);
	HAL_Delay(50);
	CO_NMT_sendCommand(canopenNode->canOpenStack->NMT, CO_NMT_ENTER_PRE_OPERATIONAL, 2);
	HAL_Delay(50);

	// Active RPDO_1
	PDO_mapping(canopenNode, 1, 1, 0x60400010, 0x01);
	PDO_mapping(canopenNode, 2, 1, 0x60400010, 0x01);
	// Active RPDO_2
	PDO_mapping(canopenNode, 1, 2, 0x607A0020, 0x01);
	PDO_mapping(canopenNode, 2, 2, 0x607A0020, 0x01);

	CO_NMT_sendCommand(canopenNode->canOpenStack->NMT, CO_NMT_ENTER_OPERATIONAL, 1);
	HAL_Delay(50);
	CO_NMT_sendCommand(canopenNode->canOpenStack->NMT, CO_NMT_ENTER_OPERATIONAL, 2);
	HAL_Delay(50);
}

void SDO_ProfileVelocity(CANopenNodeSTM32* ____canopenNode, uint8_t ____node_id, uint32_t Velocity)
{
	data[0] = Velocity			& 0xFFU;
	data[1] = (Velocity>>8)	& 0xFFU;
	data[2] = (Velocity>>16)	& 0xFFU;
	data[3] = (Velocity>>24)	& 0xFFU;
	write_SDO(____canopenNode->canOpenStack->SDOclient, ____node_id, 0x6081, 0x00, data, 4);
}
void SDO_EndVelocity(CANopenNodeSTM32* ____canopenNode, uint8_t ____node_id, uint32_t EndVelocity)
{
	data[0] = EndVelocity			& 0xFFU;
	data[1] = (EndVelocity>>8)	& 0xFFU;
	data[2] = (EndVelocity>>16)	& 0xFFU;
	data[3] = (EndVelocity>>24)	& 0xFFU;
	write_SDO(____canopenNode->canOpenStack->SDOclient, ____node_id, 0x6082, 0x00, data, 4);
}
void SDO_ProfileAcceleration(CANopenNodeSTM32* ____canopenNode, uint8_t ____node_id, uint32_t Acceleration)
{
	data[0] = Acceleration			& 0xFFU;
	data[1] = (Acceleration>>8)	& 0xFFU;
	data[2] = (Acceleration>>16)	& 0xFFU;
	data[3] = (Acceleration>>24)	& 0xFFU;
	write_SDO(____canopenNode->canOpenStack->SDOclient, ____node_id, 0x6083, 0x00, data, 4);
}
void SDO_ProfileDeceleration(CANopenNodeSTM32* ____canopenNode, uint8_t ____node_id, uint32_t Deceleration)
{
	data[0] = Deceleration			& 0xFFU;
	data[1] = (Deceleration>>8)	& 0xFFU;
	data[2] = (Deceleration>>16)	& 0xFFU;
	data[3] = (Deceleration>>24)	& 0xFFU;
	write_SDO(____canopenNode->canOpenStack->SDOclient, ____node_id, 0x6084, 0x00, data, 4);
}
void SDO_Position(CANopenNodeSTM32* __canopenNode, uint8_t __node_id)
{
	SDO_ProfileVelocity(__canopenNode,  __node_id,  0xC350);
	SDO_EndVelocity(__canopenNode,  __node_id,  0x00);
	SDO_ProfileAcceleration(__canopenNode,  __node_id,  0x61A8);
	SDO_ProfileDeceleration(__canopenNode,  __node_id,  0x30D4);
}
uint8_t SDOmode(CANopenNodeSTM32* __canopenNode, uint8_t __node_id, OPERATION_MODE mode)
{
	data[0] = mode	& 0xFFU;
	data[1] = 0x00;
	data[2] = 0x00;
	data[3] = 0x00;
	write_SDO(__canopenNode->canOpenStack->SDOclient, __node_id, 0x6060, 0x00, data, 1);
	return mode;
}
void SDO_SetParam(CANopenNodeSTM32* canopenNode, uint8_t node_id, OPERATION_MODE mode)
{
	SDOmode(canopenNode, node_id, mode);
	switch(mode){
	case PROFILE_POSITION_MODE:
	{
		SDO_Position(canopenNode, node_id);
		break;
	}
	case PROFILE_VELOCITY_MODE:
	{
		break;
	}
	case PROFILE_TORQUE_MODE:
	{
		break;
	}
	default:
		break;
	}
}




uint32_t SDO_user_read(CANopenNodeSTM32* canopenNode, uint8_t node_id, uint16_t index, uint8_t subIndex)
{
	uint8_t dataread = 0x00;
	size_t actual_size_data = 0;
	read_SDO(canopenNode->canOpenStack->SDOclient, node_id, index, subIndex, &dataread, 4, &actual_size_data);
	return dataread;
}









//void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
//{
//  if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
//  {
//    /* Retreive Rx messages from RX FIFO0 */
//    if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
//    {
//    /* Reception Error */
//    Error_Handler();
//    }
//    if (HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
//    {
//      /* Notification Error */
//      Error_Handler();
//    }
//  }
//}





















