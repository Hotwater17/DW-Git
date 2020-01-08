/*
 * sensors.h
 *
 *  Created on: 3 cze 2019
 *      Author: Hotwater
 */


#include "lsm9ds1_reg.h"

#include "bme280.h"
#include "platform_I2C.h"

#ifndef SENSORS_H_
#define SENSORS_H_

/*
typedef struct
{
	int16_t ax;
	int16_t ay;
	int16_t az;
	int16_t gx;
	int16_t gy;
	int16_t gz;
	int16_t mx;
	int16_t my;
	int16_t mz;
}IMU_Data_t;
*/
#ifdef USETPH
int8_t TPH_Init(struct bme280_dev *device);
int8_t TPH_Get_Data(struct bme280_dev *device, struct bme280_data *data);

#endif

#ifdef USEIMU
/*
int8_t IMU_Init(lsm9ds1_ctx_t *magDev, lsm9ds1_ctx_t *imuDev, lsm9ds1_id_t *idStruct);
int8_t IMU_Get_Data(lsm9ds1_ctx_t *magDev, lsm9ds1_ctx_t *imuDev, lsm9ds1_status_t *statusReg, IMU_Data_t *data);
*/
#endif


#endif /* SENSORS_H_ */
