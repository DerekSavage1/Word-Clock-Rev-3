/*
 * effects.h
 *
 *  Created on: Mar 31, 2024
 *      Author: dsava
 */

#ifndef INC_EFFECTS_H_
#define INC_EFFECTS_H_

#include "main.h"
#include "color.h"
#include "WS2812B.h"
#include "display.h"
#include "random.h"

void shuffleArray(uint8_t *array, uint32_t size);
int randomInRange(int min, int max);
void wipeCurrentDisplay(void);
void wipeNextDisplay(void);
void advanceDisplay(void);
bool flickerOut(void);
bool flickerIn(void);
void checkUpdateTime(RTC_TimeTypeDef currentTime);
void updateDisplay(RTC_TimeTypeDef currentTime);
uint8_t getLitFromNextDisplay(uint8_t *arr);
uint8_t getLitFromCurrentDisplay(uint8_t *arr);
void display_time(int hour, int minute, RgbColor color);
void setAnniversary(uint8_t brightness);
RgbColor HsvToRgb(HsvColor hsv);
HsvColor RgbToHsv(RgbColor rgb);
void addBitmapToDisplay(const uint16_t matrix[MATRIX_HEIGHT], LED *display, RgbColor color, Effect effect);




#endif /* INC_EFFECTS_H_ */
