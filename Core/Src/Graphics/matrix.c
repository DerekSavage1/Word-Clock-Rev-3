/*
 * matrix.c
 *
 *  Created on: Jan 22, 2024
 *      Author: dsava
 */
#include "matrix.h"
const uint16_t bitmap[][MATRIX_HEIGHT] = {
    //  1    2     3     4     5    6     7     8     9     10   11    12   13
    {   0,   0,    0,    0,    0,   0,    0,    0,    0,    7,   0,    0,   0}, // HOUR_ONE
    {   0,   0,    0,    0,    0,   0,    0,    0,    1792, 0,   0,    0,   0}, // HOUR_TWO
    {   0,   0,    0,    0,    0,   0,    0,    0,    0,    0,   496,  0,   0}, // HOUR_THREE
    {   0,   0,    0,    0,    0,   0,    0,    0,    15,   0,   0,    0,   0}, // HOUR_FOUR
    {   0,   0,    0,    0,    0,   0,    0,    0,    0,    0,   15,   0,   0}, // HOUR_FIVE
    {   0,   0,    0,    0,    0,   0,    1792, 0,    0,    0,   0,    0,   0}, // HOUR_SIX
    {   0,   0,    0,    0,    0,   0,    0,    248,  0,    0,   0,    0,   0}, // HOUR_SEVEN
    {   0,   0,    0,    0,    0,   0,    0,    0,    496,  0,   0,    0,   0}, // HOUR_EIGHT
    {   0,   0,    0,    0,    0,   0,    0,    0,    0,    1920,0,    0,   0}, // HOUR_NINE
    {   0,   0,    0,    0,    0,   0,    0,    7,    0,    0,   0,    0,   0}, // HOUR_TEN
    {   0,   0,    0,    0,    0,   0,    0,    0,    0,    252, 0,    0,   0}, // HOUR_ELEVEN
    {   0,   0,    0,    0,    0,   0,    0,    1920, 0,    0,   0,    0,   0}, // HOUR_NOON
    {   0,   0,    0,    0,    0,   0,    0,    0,    0,    0,   0,    2040,0}, // HOUR_MIDNIGHT
    {   0,   0,    0,    0,    1920,0,    0,    0,    0,    0,   0,    0,   0}, // MINUTE_FIVE
    {   0,   0,    0,    7,    0,   0,    0,    0,    0,    0,   0,    0,   0}, // MINUTE_TEN
    {   32,  0,    127,  0,    0,   0,    0,    0,    0,    0,   0,    0,   0}, // MINUTE_FIFTEEN
    {   0,   2016, 0,    0,    0,   0,    0,    0,    0,    0,   0,    0,   0}, // MINUTE_TWENTY
    {   0,   2016, 0,    0,    1920,0,    0,    0,    0,    0,   0,    0,   0}, // MINUTE_TWENTYFIVE
    {   0,   0,    1920, 0,    0,   0,    0,    0,    0,    0,   0,    0,   0}, // MINUTE_THIRTY
    {   15,  0,    0,    0,    0,   0,    0,    0,    0,    0,   0,    0,   0}, // BMP_ITS
    {   0,   0,    0,    0,    0,   0,    15,   0,    0,    0,   0,    0,   0}, // BMP_PAST
    {   0,   0,    0,    0,    0,   0,    120,  0,    0,    0,   0,    0,   0}, // BMP_TILL
    {   1984,0,    0,    0,    0,   0,    0,	0,    0,    0,   0,    0,   0}, // BMP_HAPPY
    {   0,   31,   0,    0,    127, 0,    0,    0,    0,    0,   0,    0,   0}, // BMP_ANNIVERSARY
    {   0,   0,    0,    2040, 0,   0,    0,    0,    0,    0,   0,    0,   0}, // BMP_BIRTHDAY
    {   0,   0,    0,    0,    0,   2047, 0,    0,    0,    0,   0,    0,   0}, // BMP_KATIEDEREK
    {   0,   0,    0,    0,    0,   0,    0,    0,    0,    0,   0,    3,   0}, // BMP_AM
    {   0,   0,    0,    0,    0,   0,    0,    0,    0,    0,   0,    0, 	0}, // BMP_PM
    {   0,   0,    0,    0,    0,   0,    0,    0,    0,    0,   0,    0,   0}, // BMP_DEREK
    {   0,   0,    0,    0,    0,   0,    0,    0,    0,    0,   0,    0,   0}, // BMP_KATIE
    {   0,   0,    0,    0,    0,   0,    0,    0,    0,    0,   0,    0,   1}, // MINUTE_ONE
    {   0,   0,    0,    0,    0,   0,    0,    0,    0,    0,   0,    0,   2}, // MINUTE_TWO
    {   0,   0,    0,    0,    0,   0,    0,    0,    0,    0,   0,    0,   4}, // MINUTE_THREE
    {   0,   0,    0,    0,    0,   0,    0,    0,    0,    0,   0,    0,   8}, // MINUTE_FOUR
    {   0,   0,    0,    0,    0,   0,    0,    0,    0,    0,   0,    0,   16},// MENU_SET
    {   0,   0,    0,    0,    0,   0,    0,    0,    0,    0,   0,    0,   32},// MENU_DEL
	{   0,   0,    0,    0,    0,   0,    0,    0,    0,    0,   0,    0,   512},// MENU_TIME
	{   0,   0,    0,    0,    0,   0,    0,    0,    0,    0,   0,    0,   256},// MENU_COLOR
	{   0,   0,    0,    0,    0,   0,    0,    0,    0,    0,   0,    0,   128},// MENU_BIRTHDAY
	{   0,   0,    0,    0,    0,   0,    0,    0,    0,    0,   0,    0,   64},// MENU_ANNIVERSARY

};

