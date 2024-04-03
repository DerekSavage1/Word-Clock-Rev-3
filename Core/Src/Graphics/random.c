/*
 * random.c
 *
 *  Created on: Apr 2, 2024
 *      Author: dsava
 */

#include "random.h"



/**
 * @brief   Shuffles the elements of an array randomly.
 *
 * Rearranges the elements of the given array in a random order.
 * Each possible permutation is equally likely.
 *
 * @param   array Pointer to the array to be shuffled.
 * @param   size  Number of elements in the array.
 *
 * @note    The array must be non-empty and contain at least two elements for shuffling to occur.
 *          Otherwise, the function does nothing.
 */
void shuffleArray(uint8_t *array, uint32_t size) {
    if (size > 1) {
        for (uint32_t i = 0; i < size - 1; i++) {
            uint32_t j = i + (uint32_t) rand() / (RAND_MAX / (size - i) + 1);
            uint8_t t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}
