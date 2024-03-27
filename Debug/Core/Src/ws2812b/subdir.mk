################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/ws2812b/ws2812b.c 

C_DEPS += \
./Core/Src/ws2812b/ws2812b.d 

OBJS += \
./Core/Src/ws2812b/ws2812b.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/ws2812b/%.o Core/Src/ws2812b/%.su Core/Src/ws2812b/%.cyclo: ../Core/Src/ws2812b/%.c Core/Src/ws2812b/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-ws2812b

clean-Core-2f-Src-2f-ws2812b:
	-$(RM) ./Core/Src/ws2812b/ws2812b.cyclo ./Core/Src/ws2812b/ws2812b.d ./Core/Src/ws2812b/ws2812b.o ./Core/Src/ws2812b/ws2812b.su

.PHONY: clean-Core-2f-Src-2f-ws2812b

