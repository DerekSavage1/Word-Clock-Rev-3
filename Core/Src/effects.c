/*
 * effects.c
 *
 *  Created on: Mar 31, 2024
 *      Author: dsava
 */

/**
 * @brief   Shuffles the elements of an array randomly.
 *
 * Rearranges the elements of the given array in a random order.
 * Each possible permutation is equally likely.
 *
 * @param   array Pointer to the array to be shuffled.
 * @param   size  Number of elements in the array.
 *
 * @note    The array must be non-empty and contain at least two elements for shuffling to occur.
 *          Otherwise, the function does nothing.
 */



#include "effects.h"

static LED nextFrame[MATRIX_SIZE];
static LED currentFrame[MATRIX_SIZE];

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
void addBitmapToNextFrame(const uint16_t matrix[MATRIX_HEIGHT], uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness) {

    //TODO: create function
    // applyBrightness((uint8_t*) red, (uint8_t*) green, (uint8_t*) blue, brightness);

    for(int i = 0; i < MATRIX_HEIGHT; i++) {
        for(int j = 0; j < MATRIX_WIDTH; j++) {

            uint8_t ledNumber = (MATRIX_WIDTH * i) + j;

            if(matrix[i] & (1 << j)) {
                nextFrame[ledNumber].red = red;
                nextFrame[ledNumber].green = green;
                nextFrame[ledNumber].blue = blue;
                nextFrame[ledNumber].draw = true;
                nextFrame[ledNumber].flicker = true;
            }

        }
    }
}

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
void addBitmapToCurrentFrame(const uint16_t matrix[MATRIX_HEIGHT], uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness) {

    //TODO: create function
    // applyBrightness((uint8_t*) red, (uint8_t*) green, (uint8_t*) blue, brightness);

    for(int i = 0; i < MATRIX_HEIGHT; i++) {
        for(int j = 0; j < MATRIX_WIDTH; j++) {

            uint8_t ledNumber = (MATRIX_WIDTH * i) + j;

            if(matrix[i] & (1 << j)) {
                currentFrame[ledNumber].red = red;
                currentFrame[ledNumber].green = green;
                currentFrame[ledNumber].blue = blue;
                currentFrame[ledNumber].draw = true;
                currentFrame[ledNumber].flicker = false;
            }

        }
    }
}

