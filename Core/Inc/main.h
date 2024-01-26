/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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
#define SEG_B_K_Pin GPIO_PIN_0
#define SEG_B_K_GPIO_Port GPIOA
#define SEG_G_K_Pin GPIO_PIN_1
#define SEG_G_K_GPIO_Port GPIOA
#define SEG_A_K_Pin GPIO_PIN_2
#define SEG_A_K_GPIO_Port GPIOA
#define SEG_C_K_Pin GPIO_PIN_3
#define SEG_C_K_GPIO_Port GPIOA
#define SEG_F_K_Pin GPIO_PIN_4
#define SEG_F_K_GPIO_Port GPIOA
#define DIG_4_A_Pin GPIO_PIN_5
#define DIG_4_A_GPIO_Port GPIOA
#define DP_K_Pin GPIO_PIN_6
#define DP_K_GPIO_Port GPIOA
#define DIG_3_A_Pin GPIO_PIN_7
#define DIG_3_A_GPIO_Port GPIOA
#define SEG_E_K_Pin GPIO_PIN_0
#define SEG_E_K_GPIO_Port GPIOB
#define DEC_A_Pin GPIO_PIN_1
#define DEC_A_GPIO_Port GPIOB
#define SEG_D_K_Pin GPIO_PIN_2
#define SEG_D_K_GPIO_Port GPIOB
#define DIG_2_A_Pin GPIO_PIN_10
#define DIG_2_A_GPIO_Port GPIOB
#define DIG_1_A_Pin GPIO_PIN_12
#define DIG_1_A_GPIO_Port GPIOB
#define ENC_CH_A_Pin GPIO_PIN_13
#define ENC_CH_A_GPIO_Port GPIOB
#define ENC_CH_A_EXTI_IRQn EXTI15_10_IRQn
#define ENC_CH_B_Pin GPIO_PIN_14
#define ENC_CH_B_GPIO_Port GPIOB
#define ENC_CH_B_EXTI_IRQn EXTI15_10_IRQn
#define BTN_Pin GPIO_PIN_15
#define BTN_GPIO_Port GPIOB
#define BTN_EXTI_IRQn EXTI15_10_IRQn
#define LED_Pin GPIO_PIN_15
#define LED_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
