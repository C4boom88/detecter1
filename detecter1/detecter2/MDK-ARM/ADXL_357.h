#ifndef __ADXL__H
#define __ADXL__H
#include "stm32l4xx.h"// Device header
#include "main.h"

extern int32_t AccX;
extern int32_t AccY;
extern int32_t AccZ;
void ADXL357_WritReg(uint8_t RegAddress, uint8_t Data);
uint8_t ADXL357_ReadReg(uint8_t RegAddress);
void ADXL357_Init(void);
uint8_t ADXL_SelfTest(void);
void ADXL357_GetData(int32_t *AccX, int32_t *AccY, int32_t *AccZ);
#endif