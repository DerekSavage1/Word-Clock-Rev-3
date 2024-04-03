/*
 * menu.c
 *
 *  Created on: Apr 2, 2024
 *      Author: dsava
 */

#include "menu.h"

uint32_t clampValue(uint32_t value, uint32_t minVal, uint32_t maxVal) {
    if ((0xFFFF - value) < (maxVal - value)) {
  	  return minVal;
    } else {
        // Normal range (does not wrap around)
        if (value < minVal) return minVal;
        if (value > maxVal) return maxVal;
        return value;
    }
}

void configureSettings(void) {

	uint32_t counter = getCounter();

	switch(getDeviceState()) {
		case SLEEP:
			break;
		case WAKE:
			setCounter(clampValue(counter, 0, 1));
			if(getSelected()) {
				setMode(SET_MODE);
			} else {
				setMode(DELETE_MODE);
			}
			break;
		case SELECT:
			setCounter(clampValue(counter, 0, 3));
			break;
		case SET_HOURS:
		    setCounter(clampValue(counter, 0, 23)); //23 hours
		    getTime()->Hours = (uint8_t) (getSelected());
			break;
		case SET_MINUTES:
		    setCounter(clampValue(counter, 0, 59)); //23 hours
		    getTime()->Minutes = (uint8_t) (getSelected());
			break;
		case SET_MONTH:
			//check which month
		    setCounter(clampValue(counter, 0, 12)); //12 months
		    getDate(getDateState())->Month = (uint8_t) (getSelected());
			break;
		case SET_DAY:
		    setCounter(clampValue(counter, 0, 31)); //31 days
		    //FIXME: user could enter February 31 which is wrong
		    getDate(getDateState())->Date = (uint8_t) (getSelected());
			break;
		case SET_YEAR:
		    setCounter(clampValue(counter, 0, 3000)); //12 months
		    getDate(getDateState())->Year = (uint8_t) (getSelected());
			break;
		case SET_COLOR:
			setCounter(clampValue(counter, 0, 16)); //16 color presets
			break;
		case SET_BRIGHTNESS:
			setCounter(clampValue(counter, 1, 255));
			break;
		default:
			break;
	}
}
