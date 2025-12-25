/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f0xx_hal.h"

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
#define VIN_ADC_Pin GPIO_PIN_1
#define VIN_ADC_GPIO_Port GPIOA
#define CS_Pin GPIO_PIN_4
#define CS_GPIO_Port GPIOA
#define RD_Pin GPIO_PIN_5
#define RD_GPIO_Port GPIOA
#define WR_Pin GPIO_PIN_6
#define WR_GPIO_Port GPIOA
#define DAT_Pin GPIO_PIN_7
#define DAT_GPIO_Port GPIOA
#define IRQ_EXTI0_Pin GPIO_PIN_0
#define IRQ_EXTI0_GPIO_Port GPIOB
#define GM_EN_Pin GPIO_PIN_1
#define GM_EN_GPIO_Port GPIOB
#define PIEZO_Pin GPIO_PIN_2
#define PIEZO_GPIO_Port GPIOB
#define GM_G_TIM1_Pin GPIO_PIN_8
#define GM_G_TIM1_GPIO_Port GPIOA
#define BCKL_Pin GPIO_PIN_9
#define BCKL_GPIO_Port GPIOA
#define VIBR_Pin GPIO_PIN_10
#define VIBR_GPIO_Port GPIOA
#define GM_BG_TIM1_Pin GPIO_PIN_11
#define GM_BG_TIM1_GPIO_Port GPIOA
#define GM_G_TIM2_Pin GPIO_PIN_15
#define GM_G_TIM2_GPIO_Port GPIOA
#define GM_BG_TIM2_Pin GPIO_PIN_3
#define GM_BG_TIM2_GPIO_Port GPIOB
#define S3_Pin GPIO_PIN_4
#define S3_GPIO_Port GPIOB
#define S1_Pin GPIO_PIN_5
#define S1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
