/*
 * WS2812B.c
 *
 *  Created on: Jan 25, 2024
 *      Author: dsava
 */

#include <ws2812b.h>

volatile int datasentflag;
extern TIM_HandleTypeDef htim1;
uint16_t pwmData[RESET_SLOTS + (24 * NUM_LEDS) + RESET_SLOTS]; // Each LED requires 24 bits.

static uint16_t pwmBuffer[PWM_ARRAY_SIZE] = {0};

/**
 * @brief   Turns on an LED by setting its 'draw' flag to false.
 *
 * @param   number The number of the LED to turn on.
 */
void turnOnLED(LED *frame, uint8_t index) {
	frame[index].on = true;
}

/**
 * @brief   Turns off an LED by setting its 'draw' flag to false.
 *
 * @param   number The number of the LED to turn off.
 */
void turnOffLED(LED *frame, uint8_t index) {
	frame[index].on = false;
}

void toggleLED(LED *frame, uint8_t index) {
	frame[index].on = !frame[index].on;
}

bool isLEDOn(LED* frame, uint8_t index) {

    if (index >= MATRIX_SIZE) {
        return false; // Index is out of bound, so LED is off by default.
    }

    return frame[index].on == true;
}

/**
 * @brief   Extracts indices of lit LEDs from the LED buffer.
 *
 * This function iterates through the LED buffer, storing the indices of lit LEDs
 * in the provided array. An LED is considered lit if its red, green, or blue
 * component is nonzero.
 *
 * @param   arr Pointer to an array for storing indices of lit LEDs.
 *            This array should be preallocated by the caller.
 *
 * @return  Number of lit LEDs found. This value represents the size of the updated array.
 */
uint8_t getLEDsWithEffect(uint8_t *result, LED *display, Effect effect) {

    uint32_t index = 0;

    for(int i = 0; i < MATRIX_SIZE; i++) {
    	if(display[i].effect == effect) {
    		result[index] = i;
            index++;
    	}
    }

    return index++;
}

void removeLED(LED *frame, uint8_t index) {
	frame[index].blue = 0;
	frame[index].red = 0;
	frame[index].green = 0;
	frame[index].effect = NONE;
	frame[index].on = false;
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

    for(int i = MATRIX_SIZE * 24; i < PWM_ARRAY_SIZE; i++) {
        pwmBuffer[i] = RESET;
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

    for(int ledNumber = 0 ; ledNumber < MATRIX_SIZE; ledNumber++) {

        if(!currentFrame[ledNumber].on) {
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

	HAL_Delay(1);
    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t*)pwmBuffer, PWM_ARRAY_SIZE);
	while (!datasentflag) {}
	datasentflag = 0;

}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {

    HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_1);
    datasentflag = 1;

}
