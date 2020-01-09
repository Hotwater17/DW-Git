/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "inttypes.h"
#include "stdlib.h"
#include "config.h"
#include "Pos_functions.h"


#include "platform_I2C.h"
#include "platform_I2C.c"
#include "bme280.h"
#include "bme280.c"
#include "selftest/bme280_selftest.h"
#include "selftest/bme280_selftest.c"
#include "lsm9ds1_reg.h"
#include "lsm9ds1_reg.c"
#include "sensors.c"

#include "config.h"
#include "port.h"
#include "deca_device_api.h"
#include "deca_regs.h"
#include "deca_spi.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/


/* USER CODE BEGIN PV */
	uint32_t debugMsg = 0;
	int debugError = -1;
	uint32_t debugTimer = 0; //in 100s of us
	volatile uint16_t debugCmd = 0;
	uint32_t deviceID = 0;
	uint32_t result32;
#ifdef TAG
	uint32_t timeoutToWrite = POLL_RX_TO_RESP_TX_DLY_UUS;
#endif
	uint32_t a,b,c,d;
	dwt_rxdiag_t rxdiag;
	double globalTof, globalDistance;
    double distanceAccu = 0;
    double distanceAvg = 0;
    uint64_t distanceAvg64 = 0;
    uint64_t distanceAccu64 = 0;
	char testBuf[20] = {"\r \n Elo: "};
	uint8_t intBuf[100];
	uint8_t intBufAux[50];
	int16_t distCnt = 0;
	uint16_t newTxDelay, oldTxDelay;

	uint8_t transmitEnable = 0;
	uint8_t currentAnchor = ANCHOR_NUMBER;
	uint8_t delayVar = 1;
	uint8_t usbRxFlag = 0;
	uint8_t usbRxBuffer[40];

	uint64_t testTagDist;
#ifdef POS_FUNCTIONS
	uwb_data_t globalUWBData;
#endif

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */


void Start_Measuring_Time();
uint32_t Stop_Measuring_Time();
void Send_Timestamp(uint64_t timestamp);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


void Start_Measuring_Time()
{
	TIM2->CNT = 0;
	HAL_TIM_Base_Start(&htim2);
}

uint32_t Stop_Measuring_Time()
{
	 HAL_TIM_Base_Stop(&htim2);
	 return TIM2->CNT;
}

void Send_Timestamp(uint64_t timestamp)
{
	char uartBuffer[30];
	typedef union
	{
		uint64_t var64;
		uint32_t var32[2];
	}combined_t;

	combined_t combinedVar;
	combinedVar.var64 = timestamp;
	HAL_UART_Transmit(&huart3, uartBuffer, sprintf(uartBuffer, "%ld %ld \r \n", combinedVar.var32[1], combinedVar.var32[0]), 100U);


}

struct bme280_data TPHdata;
struct bme280_dev TPHdevice;
int8_t TPH_state = BME280_OK;
lsm9ds1_id_t whoamI;

axis3bit16_t gyro;
axis3bit16_t accel;
axis3bit16_t mag;
static lsm9ds1_status_t reg;

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

IMU_Data_t IMU_Readout;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint8_t cnt = 0;
	char startBuf[] = {"Dobry"};
	char usbBuf[20];
	GPIO_InitTypeDef ledDef;
	ledDef.Mode = GPIO_MODE_OUTPUT_PP;
	ledDef.Pin = LED_Pin;
	ledDef.Pull = GPIO_NOPULL;
	ledDef.Speed = GPIO_SPEED_FREQ_LOW;


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI2_Init();
  MX_USART3_UART_Init();
  MX_I2C1_Init();
  MX_RTC_Init();
  MX_TIM2_Init();
  MX_ADC1_Init();
  //MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  HAL_GPIO_Init(LED_GPIO_Port, &ledDef);

#ifdef NUCLEO
  ledDef.Pin = IR_Pin;
  HAL_GPIO_Init(IR_GPIO_Port, &ledDef);
#endif
  HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN1);

  GPIO_InitTypeDef butDef;
  butDef.Pin = BUT_Pin;
  butDef.Mode = GPIO_MODE_INPUT;
  butDef.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BUT_GPIO_Port, &butDef);


#ifdef POS_FUNCTIONS
#ifdef ANCHOR
  UWB_Anchor_Init();
  globalUWBData.timeout = 2750;
