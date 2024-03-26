################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../WS2812B/examples/f411/Core/Startup/startup_stm32f411ceux.s 

S_DEPS += \
./WS2812B/examples/f411/Core/Startup/startup_stm32f411ceux.d 

OBJS += \
./WS2812B/examples/f411/Core/Startup/startup_stm32f411ceux.o 


# Each subdirectory must supply rules for building sources it contributes
WS2812B/examples/f411/Core/Startup/%.o: ../WS2812B/examples/f411/Core/Startup/%.s WS2812B/examples/f411/Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-WS2812B-2f-examples-2f-f411-2f-Core-2f-Startup

clean-WS2812B-2f-examples-2f-f411-2f-Core-2f-Startup:
	-$(RM) ./WS2812B/examples/f411/Core/Startup/startup_stm32f411ceux.d ./WS2812B/examples/f411/Core/Startup/startup_stm32f411ceux.o

.PHONY: clean-WS2812B-2f-examples-2f-f411-2f-Core-2f-Startup

