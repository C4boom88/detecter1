#include "display.h"
#include "oled.h"
#include "sht25.h"
#include "ms5803.h"
#include "ADXL_357.h"
#include "i2c.h"

void displayzhuangtai0(void)
{
//void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1,u8 mode);
//     OLED_ShowChinese(8,0,0,16,1);//��	
OLED_ShowChinese(0,8,0,64,1);//��	
OLED_ShowChinese(8,8,1,64,1);//��
OLED_ShowChinese(16,8,2,64,1);//��
OLED_ShowChinese(24,8,3,64,1);//��
OLED_ShowChinese(32,8,4,64,1);//��
OLED_ShowChinese(40,8,5,64,1);//��
OLED_ShowChinese(48,8,6,64,1);//״
OLED_ShowChinese(56,8,7,64,1);//̬
}

void displayzhuangtai1(void)
{
	OLED_Clear();//����
OLED_ShowChinese(0,8,8,64,1);//ʵ	
OLED_ShowChinese(8,8,9,64,1);//ʱ
OLED_ShowChinese(16,8,10,64,1);//��
OLED_ShowChinese(24,8,11,64,1);//��
OLED_ShowChinese(0,16,12,64,1);//��	
OLED_ShowChinese(8,16,13,64,1);//��
OLED_ShowChinese(0,24,14,64,1);//ʪ
OLED_ShowChinese(8,24,15,64,1);//��
OLED_ShowChinese(0,32,16,64,1);//ѹ	
OLED_ShowChinese(8,32,17,64,1);//��
	
gettempandhum( &SensorData)	;
float pressure =	MS5803_GetPressure( &hi2c1);
OLED_ShowNum(18,16,(u16)SensorData.temperature,8,16,1);//��ʾ�¶�
OLED_ShowNum(18,24,(u16)SensorData.humidity,8,16,1);	  //��ʾʪ��
OLED_ShowNum(18,32,(u16)pressure,8,16,1);							//��ʾѹ��
	
}


void displayzhuangtai2(void)
{
OLED_Clear();//����
OLED_ShowChinese(0,8,18,64,1);//Ѳ	
OLED_ShowChinese(8,8,19,64,1);//��
OLED_ShowChinese(16,8,20,64,1);//״
OLED_ShowChinese(24,8,21,64,1);//̬
	
OLED_ShowChinese(16,8,22,64,1);//��
OLED_ShowChinese(24,8,23,64,1);//ʱ
OLED_ShowChinese(32,8,24,64,1);//��
OLED_ShowChinese(40,8,25,64,1);//ֵ
	
OLED_ShowChinese(0,16,12,64,1);//��	
OLED_ShowChinese(8,16,13,64,1);//��
OLED_ShowChinese(0,24,14,64,1);//ʪ
OLED_ShowChinese(8,24,15,64,1);//��
OLED_ShowChinese(0,32,16,64,1);//ѹ	
OLED_ShowChinese(8,32,17,64,1);//��

gettempandhum( &SensorData)	;
float pressure =	MS5803_GetPressure(&hi2c1);
OLED_ShowNum(18,16,SensorData.temperature,8,16,1);//��ʾ�¶�
OLED_ShowNum(18,24,SensorData.humidity,8,16,1);	  //��ʾʪ��
OLED_ShowNum(18,32,pressure,8,16,1);							//��ʾѹ��
}

void displayzhuangtai3(void)
{
	

uint16_t setAccX=0;
uint16_t setAccY=0;	
uint16_t setAccZ=9;		
OLED_Clear();//����
OLED_ShowChinese(0,8,26,64,1);//��	
OLED_ShowChinese(8,8,27,64,1);//��
OLED_ShowChinese(16,8,28,64,1);//��
OLED_ShowChinese(24,8,29,64,1);//��
OLED_ShowChinese(16,8,25,64,1);//ֵ
	
	
ADXL357_GetData(&AccX, &AccY, &AccZ);	
OLED_ShowChinese(0,16,28,64,1);//��
OLED_ShowChinese(8,16,29,64,1);//��
OLED_ShowChinese(16,16,25,64,1);//ֵ
OLED_ShowNum(36,16,AccX,8,16,1);//��ʾx��
OLED_ShowNum(46,16,AccY,8,16,1);//��ʾy��	
OLED_ShowNum(56,16,AccY,8,16,1);//��ʾy��	
	
OLED_ShowChinese(0,24,28,64,1);//��
OLED_ShowChinese(8,24,29,64,1);//��
OLED_ShowChinese(16,24,30,64,1);//��
OLED_ShowChinese(24,24,25,64,1);//ֵ	
OLED_ShowNum(34,24,setAccX,8,16,1);//��ʾx����ֵ
OLED_ShowNum(44,24,setAccY,8,16,1);//��ʾy��	��ֵ
OLED_ShowNum(54,24,setAccY,8,16,1);//��ʾy��	��ֵ
}

