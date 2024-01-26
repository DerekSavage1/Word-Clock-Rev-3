/*
 * PEC11R.c
 *
 *  Created on: Jan 25, 2024
 *      Author: dsava
 */

#include "PEC11R.h"

// Private variables
static volatile int32_t encoder_count = 0;
static volatile uint8_t lastState = 0;
static volatile uint8_t button_count = 0;
static volatile uint32_t last_debounce_time = 0;
const uint32_t debounce_delay = 50; // milliseconds

// Accessor for encoder count
int32_t Encoder_GetCount(void) {
    return encoder_count;
}

// Function to reset encoder count
void Encoder_SetCount(uint32_t count) {
    encoder_count = count;
}

// Accessor for button state
uint8_t Button_GetCount(void) {
    return button_count;
}

// Function to reset button state
void Button_SetCount(uint32_t count) {
    button_count = count;
}

// EXTI callback for the encoder
void Encoder_EXTI_Callback(uint16_t GPIO_Pin) {
	uint8_t currentState;
	uint8_t aState = HAL_GPIO_ReadPin(GPIOB, ENC_CH_A_Pin);
	uint8_t bState = HAL_GPIO_ReadPin(GPIOB, ENC_CH_B_Pin);
	currentState = (aState << 1) | bState;
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
}

// EXTI callback for the button
void Button_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin != BTN_Pin)
        return;

    uint32_t current_time = HAL_GetTick();
    if ((current_time - last_debounce_time) > debounce_delay) {
        // Enough time has passed since the last button press (debounced)
        button_count++;
        last_debounce_time = current_time; // Update last debounce time
    }
}
