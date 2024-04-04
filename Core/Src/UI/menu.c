/*
 * menu.c
 *
 *  Created on: Apr 2, 2024
 *      Author: dsava
 */

#include "menu.h"

void configureSettings(void) {

	switch(getDeviceState()) {
		case SLEEP:
			setDisplayString("%d", getCounterWithinBounds(0, 50));
			break;
		case WAKE:
			if(getCounterWithinBounds(0, 1)) {
				setDisplayString("SET");
				setMode(SET_MODE);
			} else {
				setDisplayString("DEL");
				setMode(DELETE_MODE);
			}
			break;
		case SELECT:
			setDisplayString("%d", getCounterWithinBounds(0, 3));
			break;
		case SET_HOURS:
			setDisplayString("%02d%02d", getCounterWithinBounds(0, 23), getTime()->Minutes);
		    getTime()->Hours = (uint8_t) getCounterWithinBounds(0, 23);
			break;
		case SET_MINUTES:
			setDisplayString("%02d%02d", getTime()->Hours, getCounterWithinBounds(0, 59));
		    getTime()->Minutes = (uint8_t) getCounterWithinBounds(0, 59);
			break;
		case SET_MONTH:
			getCounterWithinBounds(0, 12);
			setDisplayString("%02d%02d", getCounterWithinBounds(0, 12), getDate(getDateState())->Date);
		    getDate(getDateState())->Month = (uint8_t) getCounterWithinBounds(0, 12);
			break;
		case SET_DAY:
			setDisplayString("%02d%02d", getDate(getDateState())->Month, getCounterWithinBounds(0, 31));
		    //FIXME: user could enter February 31 which is wrong
		    getDate(getDateState())->Date = (uint8_t) getCounterWithinBounds(0, 31);
			break;
		case SET_YEAR:
			setDisplayString("20%02d", getTime()->Hours, getCounterWithinBounds(0, 99));
		    getDate(getDateState())->Year = (uint8_t) getCounterWithinBounds(0, 99);
			break;
		case SET_COLOR:
			setDisplayString("COLOR");
			setCounter(getCounterWithinBounds(0, 16)); //16 color presets
			break;
		case SET_BRIGHTNESS:
			setDisplayString("BRIGHT");
			setCounter(getCounterWithinBounds(0, 255));
			break;
		default:
			break;
	}

}
