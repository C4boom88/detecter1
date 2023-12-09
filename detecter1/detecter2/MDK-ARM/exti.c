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
    
    __HAL_RCC_GPIOC_CLK_ENABLE();               //开启GPIOC时钟
    
    
    GPIO_Initure.Pin=GPIO_PIN_9 ;	//PC9
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //下降沿触发GPIO_MODE_IT_FALLING
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);
	
	
    
    //中断线8,9
    HAL_NVIC_SetPriority(EXTI9_5_IRQn,2,0);       //抢占优先级为2，子优先级为0
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);             //使能中断线0

}

void EXTI9_5_IRQHandler(void)
{
    /* 清除中断标志位 */
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