################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c 

OBJS += \
./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.o 

C_DEPS += \
./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/%.o: ../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/Inc" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/Src/compiler" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/Src/decadriver" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/Src/platform" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/Drivers/STM32F1xx_HAL_Driver/Inc" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/Drivers/CMSIS/Include" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/BME280_driver-master" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/lsm9ds1_STdC/driver" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/UWB" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/I2C" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Core/Inc"  -Og -g -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


