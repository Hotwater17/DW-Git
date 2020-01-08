/*
 * config.h
 *
 *  Created on: 29 kwi 2019
 *      Author: Hotwater
 */

#include "main.h"
#include "stm32f1xx_hal.h"

#ifndef CONFIG_H_
#define CONFIG_H_

ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart3;

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_SPI2_Init(void);
void MX_USART3_UART_Init(void);
void MX_I2C1_Init(void);
void MX_RTC_Init(void);
void MX_TIM2_Init(void);
void MX_ADC1_Init(void);

#endif /* CONFIG_H_ */
