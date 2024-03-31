/*
 * effects.h
 *
 *  Created on: Mar 31, 2024
 *      Author: dsava
 */

#ifndef INC_EFFECTS_H_
#define INC_EFFECTS_H_

#include "main.h"
#include "../../Drivers/WS2812B/WS2812B.h"

void shuffle(uint8_t *array, uint32_t size);
int randomInRange(int min, int max);
void wipeCurrentFrame(void);
void wipeNextFrame(void);
void advanceFrame(void);
void flickerOutEffect(void);
void flickerInEffect(void);
void addBitmapToCurrentFrame(const uint16_t matrix[MATRIX_HEIGHT], uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness);
void addBitmapToNextFrame(const uint16_t matrix[MATRIX_HEIGHT], uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness);
uint8_t getLitFromNextFrame(uint8_t *arr);
uint8_t getLitFromCurrentFrame(uint8_t *arr);
void display_time(int hour, int minute, uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness);

#endif /* INC_EFFECTS_H_ */
