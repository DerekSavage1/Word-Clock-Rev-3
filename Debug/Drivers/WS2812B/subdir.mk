################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/WS2812B/WS2812B.c 

C_DEPS += \
./Drivers/WS2812B/WS2812B.d 

OBJS += \
./Drivers/WS2812B/WS2812B.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/WS2812B/%.o Drivers/WS2812B/%.su Drivers/WS2812B/%.cyclo: ../Drivers/WS2812B/%.c Drivers/WS2812B/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -Wextra -Wfatal-errors -pedantic -pedantic-errors -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wconversion -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-WS2812B

clean-Drivers-2f-WS2812B:
	-$(RM) ./Drivers/WS2812B/WS2812B.cyclo ./Drivers/WS2812B/WS2812B.d ./Drivers/WS2812B/WS2812B.o ./Drivers/WS2812B/WS2812B.su

.PHONY: clean-Drivers-2f-WS2812B

