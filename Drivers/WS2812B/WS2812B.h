/*
 * WS2812B.h
 *
 *  Created on: Jan 25, 2024
 *      Author: dsava
 */

#ifndef WS2812B_WS2812B_H_
#define WS2812B_WS2812B_H_

#include <stdint.h>
#include "../Inc/main.h"

#define ONE (0.60 * 90)  // 60% duty cycle, adjust the base unit as per your PWM frequency
#define ZERO (0.30 * 90) // 30% duty cycle, adjust the base unit as per your PWM frequency
#define NUM_LEDS 141
#define RESET_SLOTS 50  // Number of slots for reset signal. Update if needed.

void Set_LED(int, int, int, int);
void Set_LED_Hex(int, uint32_t);
void WS2812B_Send();

#endif /* WS2812B_WS2812B_H_ */
