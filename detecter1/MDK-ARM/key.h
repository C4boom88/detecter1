#ifndef _KEY_H
#define _KEY_H

#include "main.h"

#define KEY        HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_9)


extern int count;

void KEY_Init(void);

#endif