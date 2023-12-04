#ifndef __OLED_H
#define __OLED_H 

#include "stm32l4xx_hal.h"	
#include "main.h"

//���ú�������������ʾ 0   ������ʾ
//                     90  ��ת90����ʾ
//                     180 ��ת90����ʾ
//                     270 ��ת270����ʾ

#define USE_HORIZONTAL 0

#if USE_HORIZONTAL==0||USE_HORIZONTAL==180 //������ʾ
#define oled_x  64
#define oled_y  16
#else                                      //������ʾ
#define oled_x  128
#define oled_y  8
#endif


//-----------------����LED�˿ڶ���---------------- 

#define LED_ON HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12, GPIO_PIN_RESET)
#define LED_OFF HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12, GPIO_PIN_SET)

//-----------------OLED�˿ڶ���---------------- 

#define OLED_SCL_Clr() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8, GPIO_PIN_RESET)//SCL
#define OLED_SCL_Set() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8, GPIO_PIN_SET)

#define OLED_SDA_Clr() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9, GPIO_PIN_RESET)//SDA
#define OLED_SDA_Set() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9, GPIO_PIN_SET)

#define OLED_SDA_READ HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9)

//#define OLED_RES_Clr() HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2, GPIO_PIN_RESET)//RES
//#define OLED_RES_Set() HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2, GPIO_PIN_SET)

//#define OLED_DC_Clr() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_RESET)//DC
//#define OLED_DC_Set() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_SET)
// 
//#define OLED_CS_Clr()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4, GPIO_PIN_RESET)//CS
//#define OLED_CS_Set()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4, GPIO_PIN_SET)


#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long

void OLED_ClearPoint(u8 x,u8 y);
void OLED_ColorTurn(u8 i);
void OLED_WR_Byte(u8 dat,u8 mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode);
void OLED_DrawCircle(u8 x,u8 y,u8 r);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1,u8 mode);
void OLED_ShowChar6x8(u8 x,u8 y,u8 chr,u8 mode);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1,u8 mode);
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1,u8 mode);
void OLED_ScrollDisplay(u8 num,u8 space,u8 mode);
void OLED_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode);
void OLED_Init(void);

#endif
