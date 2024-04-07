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

void display_time(uint8_t hour, uint8_t minute) {

	wipeDisplay((LED *) targetDisplay);
    addBitmapToDisplay(BMP_ITS, (LED *) targetDisplay, FLICKER);

    switch(minute % 5) {
    case 1:
    	addBitmapToDisplay(MINUTE_ONE, (LED *) targetDisplay, FLICKER);
    	break;
    case 2:
    	addBitmapToDisplay(MINUTE_ONE, (LED *) targetDisplay, FLICKER);
    	addBitmapToDisplay(MINUTE_TWO, (LED *) targetDisplay, FLICKER);
    	break;
    case 3:
    	addBitmapToDisplay(MINUTE_ONE, (LED *) targetDisplay, FLICKER);
    	addBitmapToDisplay(MINUTE_TWO, (LED *) targetDisplay, FLICKER);
    	addBitmapToDisplay(MINUTE_THREE, (LED *) targetDisplay, FLICKER);
    	break;
    case 4:
    	addBitmapToDisplay(MINUTE_ONE, (LED *) targetDisplay, FLICKER);
    	addBitmapToDisplay(MINUTE_TWO, (LED *) targetDisplay, FLICKER);
    	addBitmapToDisplay(MINUTE_THREE, (LED *) targetDisplay, FLICKER);
    	addBitmapToDisplay(MINUTE_FOUR, (LED *) targetDisplay, FLICKER);
    	break;
    }
    int roundedMinute = (minute / 5) * 5;
    if (roundedMinute > 0) {
        if (roundedMinute < 35) {
            addBitmapToDisplay(BMP_PAST, (LED *) targetDisplay, FLICKER);
        } else {
            roundedMinute = 60 - roundedMinute;
            hour++;
            addBitmapToDisplay(BMP_TILL, (LED *) targetDisplay, FLICKER);
        }
    }

    hour %= 24; // Normalize hour to 0-23
    if(hour == 0) {
        addBitmapToDisplay(HOUR_MIDNIGHT, (LED *) targetDisplay, FLICKER);
    } else if (hour == 12) {
        addBitmapToDisplay(HOUR_NOON, (LED *) targetDisplay, FLICKER);
    } else if (hour < 12) {
        addBitmapToDisplay(BMP_AM, (LED *) targetDisplay, FLICKER);
    } else {
        addBitmapToDisplay(BMP_PM, (LED *) targetDisplay, FLICKER);
    }

    if (hour > 12) {
        hour -= 12; // Convert to 12-hour format
    }

    if(hour >= 1 && hour < 12) {
        addBitmapToDisplay(hourBitmaps[hour % 12], (LED *) targetDisplay, FLICKER);
    }

    if (roundedMinute > 0) {
        addBitmapToDisplay(minuteBitmaps[(roundedMinute / 5) - 1], (LED *) targetDisplay, FLICKER);
    }

    display_date();
}

void display_date() {
    if(getDate(SYSTEM_DATE)->Month == getDate(BIRTHDAY_DATE)->Month
    		&& getDate(SYSTEM_DATE)->Date == getDate(BIRTHDAY_DATE)->Date) {
    	addBitmapToDisplay(BMP_HAPPY, (LED *) currentDisplay, RAINBOW);
    	addBitmapToDisplay(BMP_BIRTHDAY, (LED *) currentDisplay, RAINBOW);
    	addBitmapToDisplay(BMP_KATIE, (LED *) currentDisplay, RAINBOW);
    }

    if(getDate(SYSTEM_DATE)->Month == getDate(ANNIVERSARY_DATE)->Month
    		&& getDate(SYSTEM_DATE)->Date == getDate(ANNIVERSARY_DATE)->Date) {
    	addBitmapToDisplay(BMP_HAPPY, (LED *) currentDisplay, RAINBOW);
    	addBitmapToDisplay(BMP_ANNIVERSARY, (LED *) currentDisplay, RAINBOW);
    	addBitmapToDisplay(BMP_KATIEDEREK, (LED *) currentDisplay, RAINBOW);
    }
}

void display_anniversary(void) {
	RgbColor color;
	color.r = 5;
	color.b = 5;
	color.g = 5;
	addBitmapToDisplay(BMP_HAPPY, (LED *) currentDisplay, RAINBOW);
	addBitmapToDisplay(BMP_ANNIVERSARY, (LED *) currentDisplay, RAINBOW);
	addBitmapToDisplay(BMP_KATIEDEREK, (LED *) currentDisplay, RAINBOW);
}

void display_birthday(void) {
	RgbColor color;
	color.r = 5;
	color.b = 5;
	color.g = 5;
	addBitmapToDisplay(BMP_HAPPY, (LED *) currentDisplay, RAINBOW);
	addBitmapToDisplay(BMP_BIRTHDAY, (LED *) currentDisplay, RAINBOW);
	addBitmapToDisplay(BMP_DEREK, (LED *) currentDisplay, RAINBOW);
}
