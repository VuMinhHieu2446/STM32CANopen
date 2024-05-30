#include "../Library/cli_command_table.h"

const cli_command_info_t command_infor_running_servo =
{
	running_servo,
	"command set effect led: \"SetEffect_Led argv\" "
};
const	cli_command_entry_t command_entry_table[] = 
{
	{"Running_Servo",&command_infor_running_servo},
	{NULL,NULL},
};
