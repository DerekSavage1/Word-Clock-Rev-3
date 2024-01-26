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
#include "matrix.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../../Drivers/WS2812B/WS2812B.h"
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
RTC_HandleTypeDef hrtc;

TIM_HandleTypeDef htim1;
DMA_HandleTypeDef hdma_tim1_ch1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM1_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint32_t getRainbowColor(uint8_t colorOption) {
    switch (colorOption) {
        case 1:
            return 0xFF0000; // Red
        case 2:
            return 0xFF7F00; // Orange
        case 3:
            return 0xFFFF00; // Yellow
        case 4:
            return 0x7FFF00; // Yellow-Green
        case 5:
            return 0x00FF00; // Green
        case 6:
            return 0x00FF7F; // Spring Green
        case 7:
            return 0x00FFFF; // Cyan
        case 8:
            return 0x007FFF; // Sky Blue
        case 9:
            return 0x0000FF; // Blue
        case 10:
            return 0x7F00FF; // Violet
        case 11:
            return 0xFF00FF; // Magenta
        case 12:
            return 0xFF007F; // Rose
        case 13:
            return 0xFF1493; // Deep Pink
        case 14:
            return 0xC71585; // Medium Violet Red
        case 15:
            return 0x800080; // Purple
        case 16:
            return 0x8B008B; // Dark Magenta
        default:
            return 0xFFFFFF; // Default to White if an unexpected value is provided
    }
}

volatile int32_t a_count = 0;
volatile int32_t b_count = 0;



const uint16_t * minuteBitmaps[] = {
    MINUTE_FIVE,
    MINUTE_TEN,
    MINUTE_FIFTEEN,
    MINUTE_TWENTY,
    MINUTE_TWENTYFIVE,
    MINUTE_THIRTY // This is only used if we exactly hit the 30-minute mark
};

unsigned char displayBuffer[12][11] = {0}; // Adjust the buffer to be 12 rows by 11 columns

void clear_display_buffer() {
    for (int row = 0; row < 12; row++) {
        for (int col = 0; col < 11; col++) {
            displayBuffer[row][col] = 0; // Clear the bit in the display buffer
        }
    }
}

void add_bmp(const uint16_t bmp[12]) {
    for (int row = 0; row < 12; row++) { // Loop over each row
        for (int col = 0; col < 11; col++) { // Loop over the first 11 columns
            if ((bmp[row] & (1 << col)) != 0) { // Check if the bit is set in bmp at (row, col)
                displayBuffer[row][col] |= 1; // Set the bit in the display buffer
            }
        }
    }
}

void display_bmp(uint32_t color) {
    // Extract the red, green, and blue components from the color
    uint8_t red = (color >> 16) & 0xFF;
    uint8_t green = (color >> 8) & 0xFF;
    uint8_t blue = color & 0xFF;

    for (int row = 0; row < 12; row++) {
        for (int col = 0; col < 11; col++) {
            if (displayBuffer[row][col] & 1) { // Check if the bit is set
                // Set the LED to the specified color
                Set_LED((row * 11) + col, red, green, blue);
            } else {
                // Turn the LED off
                Set_LED((row * 11) + col, 0, 0, 0);
            }
        }
    }
}



