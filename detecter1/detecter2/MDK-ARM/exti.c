#include "exti.h"
#include "key.h"
#include "main.h"

uint8_t button_state=0;


void EXTI_Init(void)
{
	/*
		KEY 	- PC9
		
	*/
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOC_CLK_ENABLE();               //����GPIOCʱ��
    
    
    GPIO_Initure.Pin=GPIO_PIN_9 ;	//PC9
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //�½��ش���GPIO_MODE_IT_FALLING
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);
	
	
    
    //�ж���8,9
    HAL_NVIC_SetPriority(EXTI9_5_IRQn,2,0);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ0
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);             //ʹ���ж���0

}

void EXTI9_5_IRQHandler(void)
{
    /* ����жϱ�־λ */
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_9)
    {
        button_state++;
			if (button_state==4)button_state=0;
    }
}