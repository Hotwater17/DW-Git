################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/decadriver/deca_device.c \
../Src/decadriver/deca_params_init.c 

OBJS += \
./Src/decadriver/deca_device.o \
./Src/decadriver/deca_params_init.o 

C_DEPS += \
./Src/decadriver/deca_device.d \
./Src/decadriver/deca_params_init.d 


# Each subdirectory must supply rules for building sources it contributes
Src/decadriver/deca_device.o: ../Src/decadriver/deca_device.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Inc -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/compiler" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/decadriver" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/platform" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/BME280_driver-master" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/lsm9ds1_STdC/driver" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/UWB" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/I2C" -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -Og -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/decadriver/deca_device.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/decadriver/deca_params_init.o: ../Src/decadriver/deca_params_init.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Inc -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/compiler" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/decadriver" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/platform" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/BME280_driver-master" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/lsm9ds1_STdC/driver" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/UWB" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/I2C" -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -Og -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/decadriver/deca_params_init.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