void display_time(int hour, int minute) {
	add_bmp(BMP_ITS);
    // Round down to the nearest five minutes
    minute = (minute / 5) * 5;

    // Display minute, accounting for 'past' or 'to'
    if (minute < 5) {
    	//no past or till
    } else if (minute < 35) {
        add_bmp(BMP_PAST);
    } else {
        minute = 60 - minute;
        hour++;
        add_bmp(BMP_TILL);
    }

    if(hour == 0 || hour == 12);
    else if(hour < 12) add_bmp(BMP_AM);
    else add_bmp(BMP_PM);

    // Display hour
    switch(hour) {
        case 0:
            add_bmp(HOUR_MIDNIGHT);
            break;
        case 1:
        case 13:
            add_bmp(HOUR_ONE);
            break;
        case 2:
        case 14:
            add_bmp(HOUR_TWO);
            break;
        case 3:
        case 15:
            add_bmp(HOUR_THREE);
            break;
        case 4:
        case 16:
            add_bmp(HOUR_FOUR);
            break;
        case 5:
        case 17:
            add_bmp(HOUR_FIVE);
            break;
        case 6:
        case 18:
            add_bmp(HOUR_SIX);
            break;
        case 7:
        case 19:
            add_bmp(HOUR_SEVEN);
            break;
        case 8:
        case 20:
            add_bmp(HOUR_EIGHT);
            break;
        case 9:
        case 21:
            add_bmp(HOUR_NINE);
            break;
        case 10:
        case 22:
            add_bmp(HOUR_TEN);
            break;
        case 11:
        case 23:
            add_bmp(HOUR_ELEVEN);
            break;
        case 12:
            add_bmp(HOUR_NOON);
            break;
        default:
            // Handle error or invalid hour
            break;
    }

    // Display minute in intervals of five using an array pointing to the bitmaps
    if (minute > 0) {
        add_bmp(minuteBitmaps[(minute / 5) - 1]);
    }
}

