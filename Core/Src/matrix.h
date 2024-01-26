/*
 * matrix.h
 *
 *  Created on: Jan 22, 2024
 *      Author: dsava
 */

#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <stdint.h>

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
#define BMP_NAME            (bitmap[25])
#define BMP_AM              (bitmap[26])
#define BMP_PM              (bitmap[27])

extern const uint16_t bitmap[][12];

#endif /* SRC_MATRIX_H_ */
