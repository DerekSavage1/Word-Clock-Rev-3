/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../../Drivers/WS2812B/WS2812B.h"
#include "../../Drivers/Numeric_Display/Numeric_Display.h"
#include "Bitmap_Display.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
  // Enumeration for different states
  typedef enum {
      SLEEP,
	  WAKE,
	  SELECT,
      SET_HOURS,
	  SET_MINUTES,
      SET_COLOR,
      SET_BRIGHTNESS,
	  SET_MONTH,
	  SET_DAY,
	  SET_YEAR,
  } DeviceState;


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LED_SET   136
#define LED_DELETE 137
#define LED_SET_TIME 141
#define LED_SET_COLOR 140
#define LED_SET_ANNIVERSARY 139
#define LED_SET_BIRTHDAY 138
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
DMA_HandleTypeDef hdma_tim1_ch1;

/* USER CODE BEGIN PV */
volatile uint32_t counter = 0;
RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;
volatile uint16_t color = 0;
volatile uint16_t brightness = 50;
volatile DeviceState currentState = SLEEP;
volatile int sensitivity = 10;
char displayStr[128];
bool userIsConfiguring = false;
volatile uint32_t tick = 0;
uint16_t refreshRate = 1000;
bool stateChangeRequest = false;
uint32_t lastTick = 0;
uint32_t delayMs = 375;
bool isOff = true;
bool isSet = true;
uint8_t lastLED = 0xFF;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM1_Init(void);
static void MX_RTC_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void Blink_LED(uint16_t LED, uint32_t color) {

	if(LED != lastLED) {
		Set_LED_Hex(lastLED, 0);
		lastLED = LED;
	}

	if (HAL_GetTick() - lastTick >= delayMs) {

		//Toggle LED
		if(isOff){
			Set_LED_Hex(LED, color);
		} else {
			Set_LED_Hex(LED, 0);
		}

		isOff = !isOff;
		lastTick = HAL_GetTick();
	}
}

uint16_t clampValue(uint16_t value, uint16_t minVal, uint16_t maxVal) {
    if (abs(0xFFFF - value) < abs(maxVal - value)) {
  	  return minVal;
    } else {
        // Normal range (does not wrap around)
        if (value < minVal) return minVal;
        if (value > maxVal) return maxVal;
        return value;
    }
}

bool userSelectingFeature = true; // True when in SELECT state to decide what feature to adjust

void switchState(void) {
    switch(currentState) {
        case SLEEP:
            currentState = WAKE;
            break;
        case WAKE:
            currentState = SELECT;
            break;
        case SELECT:
        	switch((counter / sensitivity)){
        	case 2:
        		counter = sTime.Hours * sensitivity;
        		currentState = SET_HOURS;
        		break;
        	case 3:
        		currentState = SET_COLOR;
        		counter = color * sensitivity;
        		break;
        	}
            break;
        case SET_HOURS:
        	counter = sTime.Minutes * sensitivity;
        	Set_LED_Hex(141, getRainbowColor(color));
        	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
        	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
            currentState = SET_MINUTES; // After setting hours, set minutes
            break;
        case SET_MINUTES:
        	counter = sDate.Month * sensitivity;
        	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
        	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
            currentState = SET_MONTH; // Return to SLEEP after setting time
            break;
        case SET_MONTH:
        	counter = sDate.Date * sensitivity;
        	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
        	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
        	currentState = SET_DAY;
        	break;
        case SET_DAY:
        	counter = sDate.Year * sensitivity;
        	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
        	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
        	currentState = SET_YEAR;
        	break;
        case SET_YEAR:
        	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
        	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
        	currentState = SLEEP;
        	break;
        case SET_COLOR:
        	counter = brightness * sensitivity;
            currentState = SET_BRIGHTNESS; // After color, set brightness
            break;
        case SET_BRIGHTNESS:
            currentState = SLEEP; // Return to SLEEP after setting LED features
            break;
        default:
            // If state is somehow unhandled, default back to SLEEP as a failsafe
            currentState = SLEEP;
            break;
    }
}

void checkButtonPress(void) {
    static GPIO_PinState lastButtonState = GPIO_PIN_SET; // Assume button is initially not pressed (HIGH due to pull-up).
    GPIO_PinState currentButtonState;

    // Read the current state of the button GPIO pin.
    currentButtonState = HAL_GPIO_ReadPin(GPIOB, BUTTON_Pin);

    // Check if button state has transitioned from HIGH to LOW.
    if (lastButtonState == GPIO_PIN_SET && currentButtonState == GPIO_PIN_RESET) {
        // Button was pressed - perform actions here.
        switchState(); // Call the state switch function only on the transition.
    }

    // Update the last button state.
    lastButtonState = currentButtonState;
}




void SetHours() {
    Set_LED(136, 100, 100, 100);
    counter = clampValue(counter, 0, 23 * sensitivity); //23 hours
    sTime.Hours = counter / sensitivity;
    snprintf(displayStr, sizeof(displayStr), "%02u:%02u", sTime.Hours, sTime.Minutes);
}

void SetMinutes() {
    counter = clampValue(counter, 0, 59 * sensitivity); //59 minutes
    sTime.Minutes = counter / sensitivity;
    snprintf(displayStr, sizeof(displayStr), "%02u:%02u", sTime.Hours, sTime.Minutes);
}

