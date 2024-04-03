/*
 * Numeric_Display.c
 *
 *  Created on: Jan 25, 2024
 *      Author: dsava
 */

#include "Numeric_Display.h"

char outputBuffer[CHAR_TO_DISPLAY_MAX] = {0};


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
void Segment_Display(const char *input) {

    // Truncate the input to 4 characters
    char truncatedInput[5];
    strncpy(truncatedInput, input, 4);
    truncatedInput[4] = '\0';

    for(uint8_t i = 0; i < 4; i++) {
        activateDigit(i + 1);

		char ch = truncatedInput[i];
        switch(ch) {
        	case '\0':
        		return;
            case '0':
                setSegments(0x3F);
                break;
            case '1':
                setSegments(0x06);
                break;
            case '2':
                setSegments(0x5B);
                break;
            case '3':
                setSegments(0x4F);
                break;
            case '4':
                setSegments(0x66);
                break;
            case '5':
                setSegments(0x6D);
                break;
            case '6':
                setSegments(0x7D);
                break;
            case '7':
                setSegments(0x07);
                break;
            case '8':
                setSegments(0x7F);
                break;
            case '9':
                setSegments(0x6F);
                break;
            case 'a':
            case 'A':
                setSegments(0x77);
                break;
            case 'b':
            case 'B':
                setSegments(0x7C);
                break;
            case 'c':
            case 'C':
                setSegments(0x39);
                break;
            case 'd':
            case 'D':
                setSegments(0x5E);
                break;
            case 'e':
            case 'E':
                setSegments(0x79);
                break;
            case 'f':
            case 'F':
                setSegments(0x71);
                break;
            case 'g':
            case 'G':
                setSegments(0x3D);
                break;
            case 'h':
            case 'H':
                setSegments(0x76);
                break;
            case 'i':
            case 'I':
                setSegments(0x30);
                break;
            case 'j':
            case 'J':
                setSegments(0x1E);
                break;
            case 'k':
            case 'K':
                // Using same as 'H', no unique representation for 'K'
                setSegments(0x76);
                break;
            case 'l':
            case 'L':
                setSegments(0x38);
                break;
            case 'm':
            case 'M':
                // 'M' uses same as 'n', no unique representation
                setSegments(0x37);
                break;
            case 'n':
            case 'N':
                setSegments(0x54);
                break;
            case 'o':
            case 'O':
                setSegments(0x3F);
                break;
            case 'p':
            case 'P':
                setSegments(0x73);
                break;
            case 'q':
            case 'Q':
                setSegments(0x67);
                break;
            case 'r':
            case 'R':
                setSegments(0x50);
                break;
            case 's':
            case 'S':
                setSegments(0x6D);
                break;
            case 't':
            case 'T':
                setSegments(0x78);
                break;
            case 'u':
            case 'U':
                setSegments(0x3E);
                break;
            case 'v':
            case 'V':
                // Using same as 'U', no unique representation for 'V'
                setSegments(0x3E);
                break;
            case 'w':
            case 'W':
                // Representation of 'W' is not possible, so using compromise
                setSegments(0x2A);
                break;
            case 'x':
            case 'X':
                // Using same as 'H', no unique representation for 'X'
                setSegments(0x76);
                break;
            case 'y':
            case 'Y':
                setSegments(0x6E);
                break;
            case 'z':
            case 'Z':
                // 'Z' uses same as '2'
                setSegments(0x5B);
                break;
            case ' ':
                // Blank character
                setSegments(0x00);
                break;
            case '-':
            	setSegments(0x04);
            	break;
            default:
            	setSegments(0x00);
                break;
        }
        HAL_Delay(5);
    }
}
