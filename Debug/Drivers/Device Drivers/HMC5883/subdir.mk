################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Device\ Drivers/HMC5883/HMC5883.c 

OBJS += \
./Drivers/Device\ Drivers/HMC5883/HMC5883.o 

C_DEPS += \
./Drivers/Device\ Drivers/HMC5883/HMC5883.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Device\ Drivers/HMC5883/HMC5883.o: ../Drivers/Device\ Drivers/HMC5883/HMC5883.c Drivers/Device\ Drivers/HMC5883/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/Device Drivers/HMC5883/HMC5883.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-Device-20-Drivers-2f-HMC5883

clean-Drivers-2f-Device-20-Drivers-2f-HMC5883:
	-$(RM) ./Drivers/Device\ Drivers/HMC5883/HMC5883.cyclo ./Drivers/Device\ Drivers/HMC5883/HMC5883.d ./Drivers/Device\ Drivers/HMC5883/HMC5883.o ./Drivers/Device\ Drivers/HMC5883/HMC5883.su

.PHONY: clean-Drivers-2f-Device-20-Drivers-2f-HMC5883

