#include "ht32f175x_275x.h"
#include "ht32f175x_275x_board.h"
#include "sys.h"
#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
 

//��ʼ��PA8��PD2Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
 
 //GPIO_InitTypeDef  GPIO_InitStructure;
	
	
 	/*
 CKCU_APBPerip0ClockConfig(CKCU_APBEN0_PA,ENABLE);	 //ʹ��PA�˿�ʱ��

 GPIO_DirectionConfig(GPIOA,GPIO_PIN_15,GPIO_DIR_OUT);
 GPIO_OpenDrainConfig(GPIOA,GPIO_PIN_15,DISABLE);//�������
 GPIO_WriteOutBits(GPIOA, GPIO_PIN_15,SET);//PA.15 �����*/

 CKCU_APBPerip0ClockConfig(CKCU_APBEN0_PB,ENABLE);	 //ʹ��PB�˿�ʱ��

 GPIO_DirectionConfig(GPIOB,GPIO_PIN_0,GPIO_DIR_OUT);
 GPIO_OpenDrainConfig(GPIOB,GPIO_PIN_0,DISABLE);//�������
 GPIO_WriteOutBits(GPIOB, GPIO_PIN_0,SET);//PB.0 �����
	
 //CKCU_APBPerip0ClockConfig(CKCU_APBEN0_PB,ENABLE);   //ʹ��PB�˿�ʱ��

 GPIO_DirectionConfig(GPIOB,GPIO_PIN_1,GPIO_DIR_OUT);
 GPIO_OpenDrainConfig(GPIOB,GPIO_PIN_1,DISABLE);//�������
 GPIO_WriteOutBits(GPIOB, GPIO_PIN_1,SET);//PB.1 �����


}
 