void shuffle(uint8_t *array, uint32_t size) {
    if (size > 1) {
        for (uint32_t i = 0; i < size - 1; i++) {
            uint32_t j = i + rand() / (RAND_MAX / (size - i) + 1);
            uint8_t t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

int randomInRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

void wipeCurrentFrame() {
	for(int i = 0; i < MATRIX_SIZE; i++) {
		currentFrame[i].blue = 0;
		currentFrame[i].green = 0;
		currentFrame[i].red = 0;
	}
}

void wipeNextFrame() {
	for(int i = 0; i < MATRIX_SIZE; i++) {
		nextFrame[i].blue = 0;
		nextFrame[i].green = 0;
		nextFrame[i].red = 0;
	}
}

void advanceFrame() {
    memcpy(currentFrame, nextFrame, sizeof(currentFrame));
    wipeNextFrame();
}

/**
 * @brief   Extracts indices of lit LEDs from the LED buffer.
 *
 * This function iterates through the LED buffer, storing the indices of lit LEDs
 * in the provided array. An LED is considered lit if its red, green, or blue
 * component is nonzero.
 *
 * @param   arr Pointer to an array for storing indices of lit LEDs.
 *            This array should be preallocated by the caller.
 *
 * @return  Number of lit LEDs found. This value represents the size of the updated array.
 */
uint8_t getLitCurrentFrame(uint8_t *arr) {

    uint32_t index = 0;


    for(int i = 0; i < MATRIX_SIZE; i++) {
        if(currentFrame[i].red != 0 || currentFrame[i].green != 0 || currentFrame[i].blue != 0) {
        	if(currentFrame[i].flicker == true) {
                arr[index] = i;
                index++;
        	}
        }
    }

    return index + 1;
}

uint8_t getLitNextFrame(uint8_t *arr) {

    uint32_t index = 0;

    for(int i = 0; i < MATRIX_SIZE; i++) {
        if(nextFrame[i].red != 0 || nextFrame[i].green != 0 || nextFrame[i].blue != 0) {
        	if(nextFrame[i].flicker == true) {
                arr[index] = i;
                index++;
        	}
        }
    }

    return index + 1;
}

uint8_t getLitFromNextFrame(uint8_t *arr) {

    uint32_t index = 0;

    for(int i = 0; i < MATRIX_SIZE; i++) {
        if(nextFrame[i].red != 0 || nextFrame[i].green != 0 || nextFrame[i].blue != 0) {
            arr[index] = i;
            index++;
        }
    }

    return index + 1;
}

uint32_t lastTickFlicker;

bool flickerOutEffectStateMachine(void) {
    static uint8_t litLEDs[MATRIX_SIZE] = {0};
    static uint8_t numLit = 0;
    static uint32_t lastTickEffect = 0;
    static uint8_t loop = 0;
    static bool isInitialized = false;
    const uint8_t flickerLoops = 10;
    const uint32_t delayInterval = 50; // milliseconds

    if (!isInitialized) {
        numLit = getLitCurrentFrame(litLEDs);
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
                turnOffLED((LED *) currentFrame, litLEDs[i]);
            }
            updatePwmBuffer((LED *) currentFrame);
            DMA_Send(); // Update LEDs through DMA
            // Reset for next call or trigger completion
            isInitialized = false; // Reset the state
            return false; // Finish the effect
        }

        shuffle(litLEDs, numLit);
        for (uint8_t i = 0; i < numLit; ++i) {
            if (randomInRange(0, flickerLoops) < loop) {
                turnOffLED((LED *) currentFrame, litLEDs[i]);
            } else {
                turnOnLED((LED *) currentFrame, litLEDs[i]);
            }
        }
        updatePwmBuffer((LED *) currentFrame);
        DMA_Send(); // Update LEDs through DMA
        lastTickEffect = HAL_GetTick();
        loop++;
    }
    return true;
}

bool flickerInEffectStateMachine(void) {
    static uint8_t litLEDs[MATRIX_SIZE] = {0};
    static uint8_t numLit = 0;
    static uint32_t lastTickEffect = 0;
    static uint8_t loop = 0;
    static bool isInitialized = false;
    const uint8_t flickerLoops = 10;
    const uint32_t delayInterval = 50; // milliseconds

    if (!isInitialized) {
        numLit = getLitCurrentFrame(litLEDs);
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
                turnOnLED((LED *) currentFrame, litLEDs[i]);
            }
            updatePwmBuffer((LED *) currentFrame);
            DMA_Send(); // Update LEDs through DMA
            // Reset for next call or trigger completion
            isInitialized = false; // Reset the state
            return false; // Finish the effect
        }

        shuffle(litLEDs, numLit);
        for (uint8_t i = 0; i < numLit; ++i) {
            if (randomInRange(0, flickerLoops) > loop) {
                turnOffLED((LED *) currentFrame, litLEDs[i]);
            } else {
                turnOnLED((LED *) currentFrame, litLEDs[i]);
            }
        }
        updatePwmBuffer((LED *) currentFrame);
        DMA_Send(); // Update LEDs through DMA
        lastTickEffect = HAL_GetTick();
        loop++;
    }
    return true;
}

extern const uint16_t * minuteBitmaps[] = {
		MINUTE_FIVE,
		MINUTE_TEN,
		MINUTE_FIFTEEN,
		MINUTE_TWENTY,
		MINUTE_TWENTYFIVE,
		MINUTE_THIRTY
};

HsvColor lastColor = {0};

void setAnniversary(uint8_t brightness) {


	lastColor.s = 255;
	lastColor.v = brightness;


	lastColor.h = lastColor.h + 5;

	RgbColor rgb = HsvToRgb(lastColor);

	addBitmapToCurrentFrame(BMP_HAPPY, rgb.r, rgb.g, rgb.b, 255);
	addBitmapToCurrentFrame(BMP_ANNIVERSARY, rgb.r, rgb.g, rgb.b, 255);
	addBitmapToCurrentFrame(BMP_KATIEDEREK, rgb.r, rgb.g, rgb.b, 255);

	updatePwmBuffer((LED *) currentFrame);
	DMA_Send();
}

