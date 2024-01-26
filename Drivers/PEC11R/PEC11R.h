/*
 * PEC11R.h
 *
 *  Created on: Jan 25, 2024
 *      Author: dsava
 */

#ifndef PEC11R_PEC11R_H_
#define PEC11R_PEC11R_H_

#include "main.h"

// Encoder and button state accessors
int32_t Encoder_GetCount(void);
void Encoder_SetCount(uint32_t);
uint8_t Button_GetCount(void);
void Button_SetCount(uint32_t);

// EXTI Callbacks
void Encoder_EXTI_Callback(uint16_t GPIO_Pin);
void Button_EXTI_Callback(uint16_t GPIO_Pin);




#endif /* PEC11R_PEC11R_H_ */
