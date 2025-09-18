/*
 * rainbow.h
 *
 *  Created on: Apr 2, 2024
 *      Author: dsava
 */

#ifndef SRC_RAINBOW_H_
#define SRC_RAINBOW_H_

#include "color.h"
#include <stdint.h>
#include "display.h"
#include "matrix.h"
#include "WS2812B.h"
#include "settings.h"
#include <math.h>

void rainbow(RTC_TimeTypeDef currentTime);
RgbColor getRainbowColor();

#endif /* SRC_RAINBOW_H_ */
