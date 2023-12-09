#include "stm32l4xx.h"                  // Device header
#include "ADXL_357REGISTER_map.h"
#include "ADXL_357.h"
#include "i2c.h"

#define ADXL375_write_ADDRESS		0X3A		//ADXL357��I2C�ӻ���ַ 0011 1010
#define ADXL375_read_ADDRESS		0X3B		//ADXL357��I2C�ӻ���ַ 0011 1011


 int32_t AccX;
 int32_t AccY;
 int32_t AccZ;
/**
  * ��    ����ADXL357д�Ĵ���
  * ��    ����RegAddress �Ĵ�����ַ
  * ��    ����Data Ҫд��Ĵ��������ݣ���Χ��0x00~0xFF
  * �� �� ֵ����
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
  * ��    ����ADXL357��ʼ��
  * ��    ������
  * �� �� ֵ����
  */
void ADXL357_Init(void)
{
	MX_I2C2_Init();//Ӳ��iic��ʼ��
	
	
	ADXL357_WritReg(POWER_CTL, 0x00);		//��Դ����Ĵ���1��ȡ��˯��ģʽ��ΪX��������
	ADXL357_WritReg(Range,0x82 );				//���ٶȼ����üĴ�����ѡ��������Ϊ��16g iic��������1000 0010
	ADXL357_WritReg(Sync,0x07);					//ʹ��ʱ��
	ADXL357_WritReg(ACT_EN, 0x07);			//�ʹ�ܼĴ���
	
	
}

/**
* ��    ��:  ��ȡID��
  * ��    ������
  * �� �� ֵ��ID��
  */
uint8_t ADXL_SelfTest(void)//self_test
{
	uint8_t sign=0;
	if(ADXL357_ReadReg(DEVID_AD)==0xAD)		//���ؼĴ�����ֵ 
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
  * ��    ����MPU6050��ȡ����
  * ��    ����AccX AccY AccZ ���ٶȼ�X��Y��Z������ݣ�ʹ�������������ʽ���أ���Χ��-32768~32767
  * ��    ����GyroX GyroY GyroZ ������X��Y��Z������ݣ�ʹ�������������ʽ���أ���Χ��-32768~32767
  * �� �� ֵ����
  */
void ADXL357_GetData(int32_t *AccX, int32_t *AccY, int32_t *AccZ)
{
	uint8_t DataH,DataM,DataL;								//�������ݸ�8λ��8λ��8λ�ı���
	
	DataH = ADXL357_ReadReg(XDATA3);		//��ȡ���ٶȼ�X��ĸ�8λ����
	DataM = ADXL357_ReadReg(XDATA2);		//��ȡ���ٶȼ�X��ĸ�8λ����
	DataL = ADXL357_ReadReg(XDATA1);		//��ȡ���ٶȼ�X��ĵ�8λ����			
	*AccX = (DataH << 16) | (DataM << 8) | DataL; 	//����ƴ�ӣ�ͨ�������������
	 
	DataH = ADXL357_ReadReg(YDATA3);		//��ȡ���ٶȼ�X��ĸ�8λ����
	DataM = ADXL357_ReadReg(YDATA2);		//��ȡ���ٶȼ�X��ĸ�8λ����
	DataL = ADXL357_ReadReg(YDATA1);		//��ȡ���ٶȼ�X��ĵ�8λ����			
	*AccY = (DataH << 16) | (DataM << 8) | DataL; 	//����ƴ�ӣ�ͨ�������������
	
	DataH = ADXL357_ReadReg(ZDATA3);		//��ȡ���ٶȼ�X��ĸ�8λ����
	DataM = ADXL357_ReadReg(ZDATA2);		//��ȡ���ٶȼ�X��ĸ�8λ����
	DataL = ADXL357_ReadReg(ZDATA1);		//��ȡ���ٶȼ�X��ĵ�8λ����			
	*AccZ = (DataH << 16) | (DataM << 8) | DataL; 	//����ƴ�ӣ�ͨ�������������
	
}




