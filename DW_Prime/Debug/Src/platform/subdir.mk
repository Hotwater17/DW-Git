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
Src/platform/%.o: ../Src/platform/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/Inc" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/Src/compiler" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/Src/decadriver" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/Src/platform" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/Drivers/STM32F1xx_HAL_Driver/Inc" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/Drivers/CMSIS/Include" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/BME280_driver-master" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/lsm9ds1_STdC/driver" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/UWB" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/I2C" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Hotwater/Documents/Eclipse/DW_Prime/Middlewares/ST/STM32_USB_Device_Library/Core/Inc"  -Og -g -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


