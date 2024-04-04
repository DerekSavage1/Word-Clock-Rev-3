/*
 * menu.c
 *
 *  Created on: Apr 2, 2024
 *      Author: dsava
 */

#include "menu.h"

void configureSettings(void) {

	uint32_t counter = getCounter();

	switch(getDeviceState()) {
		case SLEEP:
			setCounterBounds(0,50);
			setDisplayString("%d", getCounter());
			break;
		case WAKE:
			setCounterBounds(0,1);
			if(getCounter()) {
				setDisplayString("SET");
				setMode(SET_MODE);
			} else {
				setDisplayString("DEL");
				setMode(DELETE_MODE);
			}
			break;
		case SELECT:
			setDisplayString("SELE");
			counter = clamp(counter, 0, 3);
			break;
		case SET_HOURS:
			setDisplayString("HOUR");
		    setCounter(clamp(counter, 0, 23)); //23 hours
		    getTime()->Hours = (uint8_t) (getSelected());
			break;
		case SET_MINUTES:
			setDisplayString("MINUTES");
		    setCounter(clamp(counter, 0, 59)); //23 hours
		    getTime()->Minutes = (uint8_t) (getSelected());
			break;
		case SET_MONTH:
			//check which month
			setDisplayString("MONTH");
		    setCounter(clamp(counter, 0, 12)); //12 months
		    getDate(getDateState())->Month = (uint8_t) (getSelected());
			break;
		case SET_DAY:
			setDisplayString("DAY");
		    setCounter(clamp(counter, 0, 31)); //31 days
		    //FIXME: user could enter February 31 which is wrong
		    getDate(getDateState())->Date = (uint8_t) (getSelected());
			break;
		case SET_YEAR:
			setDisplayString("YEAR");
		    setCounter(clamp(counter, 0, 3000)); //12 months
		    getDate(getDateState())->Year = (uint8_t) (getSelected());
			break;
		case SET_COLOR:
			setDisplayString("COLOR");
			setCounter(clamp(counter, 0, 16)); //16 color presets
			break;
		case SET_BRIGHTNESS:
			setDisplayString("BRIGHT");
			setCounter(clamp(counter, 1, 255));
			break;
		default:
			break;
	}
}
