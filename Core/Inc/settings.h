/*
 * settings.h
 *
 *  Created on: Apr 2, 2024
 *      Author: dsava
 */

#ifndef INC_SETTINGS_H_
#define INC_SETTINGS_H_

#include <stdint.h>
#include "main.h"
#include "color.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include "ws2812b.h"
#include "display.h"


#define MAX_STRING_LENGTH 10
#define SENSITIVITY 10

typedef enum {
  SLEEP,
  WAKE,
  SELECT,
  SET_HOURS,
  SET_MINUTES,
  SET_COLOR,
  SET_BRIGHTNESS,
  SET_MONTH,
  SET_DAY,
  SET_YEAR,
} DeviceState;

typedef enum DateType {
  SYSTEM_DATE,
  ANNIVERSARY_DATE,
  BIRTHDAY_DATE
} DateType;

typedef enum Mode {
	DELETE_MODE,
	SET_MODE
} Mode;



DeviceState getDeviceState(void);
void setDeviceState(DeviceState);
uint32_t getSelected(void);
void setCounter(uint32_t _counter);
RTC_TimeTypeDef* getTime(void);
void setColor(RgbColor _color);
RgbColor getColor(void);
DateType getDateState(void);
RTC_DateTypeDef* getDate(DateType type);
void setDateState(DateType _dateState);
uint8_t getBrightnessAsPercent(void);
void setBrightnessAsPercent(uint8_t _brightness);
uint32_t getCounterWithinBounds(uint32_t _minVal, uint32_t _maxVal);
uint32_t getCounter(void);
void setMode(Mode _mode);
Mode getMode(void);
uint8_t getBrightnessAsPercent(void);
char *getDisplayString(void);
void setDisplayString(const char *format, ...);
uint32_t clamp(uint32_t value, uint32_t minVal, uint32_t maxVal);
void setCounterBounds(uint32_t minVal, uint32_t maxVal);
void setColorWithPreset(uint32_t preset);
RgbColor getColor(void);
void setDate(RTC_DateTypeDef tDate, DateType type);
uint8_t getColorPreset(void);
bool isAnniversarySet(void);
bool isBirthdaySet(void);
void deleteBirthday(void);
void deleteAnniversary(void);
uint8_t getBrightness(void);


#endif /* INC_SETTINGS_H_ */
