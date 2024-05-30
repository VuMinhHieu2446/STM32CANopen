#include "cli_command.h"
#include "cli_types.h"

extern const	cli_command_entry_t command_entry_table[];
CANopenNodeSTM32 *canopenNode;
//	/*1
const cli_command_info_t* find_command_info(char *cmd)
{
	const cli_command_entry_t *command_entry = command_entry_table;
	while(command_entry -> command_info != NULL)
	{
		if(strcmp(command_entry ->name, cmd) == 0)
		{
			return command_entry -> command_info;
		}
		command_entry++;
	}
	return NULL;
}
// */

/*	2
const cli_command_entry_t* find_command_entry(char *cmd)
{
	const cli_command_entry_t *command_entry = command_entry_table;
	while(command_entry -> command_info != NULL)
	{
		if(strcmp(command_entry ->name,cmd) == 0)
		{
			return command_entry;
		}
		command_entry++;
	}
	return NULL;
}	
*/

//3
//const cli_command_entry_t* find_command_entry(char *cmd)
//{
//	uint8_t index = 0;
//	while(command_entry_table[index].command_info != NULL)
//	{
//		if(strcmp(command_entry_table[index].name,cmd) == 0)
//		{
//			return &command_entry_table[index];
//		}
//		index++;
//	}
//	return NULL;
//}

void cli_command_excute(char *uart_buff, uint8_t len)
{
	char *argv[10];				
	uint8_t argv_num = 0;
	char *pch;
	pch = strtok(uart_buff," ");
	while(pch != NULL)
	{		
		argv[argv_num++] = pch;
		pch = strtok (NULL, " "); 
	}
	// /*	1
//	const cli_command_entry_t *command_entry_help = command_entry_table;
	const cli_command_info_t* command_info = find_command_info(argv[0]);
	if(command_info != NULL)
	{
		command_info->function(argv,argv_num);
	}
	else
	{
		response_print("find not found command \n");
//		while(command_entry_help ->name != NULL)
//		{
//			response_print("%s\n",command_entry_help->command_info->help);
//			command_entry_help++;
//		}
	}
	// */

	/*	2
	const cli_command_entry_t *command_entry = find_command_entry(argv[0]);
	if(command_entry != NULL)
	{
		command_entry->command_info->function(argv,argv_num);
	}
	else
	{
		response_print("find not found command");
	}
	*/
}
