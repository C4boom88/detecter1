#ifndef __MS5803_H__
#define __MS5803_H__
#include "main.h"



#define MS5803_ADDR 0x76

void MS5803_Init(I2C_HandleTypeDef *hi2c1);
uint32_t MS5803_ReadRawPressure(I2C_HandleTypeDef *hi2c1);
float MS5803_GetPressure(I2C_HandleTypeDef *hi2c1);




#endif