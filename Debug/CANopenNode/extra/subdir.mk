################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANopenNode/extra/CO_trace.c 

OBJS += \
./CANopenNode/extra/CO_trace.o 

C_DEPS += \
./CANopenNode/extra/CO_trace.d 


# Each subdirectory must supply rules for building sources it contributes
CANopenNode/extra/%.o CANopenNode/extra/%.su: ../CANopenNode/extra/%.c CANopenNode/extra/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H742xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"D:/CANopen/Project/Loop_back/CANopenNode" -I"D:/CANopen/Project/Loop_back/CANopenNode_STM32" -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"D:/CANopen/Project/Loop_back/Library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CANopenNode-2f-extra

clean-CANopenNode-2f-extra:
	-$(RM) ./CANopenNode/extra/CO_trace.d ./CANopenNode/extra/CO_trace.o ./CANopenNode/extra/CO_trace.su

.PHONY: clean-CANopenNode-2f-extra

