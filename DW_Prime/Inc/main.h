/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_14
#define LED_GPIO_Port GPIOC
#define BUT_Pin GPIO_PIN_0
#define BUT_GPIO_Port GPIOA
#define STATUS_LED_Pin GPIO_PIN_2
#define STATUS_LED_GPIO_Port GPIOA
#define DW_IRQn_Pin GPIO_PIN_0
#define DW_IRQn_GPIO_Port GPIOB
#define DW_IRQn_EXTI_IRQn EXTI0_IRQn
#define UART_TX_Pin GPIO_PIN_10
#define UART_TX_GPIO_Port GPIOB
#define UART_RX_Pin GPIO_PIN_11
#define UART_RX_GPIO_Port GPIOB
#define IR_Pin GPIO_PIN_12
#define IR_GPIO_Port GPIOB
#define DW_SCK_Pin GPIO_PIN_13
#define DW_SCK_GPIO_Port GPIOB
#define DW_MISO_Pin GPIO_PIN_14
#define DW_MISO_GPIO_Port GPIOB
#define DW_MOSI_Pin GPIO_PIN_15
#define DW_MOSI_GPIO_Port GPIOB
#define DW_RESET_Pin GPIO_PIN_8
#define DW_RESET_GPIO_Port GPIOA
#define DW_NSS_Pin GPIO_PIN_9
#define DW_NSS_GPIO_Port GPIOA
#define DW_WKUP_Pin GPIO_PIN_10
#define DW_WKUP_GPIO_Port GPIOA
#define J_TMS_Pin GPIO_PIN_13
#define J_TMS_GPIO_Port GPIOA
#define J_TCK_Pin GPIO_PIN_14
#define J_TCK_GPIO_Port GPIOA
#define J_TDI_Pin GPIO_PIN_15
#define J_TDI_GPIO_Port GPIOA
#define J_TDO_Pin GPIO_PIN_3
#define J_TDO_GPIO_Port GPIOB
#define J_TRST_Pin GPIO_PIN_4
#define J_TRST_GPIO_Port GPIOB
#define IMU_SCL_Pin GPIO_PIN_6
#define IMU_SCL_GPIO_Port GPIOB
#define IMU_SDA_Pin GPIO_PIN_7
#define IMU_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

// 0 - unused, 1 - used

#define USE_LEDS 0
#define USE_SWITCH 0
#define USE_LCD 0
#define USE_USB 0

//#define UART_BLINK
//#define DELAY_CALIBRATION

#define ANCHOR_NUMBER 1

#define POS_FUNCTIONS
#define TAG
#define NUCLEO

#ifndef TAG
#define ANCHOR
#endif

#ifndef TAG

#define USEIMU
#define USETPH
#endif


#define LED_ACTIVE_STATE 1
#define BUT_PRESSED 0
/*
#define DW_IRQn_Pin GPIO_PIN_0
#define DW_IRQn_GPIO_Port GPIOB
#define DW_IRQn_EXTI_IRQn EXTI0_IRQn


#define IR_GPIO_Port GPIOB
#define IR_Pin GPIO_PIN_12

#define LED_ACTIVE_STATE 1

#define DW_WUP_Pin GPIO_PIN_10
#define DW_WUP_GPIO_Port GPIOA

#define DW_RESET_Pin GPIO_PIN_8
#define DW_RESET_GPIO_Port GPIOA

#define LED_GPIO_Port GPIOC
#define LED_Pin GPIO_PIN_14

#define LED_ACTIVE_STATE 1



#define BUT_GPIO_Port GPIOA
#define BUT_Pin GPIO_PIN_0
#define BUT_PRESSED 0

#define UART_TX_Pin GPIO_PIN_10
#define UART_TX_GPIO_Port GPIOB
#define UART_RX_Pin GPIO_PIN_11
#define UART_RX_GPIO_Port GPIOB

#define UART2_RX_GPIO_Port GPIOA
#define UART2_RX_Pin GPIO_PIN_3
#define UART2_TX_GPIO_Port GPIOA
#define UART2_TX_Pin GPIO_PIN_2

#define DW_SCK_Pin GPIO_PIN_13
#define DW_SCK_GPIO_Port GPIOB
#define DW_MISO_Pin GPIO_PIN_14
#define DW_MISO_GPIO_Port GPIOB
#define DW_MOSI_Pin GPIO_PIN_15
#define DW_MOSI_GPIO_Port GPIOB






#define DW_NSS_Pin GPIO_PIN_9
#define DW_NSS_GPIO_Port GPIOA


#define J_TMS_Pin GPIO_PIN_13
#define J_TMS_GPIO_Port GPIOA
#define J_TCK_Pin GPIO_PIN_14
#define J_TCK_GPIO_Port GPIOA
#define J_TDI_Pin GPIO_PIN_15
#define J_TDI_GPIO_Port GPIOA
#define J_TDO_Pin GPIO_PIN_3
#define J_TDO_GPIO_Port GPIOB
#define J_TRST_Pin GPIO_PIN_4
#define J_TRST_GPIO_Port GPIOB
#define IMU_SCL_Pin GPIO_PIN_6
#define IMU_SCL_GPIO_Port GPIOB
#define IMU_SDA_Pin GPIO_PIN_7
#define IMU_SDA_GPIO_Port GPIOB
*/
#define dwhspi hspi2
/* MG: UNUSED
#define LCD_RW_Pin GPIO_PIN_10
#define LCD_RW_GPIO_Port GPIOB
#define LCD_RS_Pin GPIO_PIN_11
#define LCD_RS_GPIO_Port GPIOB
#define LCD_NSS_Pin GPIO_PIN_12
#define LCD_NSS_GPIO_Port GPIOB
#define LCD_SCK_Pin GPIO_PIN_13
#define LCD_SCK_GPIO_Port GPIOB
#define LCD_MISO_Pin GPIO_PIN_14
#define LCD_MISO_GPIO_Port GPIOB
#define LCD_MOSI_Pin GPIO_PIN_15
#define LCD_MOSI_GPIO_Port GPIOB
#define LED5_Pin GPIO_PIN_6
#define LED5_GPIO_Port GPIOC
#define LED6_Pin GPIO_PIN_7
#define LED6_GPIO_Port GPIOC
#define LED7_Pin GPIO_PIN_8
#define LED7_GPIO_Port GPIOC
#define LED8_Pin GPIO_PIN_9
#define LED8_GPIO_Port GPIOC
#define USB_VBUS_Pin GPIO_PIN_9
#define USB_VBUS_GPIO_Port GPIOA
#define USB_ID_Pin GPIO_PIN_10
#define USB_ID_GPIO_Port GPIOA
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA

*/

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
