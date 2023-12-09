#include "sht25.h"
#include "i2c.h"


///温度湿度传感器使用型号： SHT25
#define	SHT25_IIC_PORT         hi2c1   ///SHT25对应使用的IIC端口

#define	SHT25_ADDRESS_READ          0x81 ///读
#define	SHT25_ADDRESS_WRITE         0x80  ///写
#define	SHT25_READ_TEMPERATURE_CMD  0xF3   ///no hold master
#define	SHT25_READ_HUMIDITY_CMD     0xF5   ///no hold master
#define	SHT25_SOFTRESET_CMD         0xFE   
  
 
SensorStruct  SensorData;   

//bool Is_Sht25_Readdata_Ok(unsigned char * d)
//{
//    unsigned char crc;
// //   crc = HAL_I2C_Master_Transmit( &SHT25_IIC_PORT, 0x81, , 1, HAL_MAX_DELAY );
//    
//    if(crc == *(d+2))
//    {
//        return true;
//    }
//    return false;
//}


bool Sht25_Write(uint8_t addr,uint8_t cmd)
{

    HAL_StatusTypeDef ret;

    ret = HAL_I2C_Master_Transmit( &SHT25_IIC_PORT, addr, &cmd, 1, HAL_MAX_DELAY );

    if ( ret != HAL_OK )
    {
       //DBG_PRINTF( "Error Tx SHT20\r\n" );
        return false;
    }
    return true;
}


bool Sht25_Read(uint8_t * d)
{ 
    HAL_StatusTypeDef ret;																			// return status of i2c

    ret = HAL_I2C_Master_Receive( &SHT25_IIC_PORT, SHT25_ADDRESS_READ, d, 3, HAL_MAX_DELAY );
    if ( ret != HAL_OK )
    {
       // DBG_PRINTF( "Error Rx SHT20\r\n" );
        return false;
    }
    
    return true;
}


float Calc_Temperature_Sth25(uint16_t rawdata)
{
    float temperature;
    
    rawdata &= 0xFFFC;
    
    temperature = rawdata*175.72/65536;///参考手册数值意义
    temperature -= 46.85;
    
    return temperature;
}

float Calc_Humidity_Sth25(uint16_t rawdata)
{
    float humidity;
    
    rawdata &= 0xFFFC;
    
    humidity = rawdata*125/65536;  ///参考手册数值意义
    humidity -= 6;
    
    return humidity;
}

 void  gettempandhum(void *pvParameters)
{
    uint16_t rawdata;
    uint8_t sht25_buffer[4];
    uint8_t string_temp[30];
    //float date[2];
    HAL_Delay(500);    
    Sht25_Write(SHT25_ADDRESS_WRITE, SHT25_SOFTRESET_CMD);  
    
    while(1)
    {
        HAL_Delay(500);
        if(Sht25_Write(SHT25_ADDRESS_WRITE, SHT25_READ_TEMPERATURE_CMD))
        {
            HAL_Delay(100);
            Sht25_Read(sht25_buffer);
            
            rawdata = sht25_buffer[0]*256+sht25_buffer[1];
            rawdata &= 0xFFFC;
            SensorData.temperature = Calc_Temperature_Sth25(rawdata);
        }
                                                         
        HAL_Delay(500);
        
        if(Sht25_Write(SHT25_ADDRESS_WRITE, SHT25_READ_HUMIDITY_CMD))
        {
            HAL_Delay(100);
            Sht25_Read(sht25_buffer);
            
            rawdata = sht25_buffer[0]*256+sht25_buffer[1];
            rawdata &= 0xFFFC;
            SensorData.humidity = Calc_Humidity_Sth25(rawdata);
					
        }
//date[0]=SensorData.temperature;
//date[1]=SensorData.humidity;				
 //       sprintf ( (char*)string_temp, "temper:%.1f C,humidity:%.1f %\r\n", 		
 //       SensorData.temperature,SensorData.humidity); //   最终温度与湿度的使用
      //  DBG_PRINTF( string_temp );
    }

}

//}
//float get_humidity(*humidity)
//{
//uint16_t rawdata;
//    uint8_t sht25_buffer[4];
//    uint8_t string_temp[30];
//    
//    HAL_Delay(500);    
//    Sht25_Write(SHT25_ADDRESS_WRITE, SHT25_SOFTRESET_CMD); 
//	HAL_Delay(500);
//        
//        if(Sht25_Write(SHT25_ADDRESS_WRITE, SHT25_READ_HUMIDITY_CMD))
//        {
//            HAL_Delay(100);
//            Sht25_Read(sht25_buffer);
//            
//            rawdata = sht25_buffer[0]*256+sht25_buffer[1];
//            rawdata &= 0xFFFC;
//            SensorData.humidity = Calc_Humidity_Sth25(rawdata);
//			return 		SensorData.humidity;
//        }
//}

//float get_temperature(*temperature)
//{
//uint16_t rawdata;
//    uint8_t sht25_buffer[4];
//    uint8_t string_temp[30];
//    
//    HAL_Delay(500);
//        if(Sht25_Write(SHT25_ADDRESS_WRITE, SHT25_READ_TEMPERATURE_CMD))
//        {
//            HAL_Delay(100);
//            Sht25_Read(sht25_buffer);
//            
//            rawdata = sht25_buffer[0]*256+sht25_buffer[1];
//            rawdata &= 0xFFFC;
//            SensorData.temperature = Calc_Temperature_Sth25(rawdata);
//			return  SensorData.temperature;
//        }
//}
	