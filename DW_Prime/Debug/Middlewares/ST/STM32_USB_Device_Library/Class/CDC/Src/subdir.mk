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
Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.o: ../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Inc -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/compiler" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/decadriver" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/platform" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/BME280_driver-master" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/lsm9ds1_STdC/driver" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/UWB" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/I2C" -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -Og -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

