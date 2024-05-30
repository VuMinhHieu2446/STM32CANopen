#include "response_ci.h"
#include "stdarg.h"

//static UART_HandleTypeDef *huart_print;

void response_print(const char* str, ...)
{ 
	char stringArray[100];  //100: so ky tu trong 1 tham so
//	uint8_t cdc_send_flag = 1;
	
	va_list args;
	va_start(args, str);
	vsprintf(stringArray, str, args);
	va_end(args);

//	uint32_t time_print_data = HAL_GetTick();
//	while (1)
//	    {
//	        if (HAL_GetTick() - time_print_data >= 300)
//	        {
//	            if (cdc_send_flag)
//	            {
//	                CDC_Transmit_FS((uint8_t *)stringArray, strlen(stringArray));
//	                time_print_data = HAL_GetTick();
//	                cdc_send_flag = 0;
//	                break;
//	            }
//	        }
//	    }
	CDC_Transmit_FS((uint8_t *)stringArray, strlen(stringArray));
}

//void response_init(UART_HandleTypeDef *_huart_print)
//{
//	huart_print = _huart_print;
//}
