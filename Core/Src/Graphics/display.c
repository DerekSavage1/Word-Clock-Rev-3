/*
 * display.c
 *
 *  Created on: Apr 2, 2024
 *      Author: dsava
 */

#include "display.h"

LED targetDisplay[MATRIX_SIZE];
LED currentDisplay[MATRIX_SIZE];

void addBitmapToDisplay(const uint16_t matrix[MATRIX_HEIGHT], LED *display, Effect effect) {

	RgbColor color = getColor();
    //TODO: create function
    // applyBrightness((uint8_t*) red, (uint8_t*) green, (uint8_t*) blue, brightness);

    for(int i = 0; i < MATRIX_HEIGHT; i++) {
        for(int j = 0; j < MATRIX_WIDTH; j++) {

            uint8_t ledNumber = (MATRIX_WIDTH * i) + j;

            if(matrix[i] & (1 << j)) {
            	display[ledNumber].red = color.r;
            	display[ledNumber].green = color.g;
            	display[ledNumber].blue = color.b;
            	display[ledNumber].effect = effect;
            }

        }
    }
}

void removeBitmapFromDisplay(const uint16_t matrix[MATRIX_HEIGHT], LED *display) {

	RgbColor color = getColor();
    //TODO: create function
    // applyBrightness((uint8_t*) red, (uint8_t*) green, (uint8_t*) blue, brightness);

    for(int i = 0; i < MATRIX_HEIGHT; i++) {
        for(int j = 0; j < MATRIX_WIDTH; j++) {

            uint8_t ledNumber = (MATRIX_WIDTH * i) + j;

            if(matrix[i] & (1 << j)) {
            	display[ledNumber].red = color.r;
            	display[ledNumber].green = color.g;
            	display[ledNumber].blue = color.b;
            	display[ledNumber].on = false;
            	display[ledNumber].effect = NONE;
            }

        }
    }
}

void updateDisplayColor(void) {

	RgbColor color = getColor();

    for(int i = 0; i < MATRIX_HEIGHT; i++) {
        for(int j = 0; j < MATRIX_WIDTH; j++) {

            uint8_t ledNumber = (MATRIX_WIDTH * i) + j;

        	if(currentDisplay[ledNumber].effect == RAINBOW) {
        		continue;
        	}

        	if(currentDisplay[ledNumber].effect == NONE) {
        		continue;
        	}

			currentDisplay[ledNumber].red = color.r;
			currentDisplay[ledNumber].green = color.g;
			currentDisplay[ledNumber].blue = color.b;
        }
    }
}

void wipeDisplay(LED *display) {
	for(int i = 0; i < MATRIX_SIZE; i++) {
		display[i].blue = 0;
		display[i].green = 0;
		display[i].red = 0;
		display[i].effect = NONE;
	}
}

void advanceDisplay(Effect effect) {

	for(int i = 0; i < MATRIX_SIZE; i++) {
		if(targetDisplay[i].effect == effect) {
			currentDisplay[i] = targetDisplay[i];
		}

		if(currentDisplay[i].effect == effect) {
			removeLED(currentDisplay, i);
		}
	}
    memcpy(currentDisplay, targetDisplay, sizeof(currentDisplay));
    wipeDisplay((LED *) targetDisplay);
}

void sendDisplayToDMA() {
	updatePwmBuffer((LED *) currentDisplay);
	DMA_Send();
}
