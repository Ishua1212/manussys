################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Common/Src/acc.c \
../Common/Src/button.c \
../Common/Src/log.c \
../Common/Src/points.c 

OBJS += \
./Common/Src/acc.o \
./Common/Src/button.o \
./Common/Src/log.o \
./Common/Src/points.o 

C_DEPS += \
./Common/Src/acc.d \
./Common/Src/button.d \
./Common/Src/log.d \
./Common/Src/points.d 


# Each subdirectory must supply rules for building sources it contributes
Common/Src/%.o Common/Src/%.su Common/Src/%.cyclo: ../Common/Src/%.c Common/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/BSP -I../Drivers/BSP/STM32F429i-Discovery -I../Utilities/Fonts -I../Common/Inc -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Common-2f-Src

clean-Common-2f-Src:
	-$(RM) ./Common/Src/acc.cyclo ./Common/Src/acc.d ./Common/Src/acc.o ./Common/Src/acc.su ./Common/Src/button.cyclo ./Common/Src/button.d ./Common/Src/button.o ./Common/Src/button.su ./Common/Src/log.cyclo ./Common/Src/log.d ./Common/Src/log.o ./Common/Src/log.su ./Common/Src/points.cyclo ./Common/Src/points.d ./Common/Src/points.o ./Common/Src/points.su

.PHONY: clean-Common-2f-Src

