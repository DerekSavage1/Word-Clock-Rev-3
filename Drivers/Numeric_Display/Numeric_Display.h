/*
 * Numeric_Display.h
 *
 *  Created on: Jan 25, 2024
 *      Author: dsava
 */

#ifndef NUMERIC_DISPLAY_NUMERIC_DISPLAY_H_
#define NUMERIC_DISPLAY_NUMERIC_DISPLAY_H_

#include <stdint.h>
#include "main.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define NUM_DIGITS 4
#define CHAR_TO_DISPLAY_MAX (NUM_DIGITS + 1) // For additional colon
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

extern char outputBuffer[CHAR_TO_DISPLAY_MAX];
extern const uint8_t charToSegmentsMap[];

void setSegments(uint8_t segments);
void activateDigit(uint8_t digit);
void processInput(const char *input);
void Segment_Display(const char *input);


#endif /* NUMERIC_DISPLAY_NUMERIC_DISPLAY_H_ */
