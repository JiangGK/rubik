/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ����ͷ����ov7725��������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� ISO-MINI STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "bsp_ov7725.h"
#include "bsp_ili9341_lcd.h"
#include "color.h"
#include "bsp_TiMbase.h"
//#include "rubik.h"

extern uint32_t time;

extern uint16_t MidColorData[3][3];

extern HSL_type hsl_l[9];

extern uint8_t Ov7725_vsync;
//void displaystep(char* step);
void init(void);
/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void) 	
{

	init();
//		char rubik[6][9] =
//	{
//		{ 1,3,4,3,6,1,2,4,3 },//F 0
//		{ 5,5,2,6,1,4,2,2,3 },//U 1
//		{ 6,3,5,5,5,1,1,3,6 },//D 2
//		{ 6,4,3,4,4,5,4,6,1 },//L 3
//		{ 1,1,5,6,2,2,4,2,5 },//R 4
//		{ 3,2,2,6,3,5,4,1,6 },//B 5
//	};
//	char step[40];
//		Rubik(rubik,step);
	while(1)
	{
		if( Ov7725_vsync == 2 )
		{
			LCD_OpenWindow(0, 0, 320, 240);
			LCD_ILI9341_CMD(0X2C);	
			FIFO_PREPARE;  			/*FIFO׼��*/					
			ImagDisp();					/*�ɼ�����ʾ*/
			Ov7725_vsync = 0;
		}
			Dispaly_H();
		}
//		  displaystep(step);
	}

void init()
{
	/* Һ����ʼ�� */
	LCD_Init();
	

	/* ov7725 gpio ��ʼ�� */
	Ov7725_GPIO_Config();
	
	
	/* ov7725 �Ĵ������ó�ʼ�� */
	while(Ov7725_Init() != SUCCESS);
	
	/* ov7725 ���ź��߳�ʼ�� */
	VSYNC_Init();	
	Ov7725_vsync = 0;
	
	/* TIM2 ��ʱ���� */	
  TIM2_Configuration();
	
	/* ʵս��ʱ�����ж����ȼ� */
	TIM2_NVIC_Configuration();

	/* TIM2 ���¿�ʱ�ӣ���ʼ��ʱ */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
}
//void displaystep(char *step)
//{
//	char i;
//	while(step[i++]!=0)
//	{
//		LCD_DisNum(10+i*10,140,step[i],WHITE);
//	}
//}
/*********************************************END OF FILE**********************/

