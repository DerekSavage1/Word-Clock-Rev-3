/*
 * static.c
 *
 *  Created on: Apr 4, 2024
 *      Author: dsava
 */
#include "constant.h"

void constant(void) {

	uint8_t leds[MATRIX_SIZE];
	uint32_t size = getLEDsWithEffect((uint8_t *) leds, (LED *) currentDisplay, CONSTANT);

	for(int i = 0; i < size; i++) {
		turnOnLED(currentDisplay, leds[i]);
	}

}


