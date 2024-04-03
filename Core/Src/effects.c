/*
 * effects.c
 *
 *  Created on: Mar 31, 2024
 *      Author: dsava
 */

#include "effects.h"

static LED targetDisplay[MATRIX_SIZE];
static LED currentDisplay[MATRIX_SIZE];

/**
 * @brief Converts a bitmap to PWM data for WS2812B LEDs.
 *
 * Converts a bitmap into PWM data for driving WS2812B LEDs. Each bit in the bitmap
 * corresponds to an LED in a left-to-right, top-to-bottom layout, where a set bit
 * represents an illuminated LED and a clear bit represents an unilluminated LED.
 * The PWM data includes color information based on the specified 24-bit color and
 * brightness level. ONE and ZERO are defined based on a 72Mhz clock.
 *
 * @param[in] bitmap     Bitmap representing LED layout.
 * @param[in] color      24-bit color value (0xRRGGBB).
 * @param[in] brightness Brightness level (0-255).
 */
void addBitmapToDisplay(const uint16_t matrix[MATRIX_HEIGHT], LED *display, RgbColor color, Effect effect) {

    //TODO: create function
    // applyBrightness((uint8_t*) red, (uint8_t*) green, (uint8_t*) blue, brightness);

    for(int i = 0; i < MATRIX_HEIGHT; i++) {
        for(int j = 0; j < MATRIX_WIDTH; j++) {

            uint8_t ledNumber = (MATRIX_WIDTH * i) + j;

            if(matrix[i] & (1 << j)) {
            	display[ledNumber].red = color.r;
            	display[ledNumber].green = color.g;
            	display[ledNumber].blue = color.b;
            	display[ledNumber].on = true;
            	display[ledNumber].effect = effect;
            }

        }
    }
}



typedef enum FlickerState {
    STATE_IDLE,
    STATE_FLICKER_OUT,
    STATE_FLICKER_IN
}FlickerState;

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



void wipeDisplay(LED *display) {
	for(int i = 0; i < MATRIX_SIZE; i++) {
		display[i].blue = 0;
		display[i].green = 0;
		display[i].red = 0;
		display[i].effect = NONE;
	}
}

void advanceDisplay() {
    memcpy(currentDisplay, targetDisplay, sizeof(currentDisplay));
    wipeDisplay((LED *) targetDisplay);
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

const uint16_t *hourBitmaps[] = {
		HOUR_MIDNIGHT,
		HOUR_ONE,
		HOUR_TWO,
		HOUR_THREE,
		HOUR_FOUR,
		HOUR_FIVE,
		HOUR_SIX,
		HOUR_SEVEN,
		HOUR_EIGHT,
		HOUR_NINE,
		HOUR_TEN,
		HOUR_ELEVEN,
		HOUR_NOON
};

const uint16_t *minuteBitmaps[] = {
		MINUTE_FIVE,
		MINUTE_TEN,
		MINUTE_FIFTEEN,
		MINUTE_TWENTY,
		MINUTE_TWENTYFIVE,
		MINUTE_THIRTY
};

void display_time(int hour, int minute, RgbColor color) {
    addBitmapToDisplay(BMP_ITS, (LED *) targetDisplay, color, FLICKER);

    // Round down to the nearest five minutes and determine if it is 'past' or 'to' the hour
    int roundedMinute = (minute / 5) * 5;
    if (roundedMinute > 0) {
        if (roundedMinute < 35) {
            addBitmapToDisplay(BMP_PAST, (LED *) targetDisplay, color, FLICKER);
        } else {
            roundedMinute = 60 - roundedMinute;
            hour++;
            addBitmapToDisplay(BMP_TILL, (LED *) targetDisplay, color, FLICKER);
        }
    }

    // Normalize the hour to a 12-hour format and display AM/PM where applicable
    hour %= 24; // Normalize hour to 0-23
    if(hour == 0 || hour == 12) {
        // It's exactly midnight or noon, so we will handle it in the hour display section.
    } else if (hour < 12) {
        addBitmapToDisplay(BMP_AM, (LED *) targetDisplay, color, FLICKER);
    } else {
        addBitmapToDisplay(BMP_PM, (LED *) targetDisplay, color, FLICKER);
    }

    // Display the hour, normalizing hour again for 12-hour format with special cases for noon and midnight
    if (hour > 12) {
        hour -= 12; // Convert to 12-hour format
    }
    if (hour == 0) {
        hour = 12; // Adjust for midnight/noon display
    }

    // Use an array to simplify hour display logic
    if(hour >= 1 && hour <= 12) {
        addBitmapToDisplay(hourBitmaps[hour % 12], (LED *) targetDisplay, color, FLICKER);
    }

    // Display the minute in intervals of five using an array pointing to the bitmaps
    if (roundedMinute > 0) {
        addBitmapToDisplay(minuteBitmaps[(roundedMinute / 5) - 1], (LED *) targetDisplay, color, FLICKER);
    }
}


