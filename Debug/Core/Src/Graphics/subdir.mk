################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Graphics/color.c \
../Core/Src/Graphics/display.c \
../Core/Src/Graphics/flicker.c \
../Core/Src/Graphics/matrix.c \
../Core/Src/Graphics/rainbow.c \
../Core/Src/Graphics/random.c \
../Core/Src/Graphics/time_display.c 

C_DEPS += \
./Core/Src/Graphics/color.d \
./Core/Src/Graphics/display.d \
./Core/Src/Graphics/flicker.d \
./Core/Src/Graphics/matrix.d \
./Core/Src/Graphics/rainbow.d \
./Core/Src/Graphics/random.d \
./Core/Src/Graphics/time_display.d 

OBJS += \
./Core/Src/Graphics/color.o \
./Core/Src/Graphics/display.o \
./Core/Src/Graphics/flicker.o \
./Core/Src/Graphics/matrix.o \
./Core/Src/Graphics/rainbow.o \
./Core/Src/Graphics/random.o \
./Core/Src/Graphics/time_display.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Graphics/%.o Core/Src/Graphics/%.su Core/Src/Graphics/%.cyclo: ../Core/Src/Graphics/%.c Core/Src/Graphics/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -Wextra -Wfatal-errors -pedantic -pedantic-errors -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wconversion -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Graphics

clean-Core-2f-Src-2f-Graphics:
	-$(RM) ./Core/Src/Graphics/color.cyclo ./Core/Src/Graphics/color.d ./Core/Src/Graphics/color.o ./Core/Src/Graphics/color.su ./Core/Src/Graphics/display.cyclo ./Core/Src/Graphics/display.d ./Core/Src/Graphics/display.o ./Core/Src/Graphics/display.su ./Core/Src/Graphics/flicker.cyclo ./Core/Src/Graphics/flicker.d ./Core/Src/Graphics/flicker.o ./Core/Src/Graphics/flicker.su ./Core/Src/Graphics/matrix.cyclo ./Core/Src/Graphics/matrix.d ./Core/Src/Graphics/matrix.o ./Core/Src/Graphics/matrix.su ./Core/Src/Graphics/rainbow.cyclo ./Core/Src/Graphics/rainbow.d ./Core/Src/Graphics/rainbow.o ./Core/Src/Graphics/rainbow.su ./Core/Src/Graphics/random.cyclo ./Core/Src/Graphics/random.d ./Core/Src/Graphics/random.o ./Core/Src/Graphics/random.su ./Core/Src/Graphics/time_display.cyclo ./Core/Src/Graphics/time_display.d ./Core/Src/Graphics/time_display.o ./Core/Src/Graphics/time_display.su

.PHONY: clean-Core-2f-Src-2f-Graphics

