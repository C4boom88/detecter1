/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "quadspi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "sht25.h"
//#include "ms5803.h"
//#include "ADXL_357.h"
//#include "key.h"
//#include "exti.h"
//#include "display.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

extern uint16_t setAccX;
extern uint16_t setAccY;
extern uint16_t setAccZ;
extern int32_t AccX;
extern int32_t AccY;
extern int32_t AccZ;
//uint32_t timerstate=0;
float pressure=0;
typedef struct
{
    float temperature;
    float humidity;
} SensorStruct;

extern SensorStruct  SensorData;
uint16_t adcx;
float temp;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
uint8_t button_state;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_QUADSPI_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  MX_TIM16_Init();
  MX_TIM17_Init();
  MX_USART3_Init();
  /* USER CODE BEGIN 2 */
	KEY_Scan(0);
	MS5803_Init(&hi2c1);
	
	
	
  /* USER CODE END 2 */
	
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	      adcx = Get_Adc_Average(ADC_CHANNEL_3, 20); 	//��ȡͨ��3��ת��ֵ��20��ȡƽ��
        //LCD_ShowxNum(174, 190, adcx, 4, 16, 0);	 	//��ʾADCC�������ԭʼֵ
        temp = (float)adcx * (3.3 / 4096);    		//��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
		//��ʾ�͵�ѹ
if(temp<2.5)	
{	
        adcx = temp;                          		//��ֵ�������ָ�adcx��������ΪadcxΪu16����
				OLED_Clear();//����
        OLED_ShowNum(42, 20, adcx, 1, 16, 0); 	//��ʾ��ѹֵ���������֣�3.1111�Ļ������������ʾ3
        temp -= adcx;                         		//���Ѿ���ʾ����������ȥ��������С�����֣�����3.1111-3=0.1111
        temp *= 1000;                         		//С�����ֳ���1000�����磺0.1111��ת��Ϊ111.1���൱�ڱ�����λС����
        OLED_ShowNum(190, 210, temp, 3, 16, 0X80); 	//��ʾС�����֣�ǰ��ת��Ϊ��������ʾ����������ʾ�ľ���111.
        HAL_Delay(250);
}	
//button_state==0--��ӭ����
//button_state==1--״̬1	
//button_state==2--״̬2	
//button_state==3--״̬3	
			
		if(button_state==0)
		{
			displayzhuangtai0();//�������
			
		}
		if(button_state==1)
		{
		displayzhuangtai1();//ʵʱ��ʾ״̬
			
		}
		if(button_state==2)
		{
		displayzhuangtai2();//Ѳ��״̬
		gettempandhum( &SensorData)	;
			
		W25Q128_Write_Enable();//�洢ʹ��
		W25Q128_Write(&AccX,0x0000,4);//����ʵʱx����ٶ�
		W25Q128_Write(&AccY,0x3000,4);//����ʵʱy����ٶ�
		W25Q128_Write(&AccZ,0x6000,4);//����ʵʱz����ٶ�
		if(timerstate==12)//ÿ��Сʱ	
    {			
			W25Q128_Write(SensorData.temperature,0x9000,4);//����һ����ʪ��ѹ��
			W25Q128_Write(SensorData.humidity,0xB000,4);//����һ����ʪ��ѹ��
			W25Q128_Write(pressure,0xD000,4);//����һ����ʪ��ѹ��
			timerstate=0;
		}
		
		}
		if(button_state==3)
		{
		displayzhuangtai3();//�鿴���ֵ
			
		}
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 25;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
