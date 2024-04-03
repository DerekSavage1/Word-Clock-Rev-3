################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/UI/button.c \
../Core/Src/UI/menu.c \
../Core/Src/UI/settings.c 

C_DEPS += \
./Core/Src/UI/button.d \
./Core/Src/UI/menu.d \
./Core/Src/UI/settings.d 

OBJS += \
./Core/Src/UI/button.o \
./Core/Src/UI/menu.o \
./Core/Src/UI/settings.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/UI/%.o Core/Src/UI/%.su Core/Src/UI/%.cyclo: ../Core/Src/UI/%.c Core/Src/UI/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -Wextra -Wfatal-errors -pedantic -pedantic-errors -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wconversion -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-UI

clean-Core-2f-Src-2f-UI:
	-$(RM) ./Core/Src/UI/button.cyclo ./Core/Src/UI/button.d ./Core/Src/UI/button.o ./Core/Src/UI/button.su ./Core/Src/UI/menu.cyclo ./Core/Src/UI/menu.d ./Core/Src/UI/menu.o ./Core/Src/UI/menu.su ./Core/Src/UI/settings.cyclo ./Core/Src/UI/settings.d ./Core/Src/UI/settings.o ./Core/Src/UI/settings.su

.PHONY: clean-Core-2f-Src-2f-UI

