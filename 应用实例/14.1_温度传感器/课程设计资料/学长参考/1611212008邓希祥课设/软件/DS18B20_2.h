#ifndef _DS18B20_2_H_
#define _DS18B20_2_H_

#include <intrins.h>
#include<reg52.h>

#define uchar unsigned char
#define uint unsigned int

sbit DQ_2=P3^7;              //ds18b20 ¶Ë¿Ú
int ReadTemperature_2(void);

extern bit flag_fu2;

#endif