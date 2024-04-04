/*
 * color.h
 *
 *  Created on: Apr 2, 2024
 *      Author: dsava
 */

#ifndef INC_COLOR_H_
#define INC_COLOR_H_

typedef struct RgbColor
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RgbColor;

typedef struct HsvColor
{
    unsigned char h;
    unsigned char s;
    unsigned char v;
} HsvColor;

RgbColor hsvToRgb(HsvColor hsv);
HsvColor rgbToHsv(RgbColor rgb);


#endif /* INC_COLOR_H_ */
