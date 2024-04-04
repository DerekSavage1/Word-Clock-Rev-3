/*
 * configuration.c
 *
 *  Created on: Apr 2, 2024
 *      Author: dsava
 */

#include "settings.h"

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
uint32_t minVal = 0;
uint32_t maxVal = 4294967295; // (2^32 - 1)

uint32_t clamp(uint32_t value, uint32_t minVal, uint32_t maxVal) {
	// Normal range (does not wrap around)
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
	return clamp(counter, minVal, maxVal);
}

void setCounter(uint32_t _counter) {

    if (_counter > maxVal) {
        counter = minVal;
    } else {
        counter = clamp(_counter, minVal, maxVal);
    }

	counter = clamp(_counter, minVal, maxVal);
	__HAL_TIM_SET_COUNTER(&htim3, counter);
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

void setBrightness(uint8_t _brightness) {
	brightness = _brightness;
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
