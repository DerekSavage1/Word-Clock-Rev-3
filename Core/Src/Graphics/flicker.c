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

void checkUpdateTime(RTC_TimeTypeDef currentTime) {
    // Check if minute ends in 5 and is different from the previous time
    if ((currentTime.Minutes % 5 == 0) && ((currentTime.Minutes != previousDisplayedTime.Minutes) || (currentTime.Hours != previousDisplayedTime.Hours))) {
        needToUpdateDisplay = true;
    }
}

void updateDisplay(RTC_TimeTypeDef currentTime) {
    // Call flicker effects based on the state
    switch (currentFlickerState) {
        case STATE_IDLE:
            if (needToUpdateDisplay) {
                currentFlickerState = STATE_FLICKER_OUT; // Start the flicker out effect
            }

            break;
        case STATE_FLICKER_OUT:
            isFlickering = flickerOut(); // This function automatically resets its state when done
            if (!isFlickering) { // Assume you have a way to check if flickering out has finished
                currentFlickerState = STATE_FLICKER_IN; // Proceed to flicker in the new display
                RgbColor color;
                color.r = 5;
                color.g = 5;
                color.b = 5;
                display_time(currentTime.Hours, currentTime.Minutes, color); // Update the nextFrame for flicker in
                advanceDisplay();
            }

            break;
        case STATE_FLICKER_IN:
        	isFlickering = flickerIn(); // This function automatically resets its state when done
            if (!isFlickering) { // Assume you have a way to check if flickering in has finished
                currentFlickerState = STATE_IDLE; // Go back to idle state
                needToUpdateDisplay = false;
                previousDisplayedTime = currentTime; // Update the time once the whole effect is done
            }
            break;
        default:
        	break;
    }
}

uint32_t lastTickFlicker;

bool flickerOut(void) {
    static uint8_t litLEDs[MATRIX_SIZE] = {0};
    static uint8_t numLit = 0;
    static uint32_t lastTickEffect = 0;
    static uint8_t loop = 0;
    static bool isInitialized = false;
    const uint8_t flickerLoops = 10;
    const uint32_t delayInterval = 50; // milliseconds

    if (!isInitialized) {
        numLit = getLEDsWithEffect(litLEDs, (LED *) currentDisplay, FLICKER);
        if (numLit == 0) {
            return true; // Function did not start flickering, return false
        }
        loop = 0;
        lastTickEffect = HAL_GetTick();
        isInitialized = true;
    }

    if ((HAL_GetTick() - lastTickEffect) >= delayInterval) {
        if (loop >= flickerLoops) {
            // Ensure all LEDs are turned off at the end
            for (uint8_t i = 0; i < numLit; ++i) {
                turnOffLED((LED *) currentDisplay, litLEDs[i]);
            }
            updatePwmBuffer((LED *) currentDisplay);
            DMA_Send(); // Update LEDs through DMA
            // Reset for next call or trigger completion
            isInitialized = false; // Reset the state
            return false; // Finish the effect
        }

        shuffleArray(litLEDs, numLit);
        for (uint8_t i = 0; i < numLit; ++i) {
            if (RANDOM_IN_RANGE(0, flickerLoops) < loop) {
                turnOffLED((LED *) currentDisplay, litLEDs[i]);
            } else {
                turnOnLED((LED *) currentDisplay, litLEDs[i]);
            }
        }
        updatePwmBuffer((LED *) currentDisplay);
        DMA_Send(); // Update LEDs through DMA
        lastTickEffect = HAL_GetTick();
        loop++;
    }
    return true;
}

bool flickerIn(void) {
    static uint8_t litLEDs[MATRIX_SIZE] = {0};
    static uint8_t numLit = 0;
    static uint32_t lastTickEffect = 0;
    static uint8_t loop = 0;
    static bool isInitialized = false;
    const uint8_t flickerLoops = 10;
    const uint32_t delayInterval = 50; // milliseconds

    if (!isInitialized) {
        numLit = getLEDsWithEffect(litLEDs, (LED *) currentDisplay, FLICKER);
        if (numLit == 0) {
            return true;
        }
        loop = 0;
        lastTickEffect = HAL_GetTick();
        isInitialized = true;
    }

    if ((HAL_GetTick() - lastTickEffect) >= delayInterval) {
        if (loop >= flickerLoops) {
            // Ensure all LEDs are turned on at the end
            for (uint8_t i = 0; i < numLit; ++i) {
                turnOnLED((LED *) currentDisplay, litLEDs[i]);
            }
            updatePwmBuffer((LED *) currentDisplay);
            DMA_Send(); // Update LEDs through DMA
            // Reset for next call or trigger completion
            isInitialized = false; // Reset the state
            return false; // Finish the effect
        }

        shuffleArray(litLEDs, numLit);
        for (uint8_t i = 0; i < numLit; ++i) {
            if (RANDOM_IN_RANGE(0, flickerLoops) > loop) {
                turnOffLED((LED *) currentDisplay, litLEDs[i]);
            } else {
                turnOnLED((LED *) currentDisplay, litLEDs[i]);
            }
        }
        updatePwmBuffer((LED *) currentDisplay);
        DMA_Send(); // Update LEDs through DMA
        lastTickEffect = HAL_GetTick();
        loop++;
    }
    return true;
}




