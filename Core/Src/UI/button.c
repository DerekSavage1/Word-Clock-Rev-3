/*
 * button.c
 *
 *  Created on: Apr 2, 2024
 *      Author: dsava
 */

#include "button.h"

bool checkButtonPress(void) {
    static GPIO_PinState lastButtonState = GPIO_PIN_SET; // Assume button is initially not pressed (HIGH due to pull-up).
    GPIO_PinState currentButtonState;

    // Read the current state of the button GPIO pin.
    currentButtonState = HAL_GPIO_ReadPin(GPIOB, BUTTON_Pin);

    // Check if button state has transitioned from HIGH to LOW.
    if (lastButtonState == GPIO_PIN_SET && currentButtonState == GPIO_PIN_RESET) {
        // Button was pressed - perform actions here.
        lastButtonState = currentButtonState; // Update the last button state.
        return true;
    } else {
        // Update the last button state.
        lastButtonState = currentButtonState;
        return false;
    }
}

void switchState() {
    switch(getDeviceState()) {
        case SLEEP:
            setDeviceState(WAKE);
        	setCounter(0);
            break;
        case WAKE:
            setDeviceState(SELECT);
        	setCounter(0);
            break;
        case SELECT:
        	switch(3-getCounterWithinBounds(0, 3)){
        	case 3:

				addBitmapToDisplay(MENU_TIME, (LED *) currentDisplay, CONSTANT);
				if(getMode() == SET_MODE) {
					addBitmapToDisplay(MENU_SET, (LED *) currentDisplay, CONSTANT);
					removeBitmapFromDisplay(MENU_DELETE, currentDisplay);
				} else {
					addBitmapToDisplay(MENU_DELETE, (LED *) currentDisplay, CONSTANT);
					removeBitmapFromDisplay(MENU_SET, currentDisplay);
				}

				setCounter(getTime()->Hours);
        		setDeviceState(SET_HOURS);

        		break;
        	case 2:

				addBitmapToDisplay(MENU_COLOR, (LED *) currentDisplay, CONSTANT);
				if(getMode() == SET_MODE) {
					addBitmapToDisplay(MENU_SET, (LED *) currentDisplay, CONSTANT);
					removeBitmapFromDisplay(MENU_DELETE, currentDisplay);
				} else {
					addBitmapToDisplay(MENU_DELETE, (LED *) currentDisplay, CONSTANT);
					removeBitmapFromDisplay(MENU_SET, currentDisplay);
				}
				removeBitmapFromDisplay(MENU_COLOR, currentDisplay);
				removeBitmapFromDisplay(MENU_ANNIVERSARY, currentDisplay);
				removeBitmapFromDisplay(MENU_TIME, currentDisplay);

				setCounter(getColorPreset());
        		setDeviceState(SET_COLOR);

        		break;
        	case 1:


				addBitmapToDisplay(MENU_BIRTHDAY, (LED *) currentDisplay, CONSTANT);
				if(getMode() == SET_MODE) {
					addBitmapToDisplay(MENU_SET, (LED *) currentDisplay, CONSTANT);
					removeBitmapFromDisplay(MENU_DELETE, currentDisplay);
	        		setDateState(BIRTHDAY_DATE);
	            	setCounter(getDate(BIRTHDAY_DATE)->Month);
	            	setDeviceState(SET_MONTH);
				} else {
					deleteBirthday();
					setDeviceState(SLEEP);
					addBitmapToDisplay(MENU_DELETE, (LED *) currentDisplay, CONSTANT);
					removeBitmapFromDisplay(MENU_SET, currentDisplay);
				}
				removeBitmapFromDisplay(MENU_TIME, currentDisplay);
				removeBitmapFromDisplay(MENU_ANNIVERSARY, currentDisplay);


        		break;
        	case 0:


				addBitmapToDisplay(MENU_ANNIVERSARY, (LED *) currentDisplay, CONSTANT);
				if(getMode() == SET_MODE) {
					addBitmapToDisplay(MENU_SET, (LED *) currentDisplay, CONSTANT);
					removeBitmapFromDisplay(MENU_DELETE, currentDisplay);
	        		setDateState(ANNIVERSARY_DATE);
	            	setCounter(getDate(ANNIVERSARY_DATE)->Month);
	            	setDeviceState(SET_MONTH);
				} else {
					deleteAnniversary();
					setDeviceState(SLEEP);
					addBitmapToDisplay(MENU_DELETE, (LED *) currentDisplay, CONSTANT);
					removeBitmapFromDisplay(MENU_SET, currentDisplay);
				}
				removeBitmapFromDisplay(MENU_COLOR, currentDisplay);
				removeBitmapFromDisplay(MENU_BIRTHDAY, currentDisplay);

        		break;
        	default:
        		break;
        	}
            break;
        case SET_HOURS:

        	setCounter(getTime()->Minutes);
            setDeviceState(SET_MINUTES);
            break;
        case SET_MINUTES:
        	setCounter(getDate(SYSTEM_DATE)->Month);
            setDeviceState(SET_MONTH);
            break;
        case SET_MONTH:;
        	RTC_DateTypeDef nDate = *getDate(getDateState());
        	nDate.Month = (uint8_t) getCounter();
        	setDate(nDate, getDateState());
        	setCounter(getDate(getDateState())->Date);

        	setDeviceState(SET_DAY);

        	break;
        case SET_DAY:
        	nDate = *getDate(getDateState());
        	nDate.Date = (uint8_t) getCounter();
        	setDate(nDate, getDateState());
        	if (getDateState() != SYSTEM_DATE) {
        		setDeviceState(SLEEP);
        		return;
        	}
        	setDeviceState(SET_YEAR);
        	break;
        case SET_YEAR:
        	nDate = *getDate(getDateState());
        	nDate.Year = (uint8_t) getCounter();
        	setDate(nDate, getDateState());
        	setDeviceState(SLEEP);
        	break;
        case SET_COLOR:
        	setCounterBounds(0,100);
        	setCounter(getBrightness());
            setDeviceState(SET_BRIGHTNESS); // After color, set brightness
            break;
        case SET_BRIGHTNESS:
            setDeviceState(SLEEP); // Return to SLEEP after setting LED features
            break;
        default:
            // If state is somehow unhandled, default back to SLEEP as a failsafe
            setDeviceState(SLEEP);
            break;
    }
}



