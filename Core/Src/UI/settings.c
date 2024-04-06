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
RgbColor brightnessColor;
uint8_t colorSelection;

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
	setCounterBounds(0,-1);
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

void setDate(RTC_DateTypeDef tDate, DateType type) {
    switch(type) {
        case SYSTEM_DATE:
            sDate = tDate;
            break;
        case ANNIVERSARY_DATE:
        	tDate.Year = 0;
            aDate = tDate;
            break;
        case BIRTHDAY_DATE:
        	tDate.Year = 0;
            bDate = tDate;
            break;
        default:
        	break;
    }
}

void setColor(RgbColor _color) {
	color = _color;
}

RgbColor getColor(void) {
	const uint8_t gamma_lut[256] = {
	     1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
	     1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   3,   3,   3,   3,   4,   4,
	     4,   4,   5,   5,   5,   5,   6,   6,   6,   7,   7,   7,   8,   8,   8,   9,
	     9,   9,  10,  10,  11,  11,  11,  12,  12,  13,  13,  14,  14,  15,  15,  16,
	    16,  17,  17,  18,  18,  19,  19,  20,  20,  21,  21,  22,  23,  23,  24,  24,
	    25,  26,  26,  27,  28,  28,  29,  30,  30,  31,  32,  32,  33,  34,  35,  35,
	    36,  37,  38,  38,  39,  40,  41,  42,  42,  43,  44,  45,  46,  47,  47,  48,
	    49,  50,  51,  52,  53,  54,  55,  56,  56,  57,  58,  59,  60,  61,  62,  63,
	    64,  65,  66,  67,  68,  69,  70,  71,  73,  74,  75,  76,  77,  78,  79,  80,
	    81,  82,  84,  85,  86,  87,  88,  89,  91,  92,  93,  94,  95,  97,  98,  99,
	   100, 102, 103, 104, 105, 107, 108, 109, 111, 112, 113, 115, 116, 117, 119, 120,
	   121, 123, 124, 126, 127, 128, 130, 131, 133, 134, 136, 137, 139, 140, 142, 143,
	   145, 146, 148, 149, 151, 152, 154, 155, 157, 158, 160, 162, 163, 165, 166, 168,
	   170, 171, 173, 175, 176, 178, 180, 181, 183, 185, 186, 188, 190, 192, 193, 195,
	   197, 199, 200, 202, 204, 206, 207, 209, 211, 213, 215, 217, 218, 220, 222, 224,
	   226, 228, 230, 232, 233, 235, 237, 239, 241, 243, 245, 247, 249, 251, 253, 255,
	  };

	uint8_t corrected_brightness = gamma_lut[brightness];

	RgbColor _color;

	_color.r = (uint8_t) ((double) gamma_lut[color.r] * (double) ((double) corrected_brightness / (double) 255.0));
	_color.g = (uint8_t) ((double) gamma_lut[color.g] * (double) ((double) corrected_brightness / (double) 255.0));
	_color.b = (uint8_t) ((double) gamma_lut[color.b] * (double) ((double) corrected_brightness  / (double) 255.0));

	return _color;
}

DateType getDateState(void) {
	return dateState;
}

void setDateState(DateType _dateState) {
	dateState = _dateState;
}

uint8_t getBrightnessAsPercent(void) {
	return (brightness * 100) / 255;
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

uint8_t getColorPreset(void) {
	return (colorSelection * 100) / 255;
}

void setColorWithPreset(uint32_t selection) {

	if(selection == 0) {
		color.r = 0xFF;
		color.g = 0xFF;
		color.b = 0xFF;
	} else {
		colorSelection = (selection * 255) / 100;

	    HsvColor hsv;
	    hsv.s = 255;
	    hsv.v = 255;
	    hsv.h = colorSelection;

	    color = hsvToRgb(hsv);

	}
}

void setBrightnessAsPercent(uint8_t _brightness) {
	brightness = (_brightness * 255) / 100;
}

bool isAnniversarySet(void) {
	return !(aDate.Year == 99);
}

bool isBirthdaySet(void) {
	return !(bDate.Year == 99);
}

void deleteAnniversary(void) {
	RTC_DateTypeDef tDate = {0, 0, 0, 99};
	aDate = tDate;
}

void deleteBirthday(void) {
	RTC_DateTypeDef tDate = {0, 0, 0, 99};
	bDate = tDate;
}
