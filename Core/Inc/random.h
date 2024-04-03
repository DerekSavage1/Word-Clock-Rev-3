/*
 * random.h
 *
 *  Created on: Apr 2, 2024
 *      Author: dsava
 */

#ifndef INC_RANDOM_H_
#define INC_RANDOM_H_

#include <stdint.h>
#include <stdlib.h>

#define RANDOM_IN_RANGE(min, max) ((min) + rand() % ((max) - (min) + 1))



#endif /* INC_RANDOM_H_ */
