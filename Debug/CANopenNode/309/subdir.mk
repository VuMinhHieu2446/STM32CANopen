################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANopenNode/309/CO_gateway_ascii.c 

OBJS += \
./CANopenNode/309/CO_gateway_ascii.o 

C_DEPS += \
./CANopenNode/309/CO_gateway_ascii.d 


# Each subdirectory must supply rules for building sources it contributes
CANopenNode/309/%.o CANopenNode/309/%.su: ../CANopenNode/309/%.c CANopenNode/309/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H742xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"D:/CANopen/Project/Loop_back/CANopenNode" -I"D:/CANopen/Project/Loop_back/CANopenNode_STM32" -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"D:/CANopen/Project/Loop_back/Library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CANopenNode-2f-309

clean-CANopenNode-2f-309:
	-$(RM) ./CANopenNode/309/CO_gateway_ascii.d ./CANopenNode/309/CO_gateway_ascii.o ./CANopenNode/309/CO_gateway_ascii.su

.PHONY: clean-CANopenNode-2f-309

