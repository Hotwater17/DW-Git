/*
 * platform_I2C.c
 *
 *  Created on: 20 maj 2019
 *      Author: Hotwater
 */

#include "platform_I2C.h"

extern I2C_HandleTypeDef hi2c1;
/*
 * @brief Initializes I2C interface for BME280 sensor
 */
void TPH_I2C_Init()
{
	MX_I2C1_Init();
}

/*
 * @brief Delay function for BME280 sensor
 */
void TPH_Delay(uint32_t period)
{
	HAL_Delay(period);
}
/*
 * @brief Reads register from BME280 sensor
 */
int8_t TPH_I2C_Read(uint8_t devId, uint8_t regAddr, uint8_t *regData, uint16_t length)
{
	int8_t result = 0;
	HAL_I2C_Mem_Read(&hi2c1, devId, regAddr, I2C_MEMADD_SIZE_8BIT, regData, length, 1000);
	return result;
}


/*
 * @brief Writes to register of BME280 sensor
 */
int8_t TPH_I2C_Write(uint8_t devId, uint8_t regAddr, uint8_t *regData, uint16_t length)
{
	int8_t result = 0;
	HAL_I2C_Mem_Write(&hi2c1, devId, regAddr, I2C_MEMADD_SIZE_8BIT, regData, length, 1000);
	return result;
}

/*
 * @brief Initializes I2C interface for LSM9DS1 sensor
 */
void IMU_I2C_Init()
{
	MX_I2C1_Init();
}

/*
 * @brief Reads register from LSM9DS1 sensor
 */
int32_t IMU_I2C_Read(void *handle, uint8_t regAddr, uint8_t *regData, uint16_t length)
{
	int8_t result = 0;
	uint8_t *i2c_address = handle;
	result = HAL_I2C_Mem_Read(&hi2c1, *i2c_address, regAddr, I2C_MEMADD_SIZE_8BIT, regData, length, 1000);
	return result;
}

/*
 * @brief Writes to register of LSM9DS1 sensor
 */
int32_t IMU_I2C_Write(void *handle, uint8_t regAddr, uint8_t *regData, uint16_t length)
{
	int8_t result = 0;
	uint8_t *i2c_address = handle;
	result = HAL_I2C_Mem_Write(&hi2c1, *i2c_address, regAddr, I2C_MEMADD_SIZE_8BIT, regData, length, 1000);
	return result;
}
