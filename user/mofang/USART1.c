#include"USART1.h"


u8 sh[15]={0};																																//��ŵ�ǰλ�õ�λ����
u8 xh[15]={0};																																//��ŵ�ǰλ�ø�λ����

void USART1_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	

	USART_InitStructure.USART_BaudRate=1000000;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
	USART_Init(USART1,&USART_InitStructure);
	
																																							//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;										//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;													//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;															//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	
   
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);															//���������ж�  �����ǰ�˫��ֻ��txһ���� ����ÿ�η����ݶ��ᴥ�������ж� ���������ָ��ػᱻ���յ�

  USART_Cmd(USART1, ENABLE);                    															//ʹ�ܴ��� 
	
	USART_HalfDuplexCmd(USART1, ENABLE);																				//��˫��ģʽ
	
}

void USART1_IRQHandler(void)                																	//����1�жϷ������
{
	static u8 ch[50]={0};
	static u8 nCount=0;	
	u8 k=0,j=0;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  											//�����ж�
	{
			ch[nCount] =USART_ReceiveData(USART1);	
			nCount++;
			if(nCount>=49)
			{	
				for(nCount=0;nCount<50;nCount++)
				{
						if(ch[nCount]==0xff && ch[nCount+1]==0xff && ch[nCount+3]==0x04 && ch[nCount+8]==0xff && ch[nCount+9]==0xff )	
						{
								if(ch[nCount+5]==0x24)
								{
									
										for(k=0;k<15;k++)
										{
											sh[j]=ch[nCount];																										//�����ݷŵ�sh��
											j++;
											nCount++;
										}
								}
								if(ch[nCount+5]==0x25)
								{
										for(k=0;k<15;k++)
										{
											xh[j]=ch[nCount];																										//�����ݷŵ�sh��
											j++;
											nCount++;
										}	
								}
							}
				}
				nCount=0;
			}	
  } 
}
u8 Receiving(u8 num)																														//��֪��ѭ��᲻���� 
{
	u8 data=0;
	if(num==0)																			//��������ݣ�  0xff 0xff 0x00 0x04 0x00 ����1  ����2  У�� 
	{	
			data=sh[13];//|(u16)(sh[6]<<8);																							//����1�Ͳ���2�ϲ���16λ
	}
	else if(num==1)
	{
			data=xh[13];
	}
	return data;
}

void Send(uint8_t Data)
{
	USART_SendData(USART1,Data);
	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
}


void RECEIVE_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
