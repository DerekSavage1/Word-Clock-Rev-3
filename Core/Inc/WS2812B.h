/*
 * WS2812B.h
 *
 *  Created on: Jan 25, 2024
 *      Author: dsava
 */

#ifndef WS2812B_WS2812B_H_
#define WS2812B_WS2812B_H_

#include "main.h"
#include "stdbool.h"
#include "matrix.h"
#include <string.h>


typedef enum {
	NONE,
	RAINBOW,
	FLICKER,
	TWINKLE,
	BLINK,
	CONSTANT
} Effect;

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    Effect effect;
    bool on;
} LED;

#define MATRIX_SIZE (MATRIX_HEIGHT * MATRIX_WIDTH)

#define ONE (0.60 * 90)  // 60% duty cycle, adjust the base unit as per your PWM frequency
#define ZERO (0.30 * 90) // 30% duty cycle, adjust the base unit as per your PWM frequency
#define NUM_LEDS 141
#define RESET_SLOTS 50  // Number of slots for reset signal. Update if needed.

#define PWM_ARRAY_SIZE (MATRIX_SIZE * 24 + RESET_SLOTS)

void DMA_Send(void);
void wipePWMBuffer(void);
void updatePwmBuffer(LED *currentFrame);
void turnOffLED(LED *frame, uint8_t index);
void turnOnLED(LED *frame, uint8_t index);
void toggleLED(LED *frame, uint8_t index);
bool isLEDOn(LED *frame, uint8_t index);
void removeLED(LED *frame, uint8_t index);
uint8_t getLEDsWithEffect(uint8_t *result, LED *display, Effect effect);

#endif /* WS2812B_WS2812B_H_ */
