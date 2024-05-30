#ifndef CLI_TYPES_H
#define CLI_TYPES_H
#include "stdint.h"
#include "CO_app_STM32.h"
typedef void (*cli_command_function_t)( char **argv, uint8_t argv_num);
//typedef void (*cli_command_function_t)(CANopenNodeSTM32 *canopenNode, char **argv, uint8_t argv_num);

typedef struct
{
	cli_command_function_t function;
	char *help;
}cli_command_info_t;

typedef struct
{
	const char *name;
	const cli_command_info_t *command_info;
}cli_command_entry_t;
#endif
