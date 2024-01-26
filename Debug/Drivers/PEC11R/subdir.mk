################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/PEC11R/PEC11R.c 

C_DEPS += \
./Drivers/PEC11R/PEC11R.d 

OBJS += \
./Drivers/PEC11R/PEC11R.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/PEC11R/%.o Drivers/PEC11R/%.su: ../Drivers/PEC11R/%.c Drivers/PEC11R/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-PEC11R

clean-Drivers-2f-PEC11R:
	-$(RM) ./Drivers/PEC11R/PEC11R.d ./Drivers/PEC11R/PEC11R.o ./Drivers/PEC11R/PEC11R.su

.PHONY: clean-Drivers-2f-PEC11R

