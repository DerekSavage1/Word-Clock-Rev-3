/*
 * flicker.c
 *
 *  Created on: Apr 2, 2024
 *      Author: dsava
 */

#include "flicker.h"

FlickerState currentFlickerState = STATE_IDLE;
static RTC_TimeTypeDef previousDisplayedTime = {0}; // Initialize to some value
bool needToUpdateDisplay = true;
bool isFlickering = false;

void updateDisplay(RTC_TimeTypeDef currentTime) {

	display_time(currentTime.Hours, currentTime.Minutes);

	if(displaysAreDifferent(FLICKER) && currentFlickerState != STATE_FLICKER_IN) {
		currentFlickerState = STATE_FLICKER_OUT;
	}

    switch (currentFlickerState) {
        case STATE_IDLE:
            break;
        case STATE_FLICKER_OUT:
            isFlickering = flickerOut();
            if (!isFlickering) {
                currentFlickerState = STATE_FLICKER_IN;
            }
            break;
        case STATE_FLICKER_IN:
        	isFlickering = flickerIn();
            if (!isFlickering) {
                currentFlickerState = STATE_IDLE;
                previousDisplayedTime = currentTime;
            }
            break;
        default:
        	break;
    }
}

uint32_t lastTickFlicker;

bool flickerOut(void) {
    static uint8_t ledsToFlickerOff[MATRIX_SIZE] = {0};
    static uint8_t numLit = 0;
    static uint32_t lastTickEffect = 0;
    static uint8_t loop = 0;
    static bool isInitialized = false;
    const uint8_t flickerLoops = 10;
    const uint32_t delayIntervalMs = 50;

    if (!isInitialized) {
    	numLit = getChangedPixels(ledsToFlickerOff, FLICKER);
        numLit = getLEDsWithEffect(ledsToFlickerOff, (LED *) currentDisplay, FLICKER);
        if (numLit == 0) {
            return false; // Function did not start flickering, return false
        }
        loop = 0;
        lastTickEffect = HAL_GetTick();
        isInitialized = true;
    }

    if ((HAL_GetTick() - lastTickEffect) >= delayIntervalMs) {
        if (loop >= flickerLoops) {
            // Ensure all LEDs are turned off at the end
            for (uint8_t i = 0; i < numLit; ++i) {
                removeLED((LED *) currentDisplay, ledsToFlickerOff[i]);
            }
            // Reset for next call or trigger completion
            isInitialized = false; // Reset the state
            return false; // Finish the effect
        }

        shuffleArray(ledsToFlickerOff, numLit);
        for (uint8_t i = 0; i < numLit; ++i) {
            if (RANDOM_IN_RANGE(0, flickerLoops) < loop) {
                turnOffLED((LED *) currentDisplay, ledsToFlickerOff[i]);
            } else {
                turnOnLED((LED *) currentDisplay, ledsToFlickerOff[i]);
            }
        }
        lastTickEffect = HAL_GetTick();
        loop++;
    }
    return true;
}

bool flickerIn(void) {
    static uint8_t ledsToFlickerIn[MATRIX_SIZE] = {0};
    static uint8_t numLit = 0;
    static uint32_t lastTickEffect = 0;
    static uint8_t loop = 0;
    static bool isInitialized = false;
    const uint8_t flickerLoops = 10;
    const uint32_t delayInterval = 50; // milliseconds

    if (!isInitialized) {
        numLit = getChangedPixels(ledsToFlickerIn, FLICKER);
        if (numLit == 0) {
            return false;
        }
        loop = 0;
        lastTickEffect = HAL_GetTick();
        isInitialized = true;
    }

    if ((HAL_GetTick() - lastTickEffect) >= delayInterval) {
        if (loop >= flickerLoops) {
            // Ensure all LEDs are turned on at the end
            for (uint8_t i = 0; i < numLit; ++i) {
            	currentDisplay[ledsToFlickerIn[i]] = targetDisplay[ledsToFlickerIn[i]];
                turnOnLED((LED *) currentDisplay, ledsToFlickerIn[i]);
            }
            // Reset for next call or trigger completion
            isInitialized = false; // Reset the state
            return false; // Finish the effect
        }

        shuffleArray(ledsToFlickerIn, numLit);
        for (uint8_t i = 0; i < numLit; ++i) {
        	currentDisplay[ledsToFlickerIn[i]] = targetDisplay[ledsToFlickerIn[i]];
            if (RANDOM_IN_RANGE(0, flickerLoops) > loop) {
                turnOffLED((LED *) currentDisplay, ledsToFlickerIn[i]);
            } else {
                turnOnLED((LED *) currentDisplay, ledsToFlickerIn[i]);
            }
        }
        lastTickEffect = HAL_GetTick();
        loop++;
    }


    return true;
}