void display_time(int hour, int minute, uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness) {
	addBitmapToNextFrame(BMP_ITS, red, green, blue, brightness);
    // Round down to the nearest five minutes
    minute = (minute / 5) * 5;

    // Display minute, accounting for 'past' or 'to'
    if (minute < 5) {
    	//no past or till
    } else if (minute < 35) {
        addBitmapToNextFrame(BMP_PAST, red, green, blue, brightness);
    } else {
        minute = 60 - minute;
        hour++;
        addBitmapToNextFrame(BMP_TILL, red, green, blue, brightness);
    }

    if(hour == 0 || hour == 12);
    else if(hour < 12) addBitmapToNextFrame(BMP_AM, red, green, blue, brightness);
    else addBitmapToNextFrame(BMP_PM, red, green, blue, brightness);

    // Display hour
    switch(hour) {
        case 0:
            addBitmapToNextFrame(HOUR_MIDNIGHT, red, green, blue, brightness);
            break;
        case 1:
        case 13:
            addBitmapToNextFrame(HOUR_ONE, red, green, blue, brightness);
            break;
        case 2:
        case 14:
            addBitmapToNextFrame(HOUR_TWO, red, green, blue, brightness);
            break;
        case 3:
        case 15:
            addBitmapToNextFrame(HOUR_THREE, red, green, blue, brightness);
            break;
        case 4:
        case 16:
            addBitmapToNextFrame(HOUR_FOUR, red, green, blue, brightness);
            break;
        case 5:
        case 17:
            addBitmapToNextFrame(HOUR_FIVE, red, green, blue, brightness);
            break;
        case 6:
        case 18:
            addBitmapToNextFrame(HOUR_SIX, red, green, blue, brightness);
            break;
        case 7:
        case 19:
            addBitmapToNextFrame(HOUR_SEVEN, red, green, blue, brightness);
            break;
        case 8:
        case 20:
            addBitmapToNextFrame(HOUR_EIGHT, red, green, blue, brightness);
            break;
        case 9:
        case 21:
            addBitmapToNextFrame(HOUR_NINE, red, green, blue, brightness);
            break;
        case 10:
        case 22:
            addBitmapToNextFrame(HOUR_TEN, red, green, blue, brightness);
            break;
        case 11:
        case 23:
            addBitmapToNextFrame(HOUR_ELEVEN, red, green, blue, brightness);
            break;
        case 12:
            addBitmapToNextFrame(HOUR_NOON, red, green, blue, brightness);
            break;
        default:
            // Handle error or invalid hour
            break;
    }

    // Display minute in intervals of five using an array pointing to the bitmaps
    if (minute > 0) {
        addBitmapToNextFrame(minuteBitmaps[(minute / 5) - 1], red, green, blue, brightness);
    }
}

RgbColor HsvToRgb(HsvColor hsv)
{
    RgbColor rgb;
    unsigned char region, remainder, p, q, t;

    if (hsv.s == 0)
    {
        rgb.r = hsv.v;
        rgb.g = hsv.v;
        rgb.b = hsv.v;
        return rgb;
    }

    region = hsv.h / 43;
    remainder = (hsv.h - (region * 43)) * 6;

    p = (hsv.v * (255 - hsv.s)) >> 8;
    q = (hsv.v * (255 - ((hsv.s * remainder) >> 8))) >> 8;
    t = (hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
        case 0:
            rgb.r = hsv.v; rgb.g = t; rgb.b = p;
            break;
        case 1:
            rgb.r = q; rgb.g = hsv.v; rgb.b = p;
            break;
        case 2:
            rgb.r = p; rgb.g = hsv.v; rgb.b = t;
            break;
        case 3:
            rgb.r = p; rgb.g = q; rgb.b = hsv.v;
            break;
        case 4:
            rgb.r = t; rgb.g = p; rgb.b = hsv.v;
            break;
        default:
            rgb.r = hsv.v; rgb.g = p; rgb.b = q;
            break;
    }

    return rgb;
}

HsvColor RgbToHsv(RgbColor rgb)
{
    HsvColor hsv;
    unsigned char rgbMin, rgbMax;

    rgbMin = rgb.r < rgb.g ? (rgb.r < rgb.b ? rgb.r : rgb.b) : (rgb.g < rgb.b ? rgb.g : rgb.b);
    rgbMax = rgb.r > rgb.g ? (rgb.r > rgb.b ? rgb.r : rgb.b) : (rgb.g > rgb.b ? rgb.g : rgb.b);

    hsv.v = rgbMax;
    if (hsv.v == 0)
    {
        hsv.h = 0;
        hsv.s = 0;
        return hsv;
    }

    hsv.s = (255 * (long)(rgbMax - rgbMin)) / hsv.v;
    if (hsv.s == 0)
    {
        hsv.h = 0;
        return hsv;
    }

    if (rgbMax == rgb.r)
        hsv.h = 0 + 43 * (rgb.g - rgb.b) / (rgbMax - rgbMin);
    else if (rgbMax == rgb.g)
        hsv.h = 85 + 43 * (rgb.b - rgb.r) / (rgbMax - rgbMin);
    else
        hsv.h = 171 + 43 * (rgb.r - rgb.g) / (rgbMax - rgbMin);

    return hsv;
}
