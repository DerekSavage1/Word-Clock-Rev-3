################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Numeric_Display/Numeric_Display.c 

C_DEPS += \
./Drivers/Numeric_Display/Numeric_Display.d 

OBJS += \
./Drivers/Numeric_Display/Numeric_Display.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Numeric_Display/%.o Drivers/Numeric_Display/%.su Drivers/Numeric_Display/%.cyclo: ../Drivers/Numeric_Display/%.c Drivers/Numeric_Display/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Numeric_Display

clean-Drivers-2f-Numeric_Display:
	-$(RM) ./Drivers/Numeric_Display/Numeric_Display.cyclo ./Drivers/Numeric_Display/Numeric_Display.d ./Drivers/Numeric_Display/Numeric_Display.o ./Drivers/Numeric_Display/Numeric_Display.su

.PHONY: clean-Drivers-2f-Numeric_Display

