################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../WS2812B/examples/f411/Core/Src/main.c \
../WS2812B/examples/f411/Core/Src/stm32f4xx_hal_msp.c \
../WS2812B/examples/f411/Core/Src/stm32f4xx_it.c \
../WS2812B/examples/f411/Core/Src/syscalls.c \
../WS2812B/examples/f411/Core/Src/sysmem.c \
../WS2812B/examples/f411/Core/Src/system_stm32f4xx.c 

C_DEPS += \
./WS2812B/examples/f411/Core/Src/main.d \
./WS2812B/examples/f411/Core/Src/stm32f4xx_hal_msp.d \
./WS2812B/examples/f411/Core/Src/stm32f4xx_it.d \
./WS2812B/examples/f411/Core/Src/syscalls.d \
./WS2812B/examples/f411/Core/Src/sysmem.d \
./WS2812B/examples/f411/Core/Src/system_stm32f4xx.d 

OBJS += \
./WS2812B/examples/f411/Core/Src/main.o \
./WS2812B/examples/f411/Core/Src/stm32f4xx_hal_msp.o \
./WS2812B/examples/f411/Core/Src/stm32f4xx_it.o \
./WS2812B/examples/f411/Core/Src/syscalls.o \
./WS2812B/examples/f411/Core/Src/sysmem.o \
./WS2812B/examples/f411/Core/Src/system_stm32f4xx.o 


# Each subdirectory must supply rules for building sources it contributes
WS2812B/examples/f411/Core/Src/%.o WS2812B/examples/f411/Core/Src/%.su WS2812B/examples/f411/Core/Src/%.cyclo: ../WS2812B/examples/f411/Core/Src/%.c WS2812B/examples/f411/Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/dsava/STM32CubeIDE/workspace_1.11.0/WordClock_Rev_3/WS2812B/examples/f411/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-WS2812B-2f-examples-2f-f411-2f-Core-2f-Src

clean-WS2812B-2f-examples-2f-f411-2f-Core-2f-Src:
	-$(RM) ./WS2812B/examples/f411/Core/Src/main.cyclo ./WS2812B/examples/f411/Core/Src/main.d ./WS2812B/examples/f411/Core/Src/main.o ./WS2812B/examples/f411/Core/Src/main.su ./WS2812B/examples/f411/Core/Src/stm32f4xx_hal_msp.cyclo ./WS2812B/examples/f411/Core/Src/stm32f4xx_hal_msp.d ./WS2812B/examples/f411/Core/Src/stm32f4xx_hal_msp.o ./WS2812B/examples/f411/Core/Src/stm32f4xx_hal_msp.su ./WS2812B/examples/f411/Core/Src/stm32f4xx_it.cyclo ./WS2812B/examples/f411/Core/Src/stm32f4xx_it.d ./WS2812B/examples/f411/Core/Src/stm32f4xx_it.o ./WS2812B/examples/f411/Core/Src/stm32f4xx_it.su ./WS2812B/examples/f411/Core/Src/syscalls.cyclo ./WS2812B/examples/f411/Core/Src/syscalls.d ./WS2812B/examples/f411/Core/Src/syscalls.o ./WS2812B/examples/f411/Core/Src/syscalls.su ./WS2812B/examples/f411/Core/Src/sysmem.cyclo ./WS2812B/examples/f411/Core/Src/sysmem.d ./WS2812B/examples/f411/Core/Src/sysmem.o ./WS2812B/examples/f411/Core/Src/sysmem.su ./WS2812B/examples/f411/Core/Src/system_stm32f4xx.cyclo ./WS2812B/examples/f411/Core/Src/system_stm32f4xx.d ./WS2812B/examples/f411/Core/Src/system_stm32f4xx.o ./WS2812B/examples/f411/Core/Src/system_stm32f4xx.su

.PHONY: clean-WS2812B-2f-examples-2f-f411-2f-Core-2f-Src

