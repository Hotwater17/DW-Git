/*
 * sensors.c
 *
 *  Created on: 3 cze 2019
 *      Author: Hotwater
 */



#include "sensors.h"





#ifdef USETPH



int8_t TPH_Init(struct bme280_dev *device)
{
	  //struct bme280_dev TPH;
	  int8_t rslt = BME280_E_DEV_NOT_FOUND;
	  uint8_t settings_sel;
	  //TPH.dev_id = BME280_I2C_ADDR_SEC;
	  device->dev_id = 0xEE; //TODO: TUTAJ TEN ADRES! Przesun ten z api moze o 1 w lewo lub zostaw 0xEE
	  device->intf = BME280_I2C_INTF;
	  device->read = TPH_I2C_Read;
	  device->write = TPH_I2C_Write;
	  device->delay_ms = TPH_Delay;
	  TPH_I2C_Init();
	  rslt = bme280_init(device);
	  if(rslt == BME280_OK)
	  {
		  for(uint8_t i = 0; i < 10; i++)
		  {
			  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			  HAL_Delay(100);
		  }
	  }
	  else
	  {
		  for(uint8_t i = 0; i < 6; i++)
		  {
			  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			  HAL_Delay(500);
		  }
	  }
	  device->settings.osr_h = BME280_OVERSAMPLING_2X;
	  device->settings.osr_p = BME280_OVERSAMPLING_2X;
	  device->settings.osr_t = BME280_OVERSAMPLING_2X;
	  device->settings.filter = BME280_FILTER_COEFF_8;

	  settings_sel = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL;

	  rslt = bme280_set_sensor_settings(settings_sel, device);
	  return rslt;
}

int8_t TPH_Get_Data(struct bme280_dev *device, struct bme280_data *data)
{
	int8_t state = BME280_E_DEV_NOT_FOUND;
	state = bme280_set_sensor_mode(BME280_FORCED_MODE, device);
	HAL_Delay(20);
	state |= bme280_get_sensor_data(BME280_ALL, data, device);

	return state;
}

#endif

#ifndef USEIMU

/*

#include "platform_I2C.h"
#include "platform_I2C.c"
#include "bme280.h"
#include "bme280.c"
#include "selftest/bme280_selftest.h"
#include "selftest/bme280_selftest.c"
#include "lsm9ds1_reg.h"
#include "lsm9ds1_reg.c"
#include "sensors.c"
*/
/*
int8_t IMU_Init(lsm9ds1_ctx_t *magDev, lsm9ds1_ctx_t *imuDev, lsm9ds1_id_t *idStruct)
{
	  int8_t result = 0;
	  uint8_t i2c_add_mag = LSM9DS1_MAG_I2C_ADD_H;
	  magDev->write_reg = IMU_I2C_Write;
	  magDev->read_reg = IMU_I2C_Read;
	  magDev->handle = (void*)&i2c_add_mag;

	  // Initialize magnetic sensors driver interface
	  uint8_t i2c_add_imu = LSM9DS1_IMU_I2C_ADD_H;
	  imuDev->write_reg = IMU_I2C_Write;
	  imuDev->read_reg = IMU_I2C_Read;
	  imuDev->handle = (void*)&i2c_add_imu;

	  lsm9ds1_dev_id_get(magDev, imuDev, idStruct);

	  if (idStruct->imu != LSM9DS1_IMU_ID || idStruct->mag != LSM9DS1_MAG_ID)
	  {
		  result = -1;

	  }

	  uint8_t rst;
	  lsm9ds1_dev_reset_set(magDev, imuDev, PROPERTY_ENABLE);
	  do {
	    lsm9ds1_dev_reset_get(magDev, imuDev, &rst);
	  } while (rst);

	  // Enable Block Data Update
	  lsm9ds1_block_data_update_set(magDev, imuDev, PROPERTY_ENABLE);

	  // Set full scale
	  lsm9ds1_xl_full_scale_set(imuDev, LSM9DS1_4g);
	  lsm9ds1_gy_full_scale_set(imuDev, LSM9DS1_2000dps);
	  lsm9ds1_mag_full_scale_set(magDev, LSM9DS1_16Ga);

	  // Configure filtering chain - See datasheet for filtering chain details
	  //Accelerometer filtering chain
	  lsm9ds1_xl_filter_aalias_bandwidth_set(imuDev, LSM9DS1_AUTO);
	  lsm9ds1_xl_filter_lp_bandwidth_set(imuDev, LSM9DS1_LP_ODR_DIV_50);
	  lsm9ds1_xl_filter_out_path_set(imuDev, LSM9DS1_LP_OUT);
	  // Gyroscope filtering chain
	  lsm9ds1_gy_filter_lp_bandwidth_set(imuDev, LSM9DS1_LP_ULTRA_LIGHT);
	  lsm9ds1_gy_filter_hp_bandwidth_set(imuDev, LSM9DS1_HP_MEDIUM);
	  lsm9ds1_gy_filter_out_path_set(imuDev, LSM9DS1_LPF1_HPF_LPF2_OUT);

	  // Set Output Data Rate / Power mode
	  lsm9ds1_imu_data_rate_set(imuDev, LSM9DS1_IMU_59Hz5);
	  lsm9ds1_mag_data_rate_set(magDev, LSM9DS1_MAG_UHP_10Hz);
	  return result;
}

int8_t IMU_Get_Data(lsm9ds1_ctx_t *magDev, lsm9ds1_ctx_t *imuDev, lsm9ds1_status_t *statusReg, IMU_Data_t *data)
{
	axis3bit16_t gyro;
	axis3bit16_t accel;
	axis3bit16_t mag;
	lsm9ds1_dev_status_get(magDev, imuDev, statusReg);

	 if((statusReg->status_imu.xlda) && (statusReg->status_imu.gda))
	  {
		  //lsm9ds1_acceleration_raw_get(imuDev, accel.u8bit);
		  //lsm9ds1_angular_rate_raw_get(imuDev, gyro.u8bit);

		  lsm9ds1_acceleration_raw_get(imuDev, accel.i16bit);
		  lsm9ds1_angular_rate_raw_get(imuDev, gyro.i16bit);
		  data->ax = accel.i16bit[0];
		  data->ay = accel.i16bit[1];
		  data->az = accel.i16bit[2];

		  data->gx = gyro.i16bit[0];
		  data->gy = gyro.i16bit[1];
		  data->gz = gyro.i16bit[2];

	  }
    if(statusReg->status_mag.zyxda)
    {
  	  lsm9ds1_magnetic_raw_get(magDev, mag.u8bit);

  	  data->mx = mag.i16bit[0];
  	  data->my = mag.i16bit[1];
  	  data->mz = mag.i16bit[2];
    }

    return 0;
}
*/
#endif