#endif

#ifdef TAG
  deviceID = 0xEE;
  UWB_Tag_Init();
  globalUWBData.timeout = POLL_RX_TO_RESP_TX_DLY_UUS;
  newTxDelay = TX_ANT_DLY;
  oldTxDelay = newTxDelay;
#endif

#endif

  deviceID = dwt_readdevid();
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, LED_ACTIVE_STATE);

#ifdef NUCLEO
  HAL_GPIO_WritePin(IR_GPIO_Port, IR_Pin, LED_ACTIVE_STATE);
#endif
  HAL_UART_Transmit(&huart3, startBuf, sizeof(startBuf), 100U);


#ifdef USETPH
 TPH_Init(&TPHdevice);
#endif


#ifdef USEIMU

  uint8_t i2c_add_mag = LSM9DS1_MAG_I2C_ADD_H;
  lsm9ds1_ctx_t dev_ctx_mag;
  dev_ctx_mag.write_reg = IMU_I2C_Write;
  dev_ctx_mag.read_reg = IMU_I2C_Read;
  dev_ctx_mag.handle = (void*)&i2c_add_mag;

  /* Initialize magnetic sensors driver interface */
  uint8_t i2c_add_imu = LSM9DS1_IMU_I2C_ADD_H;
  lsm9ds1_ctx_t dev_ctx_imu;
  dev_ctx_imu.write_reg = IMU_I2C_Write;
  dev_ctx_imu.read_reg = IMU_I2C_Read;
  dev_ctx_imu.handle = (void*)&i2c_add_imu;

  lsm9ds1_dev_id_get(&dev_ctx_mag, &dev_ctx_imu, &whoamI);
/*
  if (whoamI.imu != LSM9DS1_IMU_ID || whoamI.mag != LSM9DS1_MAG_ID){
    while(1){

    	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    	HAL_Delay(50);

    }
  }
*/
  uint8_t rst;
  lsm9ds1_dev_reset_set(&dev_ctx_mag, &dev_ctx_imu, PROPERTY_ENABLE);
  do {
    lsm9ds1_dev_reset_get(&dev_ctx_mag, &dev_ctx_imu, &rst);
  } while (rst);

  /* Enable Block Data Update */
  lsm9ds1_block_data_update_set(&dev_ctx_mag, &dev_ctx_imu, PROPERTY_ENABLE);

  /* Set full scale */
  lsm9ds1_xl_full_scale_set(&dev_ctx_imu, LSM9DS1_4g);
  lsm9ds1_gy_full_scale_set(&dev_ctx_imu, LSM9DS1_2000dps);
  lsm9ds1_mag_full_scale_set(&dev_ctx_mag, LSM9DS1_16Ga);

  /* Configure filtering chain - See datasheet for filtering chain details */
  /* Accelerometer filtering chain */
  lsm9ds1_xl_filter_aalias_bandwidth_set(&dev_ctx_imu, LSM9DS1_AUTO);
  lsm9ds1_xl_filter_lp_bandwidth_set(&dev_ctx_imu, LSM9DS1_LP_ODR_DIV_50);
  lsm9ds1_xl_filter_out_path_set(&dev_ctx_imu, LSM9DS1_LP_OUT);
  /* Gyroscope filtering chain */
  lsm9ds1_gy_filter_lp_bandwidth_set(&dev_ctx_imu, LSM9DS1_LP_ULTRA_LIGHT);
  lsm9ds1_gy_filter_hp_bandwidth_set(&dev_ctx_imu, LSM9DS1_HP_MEDIUM);
  lsm9ds1_gy_filter_out_path_set(&dev_ctx_imu, LSM9DS1_LPF1_HPF_LPF2_OUT);

  /* Set Output Data Rate / Power mode */
  lsm9ds1_imu_data_rate_set(&dev_ctx_imu, LSM9DS1_IMU_59Hz5);
  lsm9ds1_mag_data_rate_set(&dev_ctx_mag, LSM9DS1_MAG_UHP_10Hz);


#endif

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

