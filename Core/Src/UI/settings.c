/*
 * configuration.c
 *
 *  Created on: Apr 2, 2024
 *      Author: dsava
 */

#include "settings.h"

static DeviceState currentState = SLEEP;
static uint32_t counter = 0;
static uint32_t sensitivity = 10;

static Mode mode = SET_MODE;

RgbColor color;

extern RTC_TimeTypeDef sTime;
extern RTC_DateTypeDef sDate;
extern RTC_DateTypeDef aDate;
extern RTC_DateTypeDef bDate;

uint8_t brightness = 50;

DateType dateState = SYSTEM_DATE;

DeviceState getDeviceState(void) {
	return currentState;
}

void setDeviceState(DeviceState _currentState) {
	currentState = _currentState;
}

uint32_t getCounter(void) {
	return counter;
}

void setCounter(uint32_t _counter) {
	counter = _counter * sensitivity;
}

uint32_t getSelected(void) {
	return counter / sensitivity;
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

