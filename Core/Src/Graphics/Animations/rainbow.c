/*
 * rainbow.c
 *
 *  Created on: Apr 2, 2024
 *      Author: dsava
 */

#include "rainbow.h"

extern LED targetDisplay[MATRIX_SIZE];
extern LED currentDisplay[MATRIX_SIZE];


static HsvColor lastColor = {0};
bool init = false;
uint32_t lastTickRainbow = 0;
uint32_t rainbowDelay = 357;

void setupRainbow(void) {
	uint8_t rainbow[MATRIX_SIZE];
	uint32_t size = getLEDsWithEffect(rainbow, (LED *) currentDisplay, RAINBOW);

	if(HAL_GetTick() - lastTickRainbow < rainbowDelay) {
		return;
	}

	lastTickRainbow = HAL_GetTick();

	lastColor.h++;
	RgbColor rgb = hsvToRgb(lastColor);
	for(uint8_t i = 0; i < size; i++) {

		currentDisplay[rainbow[i]].red = rgb.r;
		currentDisplay[rainbow[i]].blue = rgb.g;
		currentDisplay[rainbow[i]].green = rgb.b;
	}

}

void advanceRainbow(uint8_t brightness) {
	uint8_t rainbow[MATRIX_SIZE];
	uint32_t size = getLEDsWithEffect(rainbow, (LED *) currentDisplay, RAINBOW);

	for(uint8_t i = 0; i < size; i++) {
		RgbColor ledrgb;
		ledrgb.r = currentDisplay[rainbow[i]].red;
		ledrgb.b = currentDisplay[rainbow[i]].blue;
		ledrgb.g = currentDisplay[rainbow[i]].green;
		HsvColor hsv = rgbToHsv(ledrgb);

		hsv.s = 255;
		hsv.v = getBrightnessAsPercent();
		hsv.h++;

		RgbColor rgb = hsvToRgb(hsv);
		currentDisplay[rainbow[i]].red = rgb.r;
		currentDisplay[rainbow[i]].blue = rgb.b;
		currentDisplay[rainbow[i]].green = rgb.g;

	}
}

void rainbow(uint8_t brightness) {

//	if(!init) {
//		lastColor.s = 255;
//		lastColor.v = getBrightness();
//		setupRainbow();
//		init = !init;
//		return;
//	}

	setupRainbow();
//	advanceRainbow(brightness);

	updatePwmBuffer((LED *) currentDisplay);
	DMA_Send();
}
