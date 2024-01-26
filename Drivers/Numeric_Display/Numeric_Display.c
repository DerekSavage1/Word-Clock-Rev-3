/*
 * Numeric_Display.c
 *
 *  Created on: Jan 25, 2024
 *      Author: dsava
 */

#include "Numeric_Display.h"

char outputBuffer[CHAR_TO_DISPLAY_MAX] = {0};

// Segment definitions for numbers and some characters in hexadecimal
const uint8_t charToSegmentsMap[] = {
		['0'] = 0x3F, ['1'] = 0x06, ['2'] = 0x5B, ['3'] = 0x4F,
		['4'] = 0x66, ['5'] = 0x6D, ['6'] = 0x7D, ['7'] = 0x07,
		['8'] = 0x7F, ['9'] = 0x6F, ['A'] = 0x77, ['B'] = 0x7C,
		['C'] = 0x39, ['D'] = 0x5E, ['E'] = 0x79, ['F'] = 0x71,
		['G'] = 0x3D, ['H'] = 0x76, ['I'] = 0x30, ['J'] = 0x1E,
		['K'] = 0x76, // Using same as 'H', no unique representation for 'K'
		['L'] = 0x38, ['M'] = 0x37, // 'M' uses same as 'n', no unique representation
		['N'] = 0x54, ['O'] = 0x3F, ['P'] = 0x73, ['Q'] = 0x67,
		['R'] = 0x50, ['S'] = 0x6D, ['T'] = 0x78, ['U'] = 0x3E,
		['V'] = 0x3E, // Using same as 'U', no unique representation for 'V'
		['W'] = 0x2A, // Representation of 'W' is not possible, so using compromise
		['X'] = 0x76, // Using same as 'H', no unique representation for 'X'
		['Y'] = 0x6E, ['Z'] = 0x5B,  // 'Z' uses same as '2'
		[' '] = 0x00, // Blank character
};

// Set the segments for the current digit
void setSegments(uint8_t segments) {
  HAL_GPIO_WritePin(GPIOA, SEG_A_K_Pin, (segments & (1 << 0)) ? GPIO_PIN_RESET : GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, SEG_B_K_Pin, (segments & (1 << 1)) ? GPIO_PIN_RESET : GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, SEG_C_K_Pin, (segments & (1 << 2)) ? GPIO_PIN_RESET : GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, SEG_D_K_Pin, (segments & (1 << 3)) ? GPIO_PIN_RESET : GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, SEG_E_K_Pin, (segments & (1 << 4)) ? GPIO_PIN_RESET : GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, SEG_F_K_Pin, (segments & (1 << 5)) ? GPIO_PIN_RESET : GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, SEG_G_K_Pin, (segments & (1 << 6)) ? GPIO_PIN_RESET : GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, DP_K_Pin, 	(segments & (1 << 7)) ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

// Activate a single digit
void activateDigit(uint8_t digit) {
  HAL_GPIO_WritePin(GPIOB, DIG_1_A_Pin, digit == 1 ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, DIG_2_A_Pin, digit == 2 ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, DIG_3_A_Pin, digit == 3 ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, DIG_4_A_Pin, digit == 4 ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, DEC_A_Pin,   digit == 5 ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

// Prevent errors by formatting string
void processInput(const char *input) {
    size_t inputLength = strlen(input);

    // We are assuming that outputBuffer is large enough to hold all digits
    memset(outputBuffer, 0, sizeof(outputBuffer)); // Clear the output buffer

    for (size_t i = 0, j = 0; i < inputLength && j < NUM_DIGITS; ++i) {
        // Convert lowercase letters to uppercase
        uint8_t c = (uint8_t)toupper((unsigned char)input[i]); // Cast to avoid potential negative values

        if (c == ':') {
            // If colon, handle separately
            continue;
        }
        if (c < ' ' || c > 'Z' || charToSegmentsMap[c] == 0) {
            // Replace invalid character with 'E'
            outputBuffer[j++] = 'E';
        } else {
            // Copy valid character to output buffer
            outputBuffer[j++] = c; // Now 'c' contains the uppercase version, if applicable
        }
    }

    // Null-termination is ensured by static buffer initialization to {0}
}

// Display up to four characters on the 7-segment displays
void Segment_Display(const char *input) {
    processInput(input);
    bool hasColon = strchr(input, ':') != NULL; // Check if input contains a colon

    // Clearing all digits can be optimized out if carefully controlling the display digits
    // activateDigit(0); // Assuming the digits are off to begin with

    // Calculate the number of characters to display
    size_t numChars = strlen(outputBuffer);
    for (size_t i = 0; i < numChars; i++) {
        activateDigit(i + 1); // Activate the correct digit
        setSegments(charToSegmentsMap[(uint8_t)outputBuffer[i]]); // Set segments
        HAL_Delay(1); // Delay to allow the segments to light up
    }

    if (hasColon) {
        // Handle case for the colon display
        activateDigit(5); // Assuming the fifth "digit" is for the colon
        setSegments(0b11); // Set segments to display the colon
        HAL_Delay(1);
    }

    activateDigit(0); // Turn off all digits after showing the sequence
}
