/*
 * WS2812B.h
 *
 *  Created on: Jan 25, 2024
 *      Author: dsava
 */

#ifndef WS2812B_WS2812B_H_
#define WS2812B_WS2812B_H_

#include "../Inc/main.h"
#include "../Inc/matrix.h"
#include <string.h>

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    bool draw;
} LED;

#define MATRIX_SIZE (MATRIX_HEIGHT * MATRIX_WIDTH)

#define ONE (0.60 * 90)  // 60% duty cycle, adjust the base unit as per your PWM frequency
#define ZERO (0.30 * 90) // 30% duty cycle, adjust the base unit as per your PWM frequency
#define NUM_LEDS 141
#define RESET_SLOTS 50  // Number of slots for reset signal. Update if needed.

#define PWM_ARRAY_SIZE (MATRIX_SIZE * 24 + RESET_SLOTS)

void Set_LED(uint8_t, uint8_t, uint8_t, uint8_t);
void Set_LED_Hex(uint8_t, uint32_t);
void DMA_Send();
void updatePwmBuffer(LED *currentFrame);
void turnOffLED(LED *currentFrame, uint8_t number);
void turnOnLED(LED *currentFrame, uint8_t number);



#endif /* WS2812B_WS2812B_H_ */
