################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library/Src/visEffect.c 

C_DEPS += \
./Library/Src/visEffect.d 

OBJS += \
./Library/Src/visEffect.o 


# Each subdirectory must supply rules for building sources it contributes
Library/Src/%.o Library/Src/%.su Library/Src/%.cyclo: ../Library/Src/%.c Library/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/dsava/STM32CubeIDE/workspace_1.11.0/WordClock_Rev_3/Library/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Library-2f-Src

clean-Library-2f-Src:
	-$(RM) ./Library/Src/visEffect.cyclo ./Library/Src/visEffect.d ./Library/Src/visEffect.o ./Library/Src/visEffect.su

.PHONY: clean-Library-2f-Src

