/*
 * Numeric_Display.c
 *
 *  Created on: Jan 25, 2024
 *      Author: dsava
 */

#include "Numeric_Display.h"



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
		['.'] = 0x80, // Decimal point assuming it's on a separate segment
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


// Display up to four characters on the 7-segment displays
void Segment_Display(const char* input) {

	char output[6] = "";  // Assuming maximum input length of 5 digits + null terminator
	bool hasColon = false;

	for (int i = 0; i < strlen(input); i++) {
		if (input[i] != ':') {
			int len = strlen(output);
			output[len] = input[i];
			output[len + 1] = '\0';
		}
		else {
			hasColon = true;
		}
	}


  // clearing all digits
  HAL_GPIO_WritePin(GPIOB, DIG_1_A_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, DIG_2_A_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, DIG_3_A_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, DIG_4_A_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, DEC_A_Pin,   GPIO_PIN_RESET);

  uint8_t numChars = MIN(strlen(output), NUM_DIGITS);
  for (int i = 0; i < (numChars + hasColon); i++) {
	  activateDigit(i + 1); // Activate the correct digit
	  if((i + 1) == 5) { //colon
		  setSegments(0b11);
	  } else {
		  setSegments(charToSegmentsMap[(uint8_t) output[i]]); // Set the correct segments
	  }
	  HAL_Delay(1); // Delay to allow the segments to light up
  }
  activateDigit(0); // Turn off all digits
}
