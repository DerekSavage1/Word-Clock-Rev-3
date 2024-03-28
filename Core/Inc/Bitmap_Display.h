/*
 * Bitmap_Display.h
 *
 *  Created on: Jan 25, 2024
 *      Author: dsava
 */

#ifndef INC_BITMAP_DISPLAY_H_
#define INC_BITMAP_DISPLAY_H_

#include "main.h"
#include "matrix.h"
#include "../../Drivers/WS2812B/WS2812B.h"
#include <stdint.h>

// Get a 24-bit RGB color based on a preset option
uint32_t getRainbowColor(uint8_t colorOption);

// Array of pointers to bitmaps representing minutes
extern const uint16_t *minuteBitmaps[];

// Buffer representing the state of each LED to be displayed
extern unsigned char displayBuffer[12][11];

// Clear the display buffer
void clear_display_buffer();

// Add a bitmap to the display buffer
void add_bmp(const uint16_t bmp[12]);

// Display the bitmap using a set color
void display_bmp(uint8_t preset, uint8_t color);

// Display time on the bitmap display
void display_time(int hour, int minute);



#endif /* INC_BITMAP_DISPLAY_H_ */
