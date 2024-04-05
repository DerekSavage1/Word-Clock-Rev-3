################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Graphics/Animations/blink.c \
../Core/Src/Graphics/Animations/constant.c \
../Core/Src/Graphics/Animations/flicker.c \
../Core/Src/Graphics/Animations/rainbow.c \
../Core/Src/Graphics/Animations/twinkle.c 

C_DEPS += \
./Core/Src/Graphics/Animations/blink.d \
./Core/Src/Graphics/Animations/constant.d \
./Core/Src/Graphics/Animations/flicker.d \
./Core/Src/Graphics/Animations/rainbow.d \
./Core/Src/Graphics/Animations/twinkle.d 

OBJS += \
./Core/Src/Graphics/Animations/blink.o \
./Core/Src/Graphics/Animations/constant.o \
./Core/Src/Graphics/Animations/flicker.o \
./Core/Src/Graphics/Animations/rainbow.o \
./Core/Src/Graphics/Animations/twinkle.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Graphics/Animations/%.o Core/Src/Graphics/Animations/%.su Core/Src/Graphics/Animations/%.cyclo: ../Core/Src/Graphics/Animations/%.c Core/Src/Graphics/Animations/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -Wextra -Wfatal-errors -pedantic -pedantic-errors -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wconversion -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Graphics-2f-Animations

clean-Core-2f-Src-2f-Graphics-2f-Animations:
	-$(RM) ./Core/Src/Graphics/Animations/blink.cyclo ./Core/Src/Graphics/Animations/blink.d ./Core/Src/Graphics/Animations/blink.o ./Core/Src/Graphics/Animations/blink.su ./Core/Src/Graphics/Animations/constant.cyclo ./Core/Src/Graphics/Animations/constant.d ./Core/Src/Graphics/Animations/constant.o ./Core/Src/Graphics/Animations/constant.su ./Core/Src/Graphics/Animations/flicker.cyclo ./Core/Src/Graphics/Animations/flicker.d ./Core/Src/Graphics/Animations/flicker.o ./Core/Src/Graphics/Animations/flicker.su ./Core/Src/Graphics/Animations/rainbow.cyclo ./Core/Src/Graphics/Animations/rainbow.d ./Core/Src/Graphics/Animations/rainbow.o ./Core/Src/Graphics/Animations/rainbow.su ./Core/Src/Graphics/Animations/twinkle.cyclo ./Core/Src/Graphics/Animations/twinkle.d ./Core/Src/Graphics/Animations/twinkle.o ./Core/Src/Graphics/Animations/twinkle.su

.PHONY: clean-Core-2f-Src-2f-Graphics-2f-Animations

