/*
 * blink.h
 *
 *  Created on: Apr 4, 2024
 *      Author: dsava
 */

#ifndef INC_BLINK_H_
#define INC_BLINK_H_

#include "main.h"
#include "WS2812B.h"
#include "display.h"

void blink(void);
void blinkOneLED(const uint16_t matrix[]);

#endif /* INC_BLINK_H_ */
