################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/platform/deca_mutex.c \
../Src/platform/deca_range_tables.c \
../Src/platform/deca_sleep.c \
../Src/platform/deca_spi.c \
../Src/platform/lcd.c \
../Src/platform/port.c 

OBJS += \
./Src/platform/deca_mutex.o \
./Src/platform/deca_range_tables.o \
./Src/platform/deca_sleep.o \
./Src/platform/deca_spi.o \
./Src/platform/lcd.o \
./Src/platform/port.o 

C_DEPS += \
./Src/platform/deca_mutex.d \
./Src/platform/deca_range_tables.d \
./Src/platform/deca_sleep.d \
./Src/platform/deca_spi.d \
./Src/platform/lcd.d \
./Src/platform/port.d 


# Each subdirectory must supply rules for building sources it contributes
Src/platform/deca_mutex.o: ../Src/platform/deca_mutex.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Inc -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/compiler" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/decadriver" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/platform" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/BME280_driver-master" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/lsm9ds1_STdC/driver" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/UWB" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/I2C" -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -Og -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/platform/deca_mutex.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/platform/deca_range_tables.o: ../Src/platform/deca_range_tables.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Inc -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/compiler" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/decadriver" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/platform" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/BME280_driver-master" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/lsm9ds1_STdC/driver" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/UWB" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/I2C" -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -Og -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/platform/deca_range_tables.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/platform/deca_sleep.o: ../Src/platform/deca_sleep.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Inc -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/compiler" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/decadriver" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/platform" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/BME280_driver-master" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/lsm9ds1_STdC/driver" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/UWB" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/I2C" -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -Og -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/platform/deca_sleep.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/platform/deca_spi.o: ../Src/platform/deca_spi.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Inc -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/compiler" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/decadriver" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/platform" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/BME280_driver-master" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/lsm9ds1_STdC/driver" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/UWB" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/I2C" -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -Og -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/platform/deca_spi.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/platform/lcd.o: ../Src/platform/lcd.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Inc -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/compiler" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/decadriver" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/platform" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/BME280_driver-master" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/lsm9ds1_STdC/driver" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/UWB" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/I2C" -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -Og -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/platform/lcd.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/platform/port.o: ../Src/platform/port.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Inc -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/compiler" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/decadriver" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Src/platform" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/BME280_driver-master" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/lsm9ds1_STdC/driver" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/UWB" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/I2C" -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/mgorywoda/Documents/GitHub/DW-Git/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -Og -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/platform/port.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

