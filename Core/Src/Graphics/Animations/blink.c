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
uint8_t timeOn = 263;

void blink(void) {
    uint8_t leds[MATRIX_SIZE];
    uint32_t size = getLEDsWithEffect((uint8_t *) leds, (LED *) currentDisplay, BLINK);

    // Calculate total cycle time
    uint32_t totalCycleTime = timeOn + blinkDelay;

    // Calculate on time and off time based on percentages
    uint32_t onTime = (70 * totalCycleTime) / 100;
    uint32_t offTime = totalCycleTime - onTime;

    // Calculate current position in the cycle
    uint32_t currentTime = HAL_GetTick() - lastTickBlink;
    uint32_t cyclePosition = currentTime % totalCycleTime;

    if (cyclePosition < onTime) {
        // LED should be on
        for (int i = 0; i < size; i++) {
            turnOnLED(currentDisplay, leds[i]);
        }
    } else {
        // LED should be off
        for (int i = 0; i < size; i++) {
            turnOffLED(currentDisplay, leds[i]);
        }
    }

    // Update last tick if a full cycle has passed
    if (cyclePosition == 0) {
        lastTickBlink = HAL_GetTick();
    }
}


