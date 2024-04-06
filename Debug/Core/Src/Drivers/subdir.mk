################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Drivers/WS2812B.c \
../Core/Src/Drivers/numeric_display.c 

C_DEPS += \
./Core/Src/Drivers/WS2812B.d \
./Core/Src/Drivers/numeric_display.d 

OBJS += \
./Core/Src/Drivers/WS2812B.o \
./Core/Src/Drivers/numeric_display.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Drivers/%.o Core/Src/Drivers/%.su Core/Src/Drivers/%.cyclo: ../Core/Src/Drivers/%.c Core/Src/Drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -Wextra -Wfatal-errors -pedantic -pedantic-errors -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wconversion -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Drivers

clean-Core-2f-Src-2f-Drivers:
	-$(RM) ./Core/Src/Drivers/WS2812B.cyclo ./Core/Src/Drivers/WS2812B.d ./Core/Src/Drivers/WS2812B.o ./Core/Src/Drivers/WS2812B.su ./Core/Src/Drivers/numeric_display.cyclo ./Core/Src/Drivers/numeric_display.d ./Core/Src/Drivers/numeric_display.o ./Core/Src/Drivers/numeric_display.su

.PHONY: clean-Core-2f-Src-2f-Drivers

