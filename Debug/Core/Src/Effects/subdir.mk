################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Effects/color.c \
../Core/Src/Effects/display.c \
../Core/Src/Effects/random.c \
../Core/Src/Effects/time_display.c 

C_DEPS += \
./Core/Src/Effects/color.d \
./Core/Src/Effects/display.d \
./Core/Src/Effects/random.d \
./Core/Src/Effects/time_display.d 

OBJS += \
./Core/Src/Effects/color.o \
./Core/Src/Effects/display.o \
./Core/Src/Effects/random.o \
./Core/Src/Effects/time_display.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Effects/%.o Core/Src/Effects/%.su Core/Src/Effects/%.cyclo: ../Core/Src/Effects/%.c Core/Src/Effects/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -Wextra -Wfatal-errors -pedantic -pedantic-errors -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wconversion -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Effects

clean-Core-2f-Src-2f-Effects:
	-$(RM) ./Core/Src/Effects/color.cyclo ./Core/Src/Effects/color.d ./Core/Src/Effects/color.o ./Core/Src/Effects/color.su ./Core/Src/Effects/display.cyclo ./Core/Src/Effects/display.d ./Core/Src/Effects/display.o ./Core/Src/Effects/display.su ./Core/Src/Effects/random.cyclo ./Core/Src/Effects/random.d ./Core/Src/Effects/random.o ./Core/Src/Effects/random.su ./Core/Src/Effects/time_display.cyclo ./Core/Src/Effects/time_display.d ./Core/Src/Effects/time_display.o ./Core/Src/Effects/time_display.su

.PHONY: clean-Core-2f-Src-2f-Effects

