/*
 * time_display.h
 *
 *  Created on: Apr 2, 2024
 *      Author: dsava
 */

#ifndef INC_TIME_DISPLAY_H_
#define INC_TIME_DISPLAY_H_

#include <stdint.h>
#include <ws2812b.h>
#include "matrix.h"
#include "color.h"
#include "display.h"
#include "settings.h"

extern const uint16_t *hourBitmaps[];
extern const uint16_t *minuteBitmaps[];

void display_birthday(void);
void display_anniversary(void);
void display_time(uint8_t hour, uint8_t minute);
void display_date();

#endif /* INC_TIME_DISPLAY_H_ */
