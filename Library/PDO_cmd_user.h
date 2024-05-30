#ifndef PDO_CMD_H_H
#define PDO_CMD_H_H

#include "SDO_cmd_user.h"
#include "stm32h7xx_hal_rng.h"
#include "response_ci.h"
#include <stdlib.h>

typedef struct {
    uint8_t node_id_1;
    uint32_t targetP_1;
    uint8_t node_id_2;
    uint32_t targetP_2;
} ServoParams;

CO_ReturnError_t Send_PDOPosition(CANopenNodeSTM32 *canopenNode, uint32_t id, uint32_t TargetPosition);
CO_ReturnError_t Send_PDOControlWord(CANopenNodeSTM32 *canopenNode, uint32_t id, uint16_t ControlWord);

void CO_PDO_execute(CANopenNodeSTM32 *canopenNode);
void running_servo(char **argv, uint8_t argv_num);
#endif	/*	PDO_CMD_H_H	*/
