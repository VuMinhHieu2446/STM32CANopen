################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library/CO_app_user.c \
../Library/PDO_cmd_user.c \
../Library/Response_ci.c \
../Library/SDO_cmd_user.c \
../Library/cli_command.c \
../Library/cli_command_table.c \
../Library/usb_cdc.c 

OBJS += \
./Library/CO_app_user.o \
./Library/PDO_cmd_user.o \
./Library/Response_ci.o \
./Library/SDO_cmd_user.o \
./Library/cli_command.o \
./Library/cli_command_table.o \
./Library/usb_cdc.o 

C_DEPS += \
./Library/CO_app_user.d \
./Library/PDO_cmd_user.d \
./Library/Response_ci.d \
./Library/SDO_cmd_user.d \
./Library/cli_command.d \
./Library/cli_command_table.d \
./Library/usb_cdc.d 


# Each subdirectory must supply rules for building sources it contributes
Library/%.o Library/%.su: ../Library/%.c Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H742xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"D:/CANopen/Project/Loop_back/CANopenNode" -I"D:/CANopen/Project/Loop_back/CANopenNode_STM32" -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"D:/CANopen/Project/Loop_back/Library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Library

clean-Library:
	-$(RM) ./Library/CO_app_user.d ./Library/CO_app_user.o ./Library/CO_app_user.su ./Library/PDO_cmd_user.d ./Library/PDO_cmd_user.o ./Library/PDO_cmd_user.su ./Library/Response_ci.d ./Library/Response_ci.o ./Library/Response_ci.su ./Library/SDO_cmd_user.d ./Library/SDO_cmd_user.o ./Library/SDO_cmd_user.su ./Library/cli_command.d ./Library/cli_command.o ./Library/cli_command.su ./Library/cli_command_table.d ./Library/cli_command_table.o ./Library/cli_command_table.su ./Library/usb_cdc.d ./Library/usb_cdc.o ./Library/usb_cdc.su

.PHONY: clean-Library

