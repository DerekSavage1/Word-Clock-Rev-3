/*
 * configuration.c
 *
 *  Created on: Apr 2, 2024
 *      Author: dsava
 */

#include "settings.h"

extern LED currentDisplay[];
extern TIM_HandleTypeDef htim3;

static DeviceState currentState = SLEEP;
static uint32_t counter = 0;
static Mode mode = SET_MODE;
RgbColor color;
extern RTC_TimeTypeDef sTime;
extern RTC_DateTypeDef sDate;
extern RTC_DateTypeDef aDate;
extern RTC_DateTypeDef bDate;
uint8_t brightness = 50;
DateType dateState = SYSTEM_DATE;
char displayStr[MAX_STRING_LENGTH];
static uint32_t minVal = 0;
static uint32_t maxVal = 2000; // (2^32 - 1)
RgbColor color;

#define UNDERFLOW_TRIGGER 65500

uint32_t clamp(uint32_t value, uint32_t minVal, uint32_t maxVal) {

	if(value > UNDERFLOW_TRIGGER) return minVal;

	if (value < minVal) return minVal;
	if (value > maxVal) return maxVal;
	return value;
}

void setCounterBounds(uint32_t _minVal, uint32_t _maxVal) {
	minVal = _minVal;
	maxVal = _maxVal;
}

DeviceState getDeviceState(void) {
	return currentState;
}

void setDeviceState(DeviceState _currentState) {
	currentState = _currentState;
}

uint32_t getCounter(void) {
	setCounter(clamp(__HAL_TIM_GET_COUNTER(&htim3), minVal, maxVal));
	return clamp(__HAL_TIM_GET_COUNTER(&htim3), minVal, maxVal);
}

uint32_t getCounterWithinBounds(uint32_t _minVal, uint32_t _maxVal) {
	minVal = _minVal;
	maxVal = _maxVal;
	setCounter(clamp(__HAL_TIM_GET_COUNTER(&htim3), minVal, maxVal));
	return clamp(__HAL_TIM_GET_COUNTER(&htim3), minVal, maxVal);
}

void setCounter(uint32_t _counter) {
	counter = clamp(_counter, minVal, maxVal);
	__HAL_TIM_SET_COUNTER(&htim3, clamp(_counter, minVal, maxVal));
}

uint32_t getSelected(void) {
	return counter;
}

RTC_TimeTypeDef* getTime(void) {
	return &sTime;
}

RTC_DateTypeDef* getDate(DateType type) {
	switch(type) {
		case SYSTEM_DATE:
			return &sDate;
		case ANNIVERSARY_DATE:
			return &aDate;
		case BIRTHDAY_DATE:
			return &bDate;
		default:
			return &sDate;
	}
}

void setColor(RgbColor _color) {
	color = _color;
}

RgbColor getColor(void) {
	return color;
}

DateType getDateState(void) {
	return dateState;
}

void setDateState(DateType _dateState) {
	dateState = _dateState;
}

uint8_t getBrightness(void) {
	return brightness;
}

void setMode(Mode _mode) {
	mode = _mode;
}

Mode getMode(void) {
	return mode;
}

char *getDisplayString(void) {
	return (char *) displayStr;
}

void setDisplayString(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vsnprintf(displayStr, MAX_STRING_LENGTH, format, args);
    va_end(args);
}

void setColorWithPreset(uint32_t preset) {
    switch (preset) {
        case 1:
            color.r = 255; // r
            color.g = 0;
            color.b = 0;
            break;
        case 2:
            color.r = 255; // Orange
            color.g = 165;
            color.b = 0;
            break;
        case 3:
            color.r = 255; // Yellow
            color.g = 255;
            color.b = 0;
            break;
        case 4:
            color.r = 0; // g
            color.g = 255;
            color.b = 0;
            break;
        case 5:
            color.r = 0; // b
            color.g = 0;
            color.b = 255;
            break;
        case 6:
            color.r = 75; // Indigo
            color.g = 0;
            color.b = 130;
            break;
        case 7:
            color.r = 128; // Violet
            color.g = 0;
            color.b = 128;
            break;
        case 8:
            color.r = 255; // r-Orange
            color.g = 69;
            color.b = 0;
            break;
        case 9:
            color.r = 255; // Orange-Yellow
            color.g = 215;
            color.b = 0;
            break;
        case 10:
            color.r = 154; // Yellow-g
            color.g = 205;
            color.b = 50;
            break;
        case 11:
            color.r = 0; // g-b
            color.g = 255;
            color.b = 255;
            break;
        case 12:
            color.r = 138; // b-Indigo
            color.g = 43;
            color.b = 226;
            break;
        case 13:
            color.r = 186; // Indigo-Violet
            color.g = 85;
            color.b = 211;
            break;
        case 14:
            color.r = 255; // Violet-r
            color.g = 0;
            color.b = 255;
            break;
        case 15:
            color.r = 255; // Pink
            color.g = 192;
            color.b = 203;
            break;
        case 16:
            color.r = 255; // White
            color.g = 255;
            color.b = 255;
            break;
        default:
            color.r = 255; // White for an undefined preset
            color.g = 255;
            color.b = 255;
    }

    //workaround because otherwise the color would only update when display_time is called, which is currently only while flickering
    uint8_t leds[MATRIX_SIZE];

    uint32_t size = getLEDsWithEffect((uint8_t *) leds, (LED *) currentDisplay, FLICKER);

    for(int i = 0; i < size; i++) {
		currentDisplay[leds[i]].red = color.r;
		currentDisplay[leds[i]].blue = color.g;
		currentDisplay[leds[i]].green = color.b;
    }

    size = getLEDsWithEffect((uint8_t *) leds, (LED *) currentDisplay, TWINKLE);

    for(int i = 0; i < size; i++) {
		currentDisplay[leds[i]].red = color.r;
		currentDisplay[leds[i]].blue = color.g;
		currentDisplay[leds[i]].green = color.b;
    }


}

void setBrightness(uint32_t _brightness) {

	HsvColor hsv = rgbToHsv(color);

	hsv.v = (_brightness * 255) / 100;

	color = hsvToRgb(hsv);

    uint8_t leds[MATRIX_SIZE];

    uint32_t size = getLEDsWithEffect((uint8_t *) leds, (LED *) currentDisplay, FLICKER);

    for(int i = 0; i < size; i++) {
		currentDisplay[leds[i]].red = color.r;
		currentDisplay[leds[i]].blue = color.g;
		currentDisplay[leds[i]].green = color.b;
    }

    size = getLEDsWithEffect((uint8_t *) leds, (LED *) currentDisplay, TWINKLE);

    for(int i = 0; i < size; i++) {
		currentDisplay[leds[i]].red = color.r;
		currentDisplay[leds[i]].blue = color.g;
		currentDisplay[leds[i]].green = color.b;
    }

}