#ifdef POS_FUNCTIONS
#ifdef ANCHOR

	  //d jak data.
	  //sprintf(intBuf, "d \r \n T: %ul \r \n H: %ul \r \n p: %ul \r \n", TPHdata.temperature, TPHdata.humidity, TPHdata.pressure);



	 // HAL_Delay(delayVar);
	  //UWB_Send_Data(intBuf, 50);

	  Start_Measuring_Time();

	  UWB_Anchor_Get_Distance(&globalUWBData, 1);
	  UWB_Anchor_Get_Distance(&globalUWBData, 2);
      UWB_Anchor_Get_Distance(&globalUWBData, 3);
      UWB_Anchor_Get_Distance(&globalUWBData, 4);

      dwt_readdiagnostics(&rxdiag);

      if(usbRxFlag == 1)
      {
    	  usbRxFlag = 0;

    	  newTxDelay = atoi(usbRxBuffer);
    	  CDC_Transmit_FS(intBuf, sprintf(intBuf, "Nowy delay: %d \r \n", newTxDelay));
      }

      CDC_Transmit_FS(intBuf, sprintf(intBuf, " %ld \r \n", testTagDist));

#ifdef USETPH
      TPH_Get_Data(&TPHdevice, &TPHdata);
#endif
#ifdef USEIMU



	  lsm9ds1_dev_status_get(&dev_ctx_mag, &dev_ctx_imu, &reg);
	  if ( reg.status_imu.xlda && reg.status_imu.gda)
	  {
		  lsm9ds1_acceleration_raw_get(&dev_ctx_imu, accel.i16bit);
		  lsm9ds1_angular_rate_raw_get(&dev_ctx_imu, gyro.i16bit);

		  IMU_Readout.ax = accel.i16bit[0];
		  IMU_Readout.ay = accel.i16bit[1];
		  IMU_Readout.az = accel.i16bit[2];

		  IMU_Readout.gx = gyro.i16bit[0];
		  IMU_Readout.gy = gyro.i16bit[1];
		  IMU_Readout.gz = gyro.i16bit[2];

	  }
      if(reg.status_mag.zyxda)
      {
    	  lsm9ds1_magnetic_raw_get(&dev_ctx_mag, mag.i16bit);

    	  IMU_Readout.mx = mag.i16bit[0];
    	  IMU_Readout.my = mag.i16bit[1];
    	  IMU_Readout.mz = mag.i16bit[2];


      }



#endif //USE_IMU
      debugTimer = Stop_Measuring_Time();
#ifdef DELAY_CALIBRATION
      if(oldTxDelay != newTxDelay)
      {
    	  dwt_settxantennadelay(newTxDelay);
    	  dwt_setrxantennadelay(newTxDelay);
    	  oldTxDelay = newTxDelay;
      }
#endif
#endif
#ifdef TAG
#ifdef DELAY_CALIBRATION
      for(distCnt = 0; distCnt < 100; distCnt++)
      {
          if(UWB_Tag_Get_Distance(&globalUWBData,1) != 0)
          {
        	  distCnt--;
          }
          else
          {
        	  distanceAccu += globalUWBData.uwbDistance;
        	  distanceAccu64 += globalUWBData.uwbDistance64;
          }


      }
      distanceAvg = distanceAccu/100;
      distanceAvg64 = distanceAccu64/100;
      distanceAccu64 = 0;
      distanceAccu = 0;
      CDC_Transmit_FS(intBuf, sprintf(intBuf, "%ldE-8 \r \n", distanceAvg64));
      if(usbRxFlag == 1)
      {
    	  usbRxFlag = 0;

    	  newTxDelay = atoi(usbRxBuffer);
    	  CDC_Transmit_FS(intBuf, sprintf(intBuf, "Nowy delay: %d \r \n", newTxDelay));
      }
      if(oldTxDelay != newTxDelay)
      {
    	  dwt_settxantennadelay(newTxDelay);
    	  dwt_setrxantennadelay(newTxDelay);
    	  oldTxDelay = newTxDelay;
      }
#endif

Start_Measuring_Time();

