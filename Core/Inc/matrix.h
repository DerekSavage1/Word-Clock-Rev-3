/*
 * matrix.h
 *
 *  Created on: Jan 22, 2024
 *      Author: dsava
 */

#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define MATRIX_WIDTH 11
#define MATRIX_HEIGHT 13

#define HOUR_ONE            (bitmap[0])
#define HOUR_TWO            (bitmap[1])
#define HOUR_THREE          (bitmap[2])
#define HOUR_FOUR           (bitmap[3])
#define HOUR_FIVE           (bitmap[4])
#define HOUR_SIX            (bitmap[5])
#define HOUR_SEVEN          (bitmap[6])
#define HOUR_EIGHT          (bitmap[7])
#define HOUR_NINE           (bitmap[8])
#define HOUR_TEN            (bitmap[9])
#define HOUR_ELEVEN         (bitmap[10])
#define HOUR_NOON           (bitmap[11])
#define HOUR_MIDNIGHT       (bitmap[12])
#define MINUTE_FIVE         (bitmap[13])
#define MINUTE_TEN          (bitmap[14])
#define MINUTE_FIFTEEN      (bitmap[15])
#define MINUTE_TWENTY       (bitmap[16])
#define MINUTE_TWENTYFIVE   (bitmap[17])
#define MINUTE_THIRTY       (bitmap[18])
#define BMP_ITS             (bitmap[19])
#define BMP_PAST            (bitmap[20])
#define BMP_TILL            (bitmap[21])
#define BMP_HAPPY           (bitmap[22])
#define BMP_ANNIVERSARY     (bitmap[23])
#define BMP_BIRTHDAY        (bitmap[24])
#define BMP_KATIEDEREK      (bitmap[25])
#define BMP_AM              (bitmap[26])
#define BMP_PM              (bitmap[27])
#define BMP_DEREK           (bitmap[28])
#define BMP_KATIE           (bitmap[29])
#define MINUTE_ONE          (bitmap[30])
#define MINUTE_TWO          (bitmap[31])
#define MINUTE_THREE		(bitmap[32])
#define MINUTE_FOUR         (bitmap[33])
#define MENU_SET         	(bitmap[34])
#define MENU_DELETE         (bitmap[35])
#define MENU_TIME         	(bitmap[36])
#define MENU_COLOR         	(bitmap[37])
#define MENU_BIRTHDAY       (bitmap[38])
#define MENU_ANNIVERSARY    (bitmap[39])

extern const uint16_t bitmap[][MATRIX_HEIGHT];

#endif /* SRC_MATRIX_H_ */
