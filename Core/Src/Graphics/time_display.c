/*
 * time_display.c
 *
 *  Created on: Apr 2, 2024
 *      Author: dsava
 */

#include "time_display.h"

extern LED targetDisplay[MATRIX_SIZE];
extern LED currentDisplay[MATRIX_SIZE];

const uint16_t *hourBitmaps[] = {
		HOUR_MIDNIGHT,
		HOUR_ONE,
		HOUR_TWO,
		HOUR_THREE,
		HOUR_FOUR,
		HOUR_FIVE,
		HOUR_SIX,
		HOUR_SEVEN,
		HOUR_EIGHT,
		HOUR_NINE,
		HOUR_TEN,
		HOUR_ELEVEN,
		HOUR_NOON
};

const uint16_t *minuteBitmaps[] = {
		MINUTE_FIVE,
		MINUTE_TEN,
		MINUTE_FIFTEEN,
		MINUTE_TWENTY,
		MINUTE_TWENTYFIVE,
		MINUTE_THIRTY
};

void display_time(int hour, int minute, RgbColor color) {
    addBitmapToDisplay(BMP_ITS, (LED *) targetDisplay, color, FLICKER);

    // Round down to the nearest five minutes and determine if it is 'past' or 'to' the hour
    int roundedMinute = (minute / 5) * 5;
    if (roundedMinute > 0) {
        if (roundedMinute < 35) {
            addBitmapToDisplay(BMP_PAST, (LED *) targetDisplay, color, FLICKER);
        } else {
            roundedMinute = 60 - roundedMinute;
            hour++;
            addBitmapToDisplay(BMP_TILL, (LED *) targetDisplay, color, FLICKER);
        }
    }

    // Normalize the hour to a 12-hour format and display AM/PM where applicable
    hour %= 24; // Normalize hour to 0-23
    if(hour == 0 || hour == 12) {
        // It's exactly midnight or noon, so we will handle it in the hour display section.
    } else if (hour < 12) {
        addBitmapToDisplay(BMP_AM, (LED *) targetDisplay, color, FLICKER);
    } else {
        addBitmapToDisplay(BMP_PM, (LED *) targetDisplay, color, FLICKER);
    }

    // Display the hour, normalizing hour again for 12-hour format with special cases for noon and midnight
    if (hour > 12) {
        hour -= 12; // Convert to 12-hour format
    }
    if (hour == 0) {
        hour = 12; // Adjust for midnight/noon display
    }

    // Use an array to simplify hour display logic
    if(hour >= 1 && hour <= 12) {
        addBitmapToDisplay(hourBitmaps[hour % 12], (LED *) targetDisplay, color, FLICKER);
    }

    // Display the minute in intervals of five using an array pointing to the bitmaps
    if (roundedMinute > 0) {
        addBitmapToDisplay(minuteBitmaps[(roundedMinute / 5) - 1], (LED *) targetDisplay, color, FLICKER);
    }
}

void display_anniversary(void) {
	RgbColor color;
	color.r = 5;
	color.b = 5;
	color.g = 5;
	addBitmapToDisplay(BMP_HAPPY, (LED *) currentDisplay, color, RAINBOW);
	addBitmapToDisplay(BMP_ANNIVERSARY, (LED *) currentDisplay, color, RAINBOW);
	addBitmapToDisplay(BMP_KATIEDEREK, (LED *) currentDisplay, color, RAINBOW);
}

void display_birthday(void) {
	RgbColor color;
	color.r = 5;
	color.b = 5;
	color.g = 5;
	addBitmapToDisplay(BMP_HAPPY, (LED *) currentDisplay, color, RAINBOW);
	addBitmapToDisplay(BMP_BIRTHDAY, (LED *) currentDisplay, color, RAINBOW);
	addBitmapToDisplay(BMP_DEREK, (LED *) currentDisplay, color, RAINBOW);
}
