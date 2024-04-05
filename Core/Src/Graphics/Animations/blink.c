/*
 * blink.c
 *
 *  Created on: Apr 4, 2024
 *      Author: dsava
 */

#include "blink.h"

extern LED targetDisplay[MATRIX_SIZE];
extern LED currentDisplay[MATRIX_SIZE];

uint32_t lastTickBlink = 0;
uint16_t blinkDelay = 375;

void blink(void) {

	uint8_t leds[MATRIX_SIZE];
	uint32_t size = getLEDsWithEffect((uint8_t *) leds, (LED *) currentDisplay, BLINK);

	if(HAL_GetTick() - lastTickBlink > blinkDelay) {
		for(int i = 0; i < size; i++) {
			toggleLED(currentDisplay, leds[i]);
		}
		lastTickBlink = HAL_GetTick();
	}

}


