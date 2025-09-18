/*
 * rainbow.c
 *
 *  Created on: Apr 2, 2024
 *      Author: dsava
 */

#include "rainbow.h"

extern LED targetDisplay[MATRIX_SIZE];
extern LED currentDisplay[MATRIX_SIZE];
static RgbColor rainbowColor;

void rainbow(RTC_TimeTypeDef currentTime) {

		uint8_t leds[MATRIX_SIZE];
	    uint32_t size = getLEDsWithEffect((uint8_t *) leds, (LED *) currentDisplay, RAINBOW);
	    static bool isInitialized = false;
	    const uint32_t delayIntervalMs = 1;
	    static uint32_t lastTickEffect = 0;
		static HsvColor hsv;



	    if (!isInitialized) {
			lastTickEffect = HAL_GetTick();
			isInitialized = true;
			hsv.s = 255;
			hsv.h = 0;
		}

	    hsv.v = fmax(getBrightnessAsPercent(), 5);

		if ((HAL_GetTick() - lastTickEffect) >= delayIntervalMs) {
			hsv.h = hsv.h + 1;
		}

		rainbowColor = hsvToRgb(hsv);

}

RgbColor getRainbowColor() {
	return rainbowColor;
}
