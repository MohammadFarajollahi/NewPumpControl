/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define Rele1_Pin GPIO_PIN_5
#define Rele1_GPIO_Port GPIOA
#define Rele2_Pin GPIO_PIN_6
#define Rele2_GPIO_Port GPIOA
#define In__Pin GPIO_PIN_12
#define In__GPIO_Port GPIOB
#define in__Pin GPIO_PIN_13
#define in__GPIO_Port GPIOB
#define Remot4_Pin GPIO_PIN_14
#define Remot4_GPIO_Port GPIOB
#define Remot3_Pin GPIO_PIN_15
#define Remot3_GPIO_Port GPIOB
#define MC60_Start_Pin GPIO_PIN_8
#define MC60_Start_GPIO_Port GPIOA
#define Remot2_Pin GPIO_PIN_11
#define Remot2_GPIO_Port GPIOA
#define Remot1_Pin GPIO_PIN_12
#define Remot1_GPIO_Port GPIOA
#define WC_Pin GPIO_PIN_5
#define WC_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
