#include "led.h"

void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;  //�ṹ��
	
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);    // ����ʱ��ABP2
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init (GPIOB,&GPIO_InitStructure);   //��ʼ����ַ 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
	
	GPIO_Init (GPIOC,&GPIO_InitStructure); 
	
	GPIO_SetBits (GPIOB,GPIO_Pin_0);  //�ر�gpiob�ĵ�
	
	GPIO_SetBits (GPIOC,GPIO_Pin_3); //�ر�gpioc�ĵ�
	
	GPIO_SetBits (GPIOC,GPIO_Pin_4);
}
