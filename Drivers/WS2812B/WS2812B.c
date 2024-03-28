/*
 * WS2812B.c
 *
 *  Created on: Jan 25, 2024
 *      Author: dsava
 */

#include "WS2812B.h"

uint8_t LED_Data[NUM_LEDS][3]; // color data green / red / blue
volatile int datasentflag;


void Set_LED(uint8_t LEDnum, uint8_t Red, uint8_t Green, uint8_t Blue) {

    if(LEDnum < NUM_LEDS) {
        LED_Data[LEDnum][0] = Green;
        LED_Data[LEDnum][1] = Red;
        LED_Data[LEDnum][2] = Blue;
    }
}

void Set_LED_Hex(uint8_t LEDnum, uint32_t color) {

    if(LEDnum < NUM_LEDS) {
        uint8_t Red = (color >> 16) & 0xFF;
        uint8_t Green = (color >> 8) & 0xFF;
        uint8_t Blue = color & 0xFF;
        LED_Data[LEDnum][0] = Green;
        LED_Data[LEDnum][1] = Red;
        LED_Data[LEDnum][2] = Blue;
    }
}

extern TIM_HandleTypeDef htim1;

uint16_t pwmData[(24 * NUM_LEDS) + RESET_SLOTS]; // Each LED requires 24 bits.

void WS2812B_Send() { // Changed to pointer to match typical HAL use.

    uint32_t indx = 0;
    uint32_t data;

//     Shifting colors into 24-bit buffer
    for (int i = 0; i < NUM_LEDS; i++) {

        data = ((LED_Data[i][0] << 16) | (LED_Data[i][1] << 8) | (LED_Data[i][2]));

        for (int j = 23; j >= 0; j--) {
            if (data & (1 << j))
                pwmData[indx] = ONE; // Use defined duty cycle for ONE
            else
                pwmData[indx] = ZERO; // Use defined duty cycle for ZERO
            indx++;
        }
    }

    // Create the reset signal by putting low values (0) at the end of pwmData
    for (int j = 0; j < RESET_SLOTS; j++) {
        pwmData[indx++] = 0;
    }

    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t*)pwmData, indx);
	while (!datasentflag) {}
	datasentflag = 0;

}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {

    // Properly stop the PWM output after the transmission is complete
    HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_1);

    // Set the flag indicating that the data has been sent
    datasentflag = 1;
}
