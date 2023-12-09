#ifndef __W25Q128_H
#define __W25Q128_H
#include "stm32l4xx.h"                  // Device header

void W25Q128_Init(void);					//��ʼ��W25Q128
uint16_t  W25Q128_ReadID(void);  	    		//��ȡFLASH ID
uint8_t W25Q128_ReadSR(uint8_t regno);             //��ȡ״̬�Ĵ��� 
void W25Q128_4ByteAddr_Enable(void);     //ʹ��4�ֽڵ�ַģʽ
void W25Q128_Write_SR(uint8_t regno,uint8_t sr);   //д״̬�Ĵ���
void W25Q128_Write_Enable(void);  		//дʹ�� 
void W25Q128_Write_Disable(void);		//д����
void W25Q128_Write_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);//дflash,��У��
void W25Q128_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead);   //��ȡflash
void W25Q128_Write(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);//д��flash
void W25Q128_Erase_Chip(void);    	  	//��Ƭ����
void W25Q128_Erase_Sector(uint32_t Dst_Addr);	//��������
void W25Q128_Wait_Busy(void);     
#endif