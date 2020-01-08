################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32f103xb.s 

OBJS += \
./startup/startup_stm32f103xb.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo %cd%
	arm-none-eabi-as -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


