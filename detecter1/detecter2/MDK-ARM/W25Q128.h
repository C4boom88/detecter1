#ifndef __W25Q128_H
#define __W25Q128_H
#include "stm32l4xx.h"                  // Device header

void W25Q128_Init(void);					//初始化W25Q128
uint16_t  W25Q128_ReadID(void);  	    		//读取FLASH ID
uint8_t W25Q128_ReadSR(uint8_t regno);             //读取状态寄存器 
void W25Q128_4ByteAddr_Enable(void);     //使能4字节地址模式
void W25Q128_Write_SR(uint8_t regno,uint8_t sr);   //写状态寄存器
void W25Q128_Write_Enable(void);  		//写使能 
void W25Q128_Write_Disable(void);		//写保护
void W25Q128_Write_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);//写flash,不校验
void W25Q128_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead);   //读取flash
void W25Q128_Write(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);//写入flash
void W25Q128_Erase_Chip(void);    	  	//整片擦除
void W25Q128_Erase_Sector(uint32_t Dst_Addr);	//扇区擦除
void W25Q128_Wait_Busy(void);     
#endif