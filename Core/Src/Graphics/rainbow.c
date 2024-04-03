/*
 * rainbow.c
 *
 *  Created on: Apr 2, 2024
 *      Author: dsava
 */

#include "rainbow.h"

HsvColor lastColor = {0};

void setAnniversary(uint8_t brightness) {

	lastColor.s = 255;
	lastColor.v = brightness;


	lastColor.h = lastColor.h + 5;

	RgbColor rgb = HsvToRgb(lastColor);

	addBitmapToDisplay(BMP_HAPPY, (LED *) currentDisplay, rgb, RAINBOW);
	addBitmapToDisplay(BMP_ANNIVERSARY, (LED *) currentDisplay, rgb, RAINBOW);
	addBitmapToDisplay(BMP_KATIEDEREK, (LED *) currentDisplay, rgb, RAINBOW);

	updatePwmBuffer((LED *) currentDisplay);
	DMA_Send();
}
