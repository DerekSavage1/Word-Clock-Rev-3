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
            break;
        case WAKE:
            setDeviceState(SELECT);
            break;
        case SELECT:
        	switch(getCounterWithinBounds(0, 3)){
        	case 0:
        		setCounter(getTime()->Hours);
        		setDeviceState(SET_HOURS);
        		break;
        	case 1:
        		setDeviceState(SET_COLOR);
        		setCounter(16); //16 presets
        		break;
        	case 2:
        		setDateState(ANNIVERSARY_DATE);
            	setCounter(getDate(ANNIVERSARY_DATE)->Month);
            	setDeviceState(SET_MONTH);
        		break;
        	case 3:
        		setDateState(BIRTHDAY_DATE);
            	setCounter(getDate(BIRTHDAY_DATE)->Month);
            	setDeviceState(SET_MONTH);
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
        case SET_MONTH:
        	setCounter(getDate(getDateState())->Date);
        	setDeviceState(SET_DAY);
        	break;
        case SET_DAY:
        	setCounter(getDate(getDateState())->Year);
        	setDeviceState(SET_YEAR);
        	break;
        case SET_YEAR:
        	setDeviceState(SLEEP);
        	break;
        case SET_COLOR:
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



