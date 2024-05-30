################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/CO_app_user.c \
../App/GetTemperature_ci.c \
../App/LM35.c \
../App/PDO_cmd_user.c \
../App/Response_ci.c \
../App/SDO_cmd_user.c \
../App/SetTemp_ci.c \
../App/UART.c \
../App/app_led.c \
../App/cli_command.c \
../App/cli_command_table.c \
../App/effect_led_ci.c \
../App/led_driver.c \
../App/usb_cdc.c 

OBJS += \
./App/CO_app_user.o \
./App/GetTemperature_ci.o \
./App/LM35.o \
./App/PDO_cmd_user.o \
./App/Response_ci.o \
./App/SDO_cmd_user.o \
./App/SetTemp_ci.o \
./App/UART.o \
./App/app_led.o \
./App/cli_command.o \
./App/cli_command_table.o \
./App/effect_led_ci.o \
./App/led_driver.o \
./App/usb_cdc.o 

C_DEPS += \
./App/CO_app_user.d \
./App/GetTemperature_ci.d \
./App/LM35.d \
./App/PDO_cmd_user.d \
./App/Response_ci.d \
./App/SDO_cmd_user.d \
./App/SetTemp_ci.d \
./App/UART.d \
./App/app_led.d \
./App/cli_command.d \
./App/cli_command_table.d \
./App/effect_led_ci.d \
./App/led_driver.d \
./App/usb_cdc.d 


# Each subdirectory must supply rules for building sources it contributes
App/%.o App/%.su: ../App/%.c App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H742xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"D:/CANopen/Project/Loop_back/CANopenNode" -I"D:/CANopen/Project/Loop_back/CANopenNode_STM32" -I"D:/CANopen/Project/Loop_back/App" -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App

clean-App:
	-$(RM) ./App/CO_app_user.d ./App/CO_app_user.o ./App/CO_app_user.su ./App/GetTemperature_ci.d ./App/GetTemperature_ci.o ./App/GetTemperature_ci.su ./App/LM35.d ./App/LM35.o ./App/LM35.su ./App/PDO_cmd_user.d ./App/PDO_cmd_user.o ./App/PDO_cmd_user.su ./App/Response_ci.d ./App/Response_ci.o ./App/Response_ci.su ./App/SDO_cmd_user.d ./App/SDO_cmd_user.o ./App/SDO_cmd_user.su ./App/SetTemp_ci.d ./App/SetTemp_ci.o ./App/SetTemp_ci.su ./App/UART.d ./App/UART.o ./App/UART.su ./App/app_led.d ./App/app_led.o ./App/app_led.su ./App/cli_command.d ./App/cli_command.o ./App/cli_command.su ./App/cli_command_table.d ./App/cli_command_table.o ./App/cli_command_table.su ./App/effect_led_ci.d ./App/effect_led_ci.o ./App/effect_led_ci.su ./App/led_driver.d ./App/led_driver.o ./App/led_driver.su ./App/usb_cdc.d ./App/usb_cdc.o ./App/usb_cdc.su

.PHONY: clean-App

