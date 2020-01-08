/*
 * platformI2c.h
 *
 *  Created on: 20 maj 2019
 *      Author: Hotwater
 */

#ifndef I2C_PLATFORMI2C_H_
#define I2C_PLATFORMI2C_H_

void TPH_I2C_Init();
void TPH_Delay(uint32_t period);
int8_t TPH_I2C_Read(uint8_t devId, uint8_t regAddr, uint8_t *regData, uint16_t length);
int8_t TPH_I2C_Write(uint8_t devId, uint8_t regAddr, uint8_t *regData, uint16_t length);

void IMU_I2C_Init();
int32_t IMU_I2C_Read(void *handle, uint8_t regAddr, uint8_t *regData, uint16_t length);
int32_t IMU_I2C_Write(void *handle, uint8_t regAddr, uint8_t *regData, uint16_t length);

#endif /* I2C_PLATFORMI2C_H_ */