#ifndef DELAY_CALIBRATION
/*
if(usbRxFlag == 1)
{
	  usbRxFlag = 0;
	  if(usbRxBuffer[0] == 'g')
	  {
		  transmitEnable = 1;
		  CDC_Transmit_FS(intBuf, sprintf(intBuf, "GO \r \n"));


	  }

	  if(usbRxBuffer[0] == 'h')
	  {
		  transmitEnable = 0;
		  CDC_Transmit_FS(intBuf, sprintf(intBuf, "HALT \r \n"));
	  }
	  if(usbRxBuffer[0] == 'c')
	  {
		  currentAnchor = (usbRxBuffer[1]-48); //ASCII 1-4
		  CDC_Transmit_FS(intBuf, sprintf(intBuf, "CURRENT ANCHOR: %i \r \n", currentAnchor));
	  }
      if(usbRxBuffer[0] == 'a')
      {
    	  CDC_Transmit_FS(intBuf, sprintf(intBuf, "CURRENT ANCHOR: %i \r \n", currentAnchor));
    	  for(uint8_t ledCnt = 0; ledCnt < 10; ledCnt++)
    	  {
			  HAL_GPIO_TogglePin(IR_GPIO_Port, IR_Pin);
			  HAL_Delay(100);
    	  }


      }

}
*/


if(UWB_Tag_Get_Distance(&globalUWBData, currentAnchor) == 2)
{

	//Tutaj raczej odczytaj bufor a nie probuj znowu receive robic.
	//if(UWB_Get_Data(intBuf) == 0) <- odczyt z bufora tylko.
	//CDC_Transmit_FS(intBuf, 40);
}
if(UWB_Tag_Get_Distance(&globalUWBData, currentAnchor) == 0)
{

/*
if(UWB_Get_Data(intBuf) == 0)
{
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	CDC_Transmit_FS(intBuf, 40);
}
*/
debugTimer = Stop_Measuring_Time();
//HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);


if(transmitEnable == 1)
{

	//CDC_Transmit_FS(intBuf, sprintf(intBuf, "\r \n %ldE-9 \r \n", globalUWBData.uwbDistance64));
	HAL_UART_Transmit(&huart3, intBuf, sprintf(intBuf, "\r \n %ldE-9 \r \n", globalUWBData.uwbDistance64), 100U);
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, !LED_ACTIVE_STATE);
}
else
{
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, LED_ACTIVE_STATE);
}



#ifdef USETPH

TPH_Get_Data(&TPHdevice, &TPHdata);


#endif //USE_TPH

#ifdef USEIMU



	  lsm9ds1_dev_status_get(&dev_ctx_mag, &dev_ctx_imu, &reg);
	  if ( reg.status_imu.xlda && reg.status_imu.gda)
	  {
		  lsm9ds1_acceleration_raw_get(&dev_ctx_imu, accel.i16bit);
		  lsm9ds1_angular_rate_raw_get(&dev_ctx_imu, gyro.i16bit);

		  IMU_Readout.ax = accel.i16bit[0];
		  IMU_Readout.ay = accel.i16bit[1];
		  IMU_Readout.az = accel.i16bit[2];

		  IMU_Readout.gx = gyro.i16bit[0];
		  IMU_Readout.gy = gyro.i16bit[1];
		  IMU_Readout.gz = gyro.i16bit[2];

	  }
      if(reg.status_mag.zyxda)
      {
    	  lsm9ds1_magnetic_raw_get(&dev_ctx_mag, mag.i16bit);

    	  IMU_Readout.mx = mag.i16bit[0];
    	  IMU_Readout.my = mag.i16bit[1];
    	  IMU_Readout.mz = mag.i16bit[2];


      }



#endif //USE_IMU
}

#endif //DELAY_CALIBRATION
#endif
#endif

#ifdef UART_BLINK
      HAL_UART_Receive(&huart3, intBuf, 15, 10U);
      if(intBuf[0] == 'a')
      {
    	  HAL_UART_Transmit(&huart3, intBuf, sprintf(intBuf, "Zamigano \r \n"), 10U);
    	  for(uint8_t ledCnt = 0; ledCnt < 10; ledCnt++)
    	  {
			  HAL_GPIO_TogglePin(IR_GPIO_Port, IR_Pin);
			  HAL_Delay(100);
    	  }


      }
      else if(intBuf[0] == 'd')
      {
    	  result32 = atoi(&intBuf[2]);
    	  dwt_settxantennadelay(result32);

      }
      //flush
      for(uint8_t cnt = 0; cnt < 100; cnt++)
      {
    	  intBuf[cnt] = 0;
      }

/*
      if(oldTxDelay != newTxDelay)
      {
    	  dwt_settxantennadelay(newTxDelay);
    	  oldTxDelay = newTxDelay;
      }
*/
#endif

  }
  /* USER CODE END 3 */
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
