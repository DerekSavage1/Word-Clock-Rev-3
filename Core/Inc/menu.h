/*
 * menu.h
 *
 *  Created on: Apr 2, 2024
 *      Author: dsava
 */

#ifndef INC_MENU_H_
#define INC_MENU_H_

#include <stdint.h>
#include "settings.h"

uint32_t clampValue(uint32_t value, uint32_t minVal, uint32_t maxVal);
void configureSettings(void);


#endif /* INC_MENU_H_ */