int SetMonth() {
    counter = clampValue(counter, 0, 12 * sensitivity); //12 months
    sDate.Month = counter / sensitivity;
    snprintf(displayStr, sizeof(displayStr), "%02u%02u", sDate.Month, sDate.Date);
    return counter / sensitivity;
}

int SetDay() {
    counter = clampValue(counter, 0, 31 * sensitivity); //31 days
    //FIXME: user could enter February 31 which is wrong
    sDate.Date = counter / sensitivity;
    snprintf(displayStr, sizeof(displayStr), "%02u%02u", sDate.Month, sDate.Date);
    return counter / sensitivity;
}

int SetYear() {
    counter = clampValue(counter, 0, 3000 * sensitivity); //12 months
    sDate.Year = counter / sensitivity;
    snprintf(displayStr, sizeof(displayStr), "%04u", sDate.Year);
    return counter / sensitivity;
}

void SetColor() {
    counter = clampValue(counter, 0, 16 * sensitivity); //16 color presets
    color = counter / sensitivity;
    snprintf(displayStr, sizeof(displayStr), "%04u", color);
    Set_LED_Hex(136, getRainbowColor(color));
    Set_LED_Hex(140, getRainbowColor(color));
}


void SetBrightness() {
    counter = clampValue(counter, 1, 100 * (sensitivity / 2)); //1-100% brightness
    brightness = counter / (sensitivity / 2);
    snprintf(displayStr, sizeof(displayStr), "%04u", brightness);
}

void Select() {
	counter = clampValue(counter, 0, 3 * sensitivity);
	Set_LED_Hex(LED_SET + (!isSet), getRainbowColor(color));
	Blink_LED(LED_SET_TIME - (counter/sensitivity), getRainbowColor(color));
	snprintf(displayStr, sizeof(displayStr), "%04u", counter/sensitivity);
}

void Wake() {
	counter = clampValue(counter, 0, 1);
	Blink_LED(LED_SET + counter, getRainbowColor(color));
	snprintf(displayStr, sizeof(displayStr), "%04u", LED_SET + counter);

	//counter = 0 -> isSet
	//counter = 1 -> isNotSet
	isSet = !counter;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */


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
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_RTC_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL); // Start the encoder interface


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  counter = __HAL_TIM_GET_COUNTER(&htim3);

	  checkButtonPress();
	  if(stateChangeRequest){
		  switchState();
		  stateChangeRequest = !stateChangeRequest;
	  }

	// get time and get date must both be called
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);


	switch(currentState) {
		case SLEEP:
			snprintf(displayStr, 4, "%s", "\0");
			break;
		case WAKE:
			Wake();
			break;
		case SELECT:
			Select();
			break;
		case SET_HOURS:
			SetHours();
			break;
		case SET_MINUTES:
			SetMinutes();
			break;
		case SET_MONTH:
			SetMonth();
			break;
		case SET_DAY:
			SetDay();
			break;
		case SET_YEAR:
			SetYear();
			break;
		case SET_COLOR:
			SetColor();
			break;
		case SET_BRIGHTNESS:
			SetBrightness();
			break;
	}



	__HAL_TIM_SET_COUNTER(&htim3, counter);
	Segment_Display(displayStr);

//	display_time(sTime.Hours, sTime.Minutes);
//	display_bmp(color, brightness);
//	WS2812B_Send(&htim1);
//	clear_display_buffer();




  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 7;
  sTime.Minutes = 15;
  sTime.Seconds = 50;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_TUESDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 23;
  sDate.Year = 24;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 90-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
  sConfig.IC1Polarity = TIM_ICPOLARITY_FALLING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 0;
  sConfig.IC2Polarity = TIM_ICPOLARITY_FALLING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 0;
  if (HAL_TIM_Encoder_Init(&htim3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 8, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SEG_B_K_Pin|SEG_G_K_Pin|SEG_A_K_Pin|SEG_C_K_Pin
                          |SEG_F_K_Pin|DIG_4_A_Pin|DP_K_Pin|DIG_3_A_Pin
                          |LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG_E_K_Pin|DEC_A_Pin|SEG_D_K_Pin|DIG_2_A_Pin
                          |DIG_1_A_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : SEG_B_K_Pin SEG_G_K_Pin SEG_A_K_Pin SEG_C_K_Pin
                           SEG_F_K_Pin DIG_4_A_Pin DP_K_Pin DIG_3_A_Pin
                           LED_Pin */
  GPIO_InitStruct.Pin = SEG_B_K_Pin|SEG_G_K_Pin|SEG_A_K_Pin|SEG_C_K_Pin
                          |SEG_F_K_Pin|DIG_4_A_Pin|DP_K_Pin|DIG_3_A_Pin
                          |LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG_E_K_Pin DEC_A_Pin SEG_D_K_Pin DIG_2_A_Pin
                           DIG_1_A_Pin */
  GPIO_InitStruct.Pin = SEG_E_K_Pin|DEC_A_Pin|SEG_D_K_Pin|DIG_2_A_Pin
                          |DIG_1_A_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : BUTTON_Pin */
  GPIO_InitStruct.Pin = BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BUTTON_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