// Global variables to keep track of the encoder count and direction
volatile int32_t encoder_count = 0;
volatile uint8_t lastState = 0;
volatile uint8_t button_state = 0;
volatile uint32_t last_debounce_time = 0;

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
  /* USER CODE BEGIN 2 */

  // Number of digits and definition of MIN (if it's not already defined).
  #define NUM_DIGITS 4
  #define MIN(a, b) (((a) < (b)) ? (a) : (b))

  // Modify these pins according to your particular board connections
  #define DIGIT_1_PIN DIG_1_A_Pin
  #define DIGIT_2_PIN DIG_2_A_Pin
  #define DIGIT_3_PIN DIG_3_A_Pin
  #define DIGIT_4_PIN DIG_4_A_Pin
  #define COLON_PIN   DEC_A_Pin

  // GPIO Ports
  #define DIGIT_1_PORT GPIOB
  #define DIGIT_2_PORT GPIOB
  #define DIGIT_3_PORT GPIOA
  #define DIGIT_4_PORT GPIOA

  // Segment definitions for numbers and some characters in hexadecimal
  const uint8_t charToSegmentsMap[] = {
		    ['0'] = 0x3F, ['1'] = 0x06, ['2'] = 0x5B, ['3'] = 0x4F,
		    ['4'] = 0x66, ['5'] = 0x6D, ['6'] = 0x7D, ['7'] = 0x07,
		    ['8'] = 0x7F, ['9'] = 0x6F, ['A'] = 0x77, ['B'] = 0x7C,
		    ['C'] = 0x39, ['D'] = 0x5E, ['E'] = 0x79, ['F'] = 0x71,
		    ['G'] = 0x3D, ['H'] = 0x76, ['I'] = 0x30, ['J'] = 0x1E,
		    ['K'] = 0x76, // Using same as 'H', no unique representation for 'K'
		    ['L'] = 0x38, ['M'] = 0x37, // 'M' uses same as 'n', no unique representation
		    ['N'] = 0x54, ['O'] = 0x3F, ['P'] = 0x73, ['Q'] = 0x67,
		    ['R'] = 0x50, ['S'] = 0x6D, ['T'] = 0x78, ['U'] = 0x3E,
		    ['V'] = 0x3E, // Using same as 'U', no unique representation for 'V'
		    ['W'] = 0x2A, // Representation of 'W' is not possible, so using compromise
		    ['X'] = 0x76, // Using same as 'H', no unique representation for 'X'
		    ['Y'] = 0x6E, ['Z'] = 0x5B,  // 'Z' uses same as '2'
			['!'] = 0b10000010,
      [' '] = 0x00, // Blank character
      ['.'] = 0x80, // Decimal point assuming it's on a separate segment
  };

  // Set the segments for the current digit
  void setSegments(uint8_t segments) {
      HAL_GPIO_WritePin(GPIOA, SEG_A_K_Pin, (segments & (1 << 0)) ? GPIO_PIN_RESET : GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIOA, SEG_B_K_Pin, (segments & (1 << 1)) ? GPIO_PIN_RESET : GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIOA, SEG_C_K_Pin, (segments & (1 << 2)) ? GPIO_PIN_RESET : GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIOB, SEG_D_K_Pin, (segments & (1 << 3)) ? GPIO_PIN_RESET : GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIOB, SEG_E_K_Pin, (segments & (1 << 4)) ? GPIO_PIN_RESET : GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIOA, SEG_F_K_Pin, (segments & (1 << 5)) ? GPIO_PIN_RESET : GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIOA, SEG_G_K_Pin, (segments & (1 << 6)) ? GPIO_PIN_RESET : GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIOA, DP_K_Pin, 	(segments & (1 << 7)) ? GPIO_PIN_RESET : GPIO_PIN_SET);
      // Set remaining segments and additional control for common anode/cathode if necessary
  }

  // Activate a single digit
  void activateDigit(uint8_t digit) {
      // Assuming digit is 1 based (1 first digit, 2 second digit, etc)
      HAL_GPIO_WritePin(DIGIT_1_PORT, DIGIT_1_PIN, digit == 1 ? GPIO_PIN_SET : GPIO_PIN_RESET);
      HAL_GPIO_WritePin(DIGIT_2_PORT, DIGIT_2_PIN, digit == 2 ? GPIO_PIN_SET : GPIO_PIN_RESET);
      HAL_GPIO_WritePin(DIGIT_3_PORT, DIGIT_3_PIN, digit == 3 ? GPIO_PIN_SET : GPIO_PIN_RESET);
      HAL_GPIO_WritePin(DIGIT_4_PORT, DIGIT_4_PIN, digit == 4 ? GPIO_PIN_SET : GPIO_PIN_RESET);
      HAL_GPIO_WritePin(GPIOB, 		  COLON_PIN,   digit == 5 ? GPIO_PIN_SET : GPIO_PIN_RESET);
  }


  // Display up to four characters on the 7-segment displays
  void Segment_Display(const char* input) {

	    char output[6] = "";  // Assuming maximum input length of 5 digits + null terminator
	    bool hasColon = false;

	    for (int i = 0; i < strlen(input); i++) {
	        if (input[i] != ':') {
	            int len = strlen(output);
	            output[len] = input[i];
	            output[len + 1] = '\0';
	        }
	        else {
	        	hasColon = true;
	        }
	    }


      // clearing all digits
      HAL_GPIO_WritePin(DIGIT_1_PORT, DIGIT_1_PIN, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(DIGIT_2_PORT, DIGIT_2_PIN, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(DIGIT_3_PORT, DIGIT_3_PIN, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(DIGIT_4_PORT, DIGIT_4_PIN, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(GPIOB, 		  COLON_PIN,   GPIO_PIN_RESET);

      uint8_t numChars = MIN(strlen(output), NUM_DIGITS);
      for (int i = 0; i < (numChars + hasColon); i++) {
          activateDigit(i + 1); // Activate the correct digit
          if((i + 1) == 5) { //colon
        	  setSegments(0b11);
          } else {
        	  setSegments(charToSegmentsMap[(uint8_t) output[i]]); // Set the correct segments
          }
          HAL_Delay(1); // Delay to allow the segments to light up
      }
      activateDigit(0); // Turn off all digits
  }





  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  RTC_TimeTypeDef sTime;
  RTC_DateTypeDef sDate;
  bool hours_set = false;
  bool minutes_set = false;
  bool color_set = false;
  uint32_t color = 0xFFFFFF;

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


		// Update the RTC structure with the current time
		HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN); // or RTC_FORMAT_BCD depending on your setting
		HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN); // This line is required to unlock the shadow registers



	    char displayStr[6]; // Buffer for "00:00" plus null terminator

	    switch (button_state) {
	        case 0:
	            // Default state, should not display anything.
	            Segment_Display("STRT");
	            hours_set = false;  // Reset hours_set flag
	            minutes_set = false;
	            color_set = false;
	            break;
	        case 1:
	        	if(!hours_set) {
	        		encoder_count = (sTime.Hours * 10);
	        		hours_set = true;
	        	}

	        	if(encoder_count > 230) encoder_count = 230; // 23 * 10
	        	if(encoder_count < 0) encoder_count = 0;

	        	sTime.Hours = encoder_count / 10; // Convert to actual hours by dividing by 10
	        	sTime.Minutes = 0;
	        	sTime.Seconds = 0;
	        	snprintf(displayStr, sizeof(displayStr), "%02u:%02u", sTime.Hours, sTime.Minutes);
	        	Segment_Display(displayStr);

        		HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
        		HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	            break;
	        case 2:
	        	if(!minutes_set) {
	        		encoder_count = sTime.Minutes * 10;
	        		minutes_set = true;
	        	}
	            sTime.Minutes = encoder_count;
	            sTime.Seconds = 0;

	            if(encoder_count > 590) encoder_count = 590;  // 59 * 10
	            if(encoder_count < 0) encoder_count = 0;

	            sTime.Minutes = encoder_count / 10;

	            snprintf(displayStr, sizeof(displayStr), "%02u:%02u", sTime.Hours, sTime.Minutes);
	            Segment_Display(displayStr);

        		HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
        		HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	            break;
	        case 3:
	        	if(!color_set) {
	        		encoder_count = 0;
	        		color_set = true;
	        	}

	            if(encoder_count > 160) encoder_count = 160; // 160 * 10
	            if(encoder_count < 0) encoder_count = 0;

	        	color = getRainbowColor((int) encoder_count / 10);
	        	snprintf(displayStr, sizeof(displayStr), "%04i", (encoder_count / 10));
	            Segment_Display(displayStr);
	        	break;
	        case 4:

	        default:
	            Segment_Display("ERR");
	            button_state = 0;
	            break;

	    }



	    HAL_GPIO_WritePin(GPIOA, LED_Pin, 1);

	    HAL_Delay(1);
	    HAL_GPIO_WritePin(GPIOA, LED_Pin, 0);




	// Now you can safely use sTime to display the time or perform other operations
	display_time(sTime.Hours, sTime.Minutes);
	display_bmp(color);
	WS2812B_Send(htim1);

	clear_display_buffer();
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
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 0, 0);
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

  /*Configure GPIO pins : ENC_CH_A_Pin ENC_CH_B_Pin */
  GPIO_InitStruct.Pin = ENC_CH_A_Pin|ENC_CH_B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : BTN_Pin */
  GPIO_InitStruct.Pin = BTN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BTN_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */
//----------------------------------------------------------------------------------------------------------------------------dial
// Callback function to handle encoder signals


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    uint8_t currentState;
    uint8_t aState;
    uint8_t bState;
    const uint32_t debounce_delay = 50;  // milliseconds

    // Read the current encoder states
    aState = HAL_GPIO_ReadPin(GPIOB, ENC_CH_A_Pin);
    bState = HAL_GPIO_ReadPin(GPIOB, ENC_CH_B_Pin);
    currentState = (aState << 1) | bState;

    // Only consider state changes if either A or B has generated an interrupt
    if ((GPIO_Pin == ENC_CH_A_Pin) || (GPIO_Pin == ENC_CH_B_Pin)) {
        // Determine the rotation direction based on the state transition
        if ((lastState == 0x0 && currentState == 0x2) ||
            (lastState == 0x3 && currentState == 0x1) ||
            (lastState == 0x2 && currentState == 0x3) ||
            (lastState == 0x1 && currentState == 0x0)) {
            // Encoder has moved clockwise
        	encoder_count++;
        }
        else if ((lastState == 0x0 && currentState == 0x1) ||
                 (lastState == 0x1 && currentState == 0x3) ||
                 (lastState == 0x3 && currentState == 0x2) ||
                 (lastState == 0x2 && currentState == 0x0)) {
            // Encoder has moved counterclockwise
            encoder_count--;
        }

        // Save the new state
        lastState = currentState;
    } else if (GPIO_Pin == BTN_Pin) {
        uint32_t current_time = HAL_GetTick();  // Assuming HAL_GetTick() gives you the system tick in ms

        if ((current_time - last_debounce_time) > debounce_delay) {
            // Enough time has passed since the last button press (debounced)
            button_state++;
            last_debounce_time = current_time;  // update last debounce time
        }
    }

    // Handle other GPIO pins (if any)
}

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
