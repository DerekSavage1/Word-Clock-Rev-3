/*
 * display.h
 *
 *  Created on: Apr 2, 2024
 *      Author: dsava
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include <ws2812b.h>
#include "matrix.h"
#include "color.h"
#include "settings.h"

extern LED targetDisplay[MATRIX_SIZE];
extern LED currentDisplay[MATRIX_SIZE];

void addBitmapToDisplay(const uint16_t matrix[MATRIX_HEIGHT], LED *display, Effect effect);
void advanceDisplay(Effect effect);
void sendDisplayToDMA(void);
void updateDisplayColor(void);
void removeBitmapFromDisplay(const uint16_t matrix[MATRIX_HEIGHT], LED *display);

#endif /* INC_DISPLAY_H_ */
