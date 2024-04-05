/*
 * twinkle.c
 *
 *  Created on: Apr 3, 2024
 *      Author: dsava
 */

#include "twinkle.h"

extern LED targetDisplay[MATRIX_SIZE];
extern LED currentDisplay[MATRIX_SIZE];

uint32_t lastTickTwinkle = 0;
uint16_t twinkleDelay = 1000;

RgbColor adjustBrightness(RgbColor color) {

    RgbColor newColor;
    double gammaCorrection = 1.0 / 1.5;
    double newRed   = 255.0 * pow((double)color.r / 255.0, gammaCorrection);
    double newGreen = 255.0 * pow((double)color.g / 255.0, gammaCorrection);
    double newBlue  = 255.0 * pow((double)color.b / 255.0, gammaCorrection);

    newColor.r = (uint8_t) newRed;
    newColor.g = (uint8_t) newGreen;
    newColor.b = (uint8_t) newBlue;

	updatePwmBuffer((LED *) currentDisplay);
	DMA_Send();

    return newColor;
}

void twinkle() {

	uint8_t userBrightness = getBrightness();

	uint8_t twinkleLEDs[MATRIX_SIZE];

	uint32_t numTwinleLEDs = getLEDsWithEffect((uint8_t *) twinkleLEDs, currentDisplay, TWINKLE);

	shuffleArray(twinkleLEDs, numTwinleLEDs);

	//if arrays are not equal, copy elements to other array

	if(HAL_GetTick() - lastTickTwinkle <= twinkleDelay) {
		//not enough time has passed to reassign brightness
		//ease brightnesses closer to their target
		//userBrightness is a value between 0 and 255, stay within... maybe 20% of user brightness. Don't want to keep them awake at night.
//		for(uint8_t i = 0; i < sizeof(twinkleLEDs); i++) {
//			LED led = getLED((LED *) currentFrame, twinkleLEDs[i])
//			RgbColor ledColor;
//			ledColor.r = led.red;
//			ledColor.g = led.green;
//			ledColor.b = led.blue;
//			adjustBrightness(ledColor);
//
//		}
//	} else {
//		//update brightnesses
//		for(uint8_t i = 0; i < sizeof(twinkleLEDs); i++) {
//			//assign target brightness
//			//keep a limit
//		}
	}


}
