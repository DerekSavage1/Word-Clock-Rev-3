/*
 * Bitmap_Display.c
 *
 *  Created on: Jan 25, 2024
 *      Author: dsava
 */

#include "Bitmap_Display.h"

// Gamma brightness lookup table <https://victornpb.github.io/gamma-table-generator>
// gamma = 2.00 steps = 100 range = 0-1023
const uint16_t gamma_lut[100] = {
     0,   0,   0,   1,   2,   3,   4,   5,   7,   8,  10,  13,  15,  18,  20,  23,
    27,  30,  34,  38,  42,  46,  51,  55,  60,  65,  71,  76,  82,  88,  94, 100,
   107, 114, 121, 128, 135, 143, 151, 159, 167, 175, 184, 193, 202, 211, 221, 231,
   240, 251, 261, 271, 282, 293, 304, 316, 327, 339, 351, 363, 376, 388, 401, 414,
   428, 441, 455, 469, 483, 497, 511, 526, 541, 556, 572, 587, 603, 619, 635, 651,
   668, 685, 702, 719, 736, 754, 772, 790, 808, 827, 845, 864, 883, 903, 922, 942,
   962, 982,1002,1023,};

uint32_t getRainbowColor(uint8_t colorOption) {
    switch (colorOption) {
        case 1:
            return 0xFF0000; // Red
        case 2:
            return 0xFF7F00; // Orange
        case 3:
            return 0xFFFF00; // Yellow
        case 4:
            return 0x7FFF00; // Yellow-Green
        case 5:
            return 0x00FF00; // Green
        case 6:
            return 0x00FF7F; // Spring Green
        case 7:
            return 0x00FFFF; // Cyan
        case 8:
            return 0x007FFF; // Sky Blue
        case 9:
            return 0x0000FF; // Blue
        case 10:
            return 0x7F00FF; // Violet
        case 11:
            return 0xFF00FF; // Magenta
        case 12:
            return 0xFF007F; // Rose
        case 13:
            return 0xFF1493; // Deep Pink
        case 14:
            return 0xC71585; // Medium Violet Red
        case 15:
            return 0x800080; // Purple
        case 16:
            return 0x8B008B; // Dark Magenta
        default:
            return 0xFFFFFF; // Default to White if an unexpected value is provided
    }
}


//void display_time(int hour, int minute) {
//	add_bmp(BMP_ITS);
//    // Round down to the nearest five minutes
//    minute = (minute / 5) * 5;
//
//    // Display minute, accounting for 'past' or 'to'
//    if (minute < 5) {
//    	//no past or till
//    } else if (minute < 35) {
//        add_bmp(BMP_PAST);
//    } else {
//        minute = 60 - minute;
//        hour++;
//        add_bmp(BMP_TILL);
//    }
//
//    if(hour == 0 || hour == 12);
//    else if(hour < 12) add_bmp(BMP_AM);
//    else add_bmp(BMP_PM);
//
//    // Display hour
//    switch(hour) {
//        case 0:
//            add_bmp(HOUR_MIDNIGHT);
//            break;
//        case 1:
//        case 13:
//            add_bmp(HOUR_ONE);
//            break;
//        case 2:
//        case 14:
//            add_bmp(HOUR_TWO);
//            break;
//        case 3:
//        case 15:
//            add_bmp(HOUR_THREE);
//            break;
//        case 4:
//        case 16:
//            add_bmp(HOUR_FOUR);
//            break;
//        case 5:
//        case 17:
//            add_bmp(HOUR_FIVE);
//            break;
//        case 6:
//        case 18:
//            add_bmp(HOUR_SIX);
//            break;
//        case 7:
//        case 19:
//            add_bmp(HOUR_SEVEN);
//            break;
//        case 8:
//        case 20:
//            add_bmp(HOUR_EIGHT);
//            break;
//        case 9:
//        case 21:
//            add_bmp(HOUR_NINE);
//            break;
//        case 10:
//        case 22:
//            add_bmp(HOUR_TEN);
//            break;
//        case 11:
//        case 23:
//            add_bmp(HOUR_ELEVEN);
//            break;
//        case 12:
//            add_bmp(HOUR_NOON);
//            break;
//        default:
//            // Handle error or invalid hour
//            break;
//    }
//
//    // Display minute in intervals of five using an array pointing to the bitmaps
//    if (minute > 0) {
//        add_bmp(minuteBitmaps[(minute / 5) - 1]);
//    }
//}

