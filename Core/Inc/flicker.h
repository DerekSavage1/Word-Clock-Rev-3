/*
 * flicker.h
 *
 *  Created on: Apr 2, 2024
 *      Author: dsava
 */

#include <stdint.h>
#include "main.h"
#include "stdbool.h"
#include "color.h"
#include "time_display.h"
#include "display.h"
#include "random.h"

typedef enum FlickerState {
    STATE_IDLE,
    STATE_FLICKER_OUT,
    STATE_FLICKER_IN
}FlickerState;

bool flickerOut(void);
bool flickerIn(void);
void checkUpdateTime(RTC_TimeTypeDef currentTime);
void updateDisplay(RTC_TimeTypeDef currentTime);


