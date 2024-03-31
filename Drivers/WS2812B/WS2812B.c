/*
 * WS2812B.c
 *
 *  Created on: Jan 25, 2024
 *      Author: dsava
 */

#include "WS2812B.h"

volatile int datasentflag;
extern TIM_HandleTypeDef htim1;
uint16_t pwmData[(24 * NUM_LEDS) + RESET_SLOTS]; // Each LED requires 24 bits.

static uint16_t pwmBuffer[PWM_ARRAY_SIZE] = {0};

/**
 * @brief   Turns on an LED by setting its 'draw' flag to false.
 *
 * @param   number The number of the LED to turn on.
 */
void turnOnLED(LED *currentFrame, uint8_t number) {
	currentFrame[number].draw = true;
}

/**
 * @brief   Turns off an LED by setting its 'draw' flag to false.
 *
 * @param   number The number of the LED to turn off.
 */
void turnOffLED(LED *currentFrame, uint8_t number) {
	currentFrame[number].draw = false;
}


/**
 * @brief Converts a bitmap to PWM data for WS2812B LEDs.
 *
 * Wipes PWM Buffer by filling it with user defined ZERO PWM values.
 *
 */
void wipePWMBuffer(void) {
    for(int i = 0; i < PWM_ARRAY_SIZE; i++) {
        pwmBuffer[i] = ZERO;
    }
}

/**
 * @brief   Updates the PWM buffer based on the LED data.
 *
 * This function iterates through each LED in the LED buffer, extracts
 * the red, green, and blue components, and converts them into PWM signals.
 * It assumes that the LEDs follow the ws2812b protocol, which uses GRB
 * (green, red, blue) order.
 *
 * @note    The PWM buffer must be appropriately sized to accommodate the
 *          LED data. Each LED requires 24 bits in the PWM buffer.
 */
void updatePwmBuffer(LED *currentFrame) {

    wipePWMBuffer();

    for(int ledNumber = 0; ledNumber < MATRIX_SIZE; ledNumber++) {

        if(!currentFrame[ledNumber].draw) {
            continue;
        }


        uint8_t red     = currentFrame[ledNumber].red;
        uint8_t green   = currentFrame[ledNumber].green;
        uint8_t blue    = currentFrame[ledNumber].blue;
        uint32_t arrayIndex = ledNumber * 24;

        // ws2812b is GRB, so we swap the positions of red and green
        for(int bit = 0; bit < 8; bit++) {

            if(green & (1 << bit)) {
                pwmBuffer[arrayIndex + 16 + (7 - bit)] = ONE;
            }

            if(red & (1 << bit)) {
                pwmBuffer[arrayIndex + 8 + (7 - bit)] = ONE;
            }

            if(blue & (1 << bit)) {
                pwmBuffer[arrayIndex + (7 - bit)] = ONE;
            }
        }

    }
}


void DMA_Send() {

    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t*)pwmBuffer, PWM_ARRAY_SIZE + 1);
	while (!datasentflag) {}
	datasentflag = 0;

}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {

    HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_1);
    datasentflag = 1;

}
