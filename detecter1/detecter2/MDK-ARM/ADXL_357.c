#include "stm32l4xx.h"                  // Device header
#include "ADXL_357REGISTER_map.h"
#include "ADXL_357.h"
#include "i2c.h"

#define ADXL375_write_ADDRESS		0X3A		//ADXL357的I2C从机地址 0011 1010
#define ADXL375_read_ADDRESS		0X3B		//ADXL357的I2C从机地址 0011 1011


 int32_t AccX;
 int32_t AccY;
 int32_t AccZ;
/**
  * 函    数：ADXL357写寄存器
  * 参    数：RegAddress 寄存器地址
  * 参    数：Data 要写入寄存器的数据，范围：0x00~0xFF
  * 返 回 值：无
  */

void ADXL357_WritReg(uint8_t RegAddress, uint8_t Data)
{
	I2C_WriteByte( &hi2c2, ADXL375_write_ADDRESS, RegAddress, Data);
}


uint8_t ADXL357_ReadReg(uint8_t RegAddress)
{
	uint8_t Data;
	
  Data=I2C_ReadRegister(&hi2c2, ADXL375_read_ADDRESS, RegAddress);
	return Data;
}
/**
  * 函    数：ADXL357初始化
  * 参    数：无
  * 返 回 值：无
  */
void ADXL357_Init(void)
{
	MX_I2C2_Init();//硬件iic初始化
	
	
	ADXL357_WritReg(POWER_CTL, 0x00);		//电源管理寄存器1，取消睡眠模式，为X轴陀螺仪
	ADXL357_WritReg(Range,0x82 );				//加速度计配置寄存器，选择满量程为±16g iic速率配置1000 0010
	ADXL357_WritReg(Sync,0x07);					//使能时钟
	ADXL357_WritReg(ACT_EN, 0x07);			//活动使能寄存器
	
	
}

/**
* 函    数:  获取ID号
  * 参    数：无
  * 返 回 值：ID号
  */
uint8_t ADXL_SelfTest(void)//self_test
{
	uint8_t sign=0;
	if(ADXL357_ReadReg(DEVID_AD)==0xAD)		//返回寄存器的值 
	{
		sign=1;
	}
	else
	{
		sign=0;
	}
	return sign;
}

/**
  * 函    数：MPU6050获取数据
  * 参    数：AccX AccY AccZ 加速度计X、Y、Z轴的数据，使用输出参数的形式返回，范围：-32768~32767
  * 参    数：GyroX GyroY GyroZ 陀螺仪X、Y、Z轴的数据，使用输出参数的形式返回，范围：-32768~32767
  * 返 回 值：无
  */
void ADXL357_GetData(int32_t *AccX, int32_t *AccY, int32_t *AccZ)
{
	uint8_t DataH,DataM,DataL;								//定义数据高8位中8位低8位的变量
	
	DataH = ADXL357_ReadReg(XDATA3);		//读取加速度计X轴的高8位数据
	DataM = ADXL357_ReadReg(XDATA2);		//读取加速度计X轴的高8位数据
	DataL = ADXL357_ReadReg(XDATA1);		//读取加速度计X轴的低8位数据			
	*AccX = (DataH << 16) | (DataM << 8) | DataL; 	//数据拼接，通过输出参数返回
	 
	DataH = ADXL357_ReadReg(YDATA3);		//读取加速度计X轴的高8位数据
	DataM = ADXL357_ReadReg(YDATA2);		//读取加速度计X轴的高8位数据
	DataL = ADXL357_ReadReg(YDATA1);		//读取加速度计X轴的低8位数据			
	*AccY = (DataH << 16) | (DataM << 8) | DataL; 	//数据拼接，通过输出参数返回
	
	DataH = ADXL357_ReadReg(ZDATA3);		//读取加速度计X轴的高8位数据
	DataM = ADXL357_ReadReg(ZDATA2);		//读取加速度计X轴的高8位数据
	DataL = ADXL357_ReadReg(ZDATA1);		//读取加速度计X轴的低8位数据			
	*AccZ = (DataH << 16) | (DataM << 8) | DataL; 	//数据拼接，通过输出参数返回
	
}




