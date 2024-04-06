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
			removeBitmapFromDisplay(MENU_ANNIVERSARY, currentDisplay);
			removeBitmapFromDisplay(MENU_DELETE, currentDisplay);
			removeBitmapFromDisplay(MENU_SET, currentDisplay);
			removeBitmapFromDisplay(MENU_COLOR, currentDisplay);
			removeBitmapFromDisplay(MENU_BIRTHDAY, currentDisplay);
			removeBitmapFromDisplay(MENU_TIME, currentDisplay);
			setDisplayString("");
			break;
		case WAKE:;


			uint8_t upperBound = 1;

			if(!isBirthdaySet() && !isAnniversarySet())
				upperBound = 0;

			if(!getCounterWithinBounds(0, upperBound)) {
				setDisplayString("SET");
				addBitmapToDisplay(MENU_SET, (LED *) currentDisplay, BLINK);
				removeBitmapFromDisplay(MENU_DELETE, currentDisplay);
				setMode(SET_MODE);
			} else {
				setDisplayString("DEL");
				addBitmapToDisplay(MENU_DELETE, (LED *) currentDisplay, BLINK);
				removeBitmapFromDisplay(MENU_SET, currentDisplay);
				setMode(DELETE_MODE);
			}
			break;
		case SELECT:
			if(getMode() == SET_MODE) {
				switch(getCounterWithinBounds(0, 3)) {
				case 3:
					addBitmapToDisplay(MENU_ANNIVERSARY, (LED *) currentDisplay, BLINK);
					addBitmapToDisplay(MENU_SET, (LED *) currentDisplay, CONSTANT);
					removeBitmapFromDisplay(MENU_DELETE, currentDisplay);
					removeBitmapFromDisplay(MENU_COLOR, currentDisplay);
					removeBitmapFromDisplay(MENU_BIRTHDAY, currentDisplay);
					removeBitmapFromDisplay(MENU_TIME, currentDisplay);
					break;
				case 2:
					addBitmapToDisplay(MENU_BIRTHDAY, (LED *) currentDisplay, BLINK);
					addBitmapToDisplay(MENU_SET, (LED *) currentDisplay, CONSTANT);
					removeBitmapFromDisplay(MENU_DELETE, currentDisplay);
					removeBitmapFromDisplay(MENU_COLOR, currentDisplay);
					removeBitmapFromDisplay(MENU_ANNIVERSARY, currentDisplay);
					removeBitmapFromDisplay(MENU_TIME, currentDisplay);
					break;
				case 1:
					addBitmapToDisplay(MENU_COLOR, (LED *) currentDisplay, BLINK);
					addBitmapToDisplay(MENU_SET, (LED *) currentDisplay, CONSTANT);
					removeBitmapFromDisplay(MENU_DELETE, currentDisplay);
					removeBitmapFromDisplay(MENU_ANNIVERSARY, currentDisplay);
					removeBitmapFromDisplay(MENU_BIRTHDAY, currentDisplay);
					removeBitmapFromDisplay(MENU_TIME, currentDisplay);

					break;
				case 0:
					addBitmapToDisplay(MENU_TIME, (LED *) currentDisplay, BLINK);
					addBitmapToDisplay(MENU_SET, (LED *) currentDisplay, CONSTANT);
					removeBitmapFromDisplay(MENU_DELETE, currentDisplay);
					removeBitmapFromDisplay(MENU_COLOR, currentDisplay);
					removeBitmapFromDisplay(MENU_BIRTHDAY, currentDisplay);
					removeBitmapFromDisplay(MENU_ANNIVERSARY, currentDisplay);
					break;
				default:
					break;
				}
			} else {
				//delete mode
				uint8_t lowerBound = 2 + isAnniversarySet();
				uint8_t upperBound = 2 + !isBirthdaySet();
				switch(getCounterWithinBounds(lowerBound, upperBound)) {
				case 3: //0 anniversary
					addBitmapToDisplay(MENU_ANNIVERSARY, (LED *) currentDisplay, BLINK);
					addBitmapToDisplay(MENU_DELETE, (LED *) currentDisplay, CONSTANT);
					removeBitmapFromDisplay(MENU_SET, currentDisplay);
					removeBitmapFromDisplay(MENU_COLOR, currentDisplay);
					removeBitmapFromDisplay(MENU_BIRTHDAY, currentDisplay);
					removeBitmapFromDisplay(MENU_TIME, currentDisplay);
					break;
				case 2:
					addBitmapToDisplay(MENU_BIRTHDAY, (LED *) currentDisplay, BLINK);
					addBitmapToDisplay(MENU_DELETE, (LED *) currentDisplay, CONSTANT);
					removeBitmapFromDisplay(MENU_SET, currentDisplay);
					removeBitmapFromDisplay(MENU_COLOR, currentDisplay);
					removeBitmapFromDisplay(MENU_ANNIVERSARY, currentDisplay);
					removeBitmapFromDisplay(MENU_TIME, currentDisplay);
					break;
				}
			}
			break;
		case SET_HOURS:
			addBitmapToDisplay(MENU_SET, (LED *) currentDisplay, CONSTANT);
			addBitmapToDisplay(MENU_TIME, (LED *) currentDisplay, CONSTANT);
			setDisplayString("%02d%02d", getCounterWithinBounds(0, 23), getTime()->Minutes);
		    getTime()->Hours = (uint8_t) getCounterWithinBounds(0, 23);
			break;
		case SET_MINUTES:
			addBitmapToDisplay(MENU_SET, (LED *) currentDisplay, CONSTANT);
			addBitmapToDisplay(MENU_TIME, (LED *) currentDisplay, CONSTANT);
			setDisplayString("%02d%02d", getTime()->Hours, getCounterWithinBounds(0, 59));
		    getTime()->Minutes = (uint8_t) getCounterWithinBounds(0, 59);
			break;
		case SET_MONTH:
			addBitmapToDisplay(MENU_SET, (LED *) currentDisplay, CONSTANT);
			addBitmapToDisplay(MENU_TIME, (LED *) currentDisplay, CONSTANT);
			getCounterWithinBounds(0, 12);
			setDisplayString("%02d%02d", getCounterWithinBounds(1, 12), getDate(getDateState())->Date);
		    getDate(getDateState())->Month = (uint8_t) getCounterWithinBounds(0, 12);
			break;
		case SET_DAY:;
		    uint8_t maxDay;
		    uint8_t selectedMonth = getDate(getDateState())->Month;

		    if(selectedMonth == 2) {
		    	maxDay = 29;
		    } else if(selectedMonth == 4 || selectedMonth == 6 || selectedMonth == 9 || selectedMonth == 11) {
		        maxDay = 30;
		    } else {
		        maxDay = 31;
		    }

			setDisplayString("%02d%02d", getDate(getDateState())->Month, getCounterWithinBounds(1, maxDay));
			break;
		case SET_YEAR:
			setDisplayString("20%02d", getCounterWithinBounds(0, 99));
		    getDate(getDateState())->Year = (uint8_t) getCounterWithinBounds(0, 99);
			break;
		case SET_COLOR:
			addBitmapToDisplay(MENU_SET, (LED *) currentDisplay, CONSTANT);
			addBitmapToDisplay(MENU_COLOR, (LED *) currentDisplay, CONSTANT);
			setDisplayString("%02d", getCounterWithinBounds(0, 100));
			setColorWithPreset(getCounterWithinBounds(0, 100));
			updateDisplayColor();
			break;
		case SET_BRIGHTNESS:
			addBitmapToDisplay(MENU_SET, (LED *) currentDisplay, CONSTANT);
			addBitmapToDisplay(MENU_COLOR, (LED *) currentDisplay, CONSTANT);
			setDisplayString("%02d", getCounterWithinBounds(1, 100));
			setBrightnessAsPercent(getCounterWithinBounds(1, 100));
			updateDisplayColor();
			break;
		default:
			break;
	}


}
