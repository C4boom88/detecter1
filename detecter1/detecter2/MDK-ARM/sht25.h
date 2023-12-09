#ifndef __sht25_H__
#define __sht25_H__
#include "main.h"



typedef enum {false, true} bool;
///传感器共用的数据结构体
typedef struct
{
    float temperature;
    float humidity;
} SensorStruct;

extern SensorStruct  SensorData;
extern void gettempandhum(void *pvParameters);
//float get_humidity(*humidity);
//float get_temperature(*temperature);
	
#endif 

