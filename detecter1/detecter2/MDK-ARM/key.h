#ifndef _KEY_H
#define _KEY_H

#include "main.h"

#define KEY        HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_9)
#define KEY_PRES  1



uint8_t KEY_Scan(uint8_t mode);
#endif