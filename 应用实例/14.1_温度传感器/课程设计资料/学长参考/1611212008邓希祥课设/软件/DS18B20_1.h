#ifndef _DS18B20_1_H_
#define _DS18B20_1_H_

#include <intrins.h>
#include<reg52.h>

#define uchar unsigned char
#define uint unsigned int

sbit DQ_1=P3^6;              //ds18b20 ¶Ë¿Ú
int ReadTemperature_1(void);

extern bit flag_fu1;

#endif