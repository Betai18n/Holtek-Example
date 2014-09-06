#include "delay.h"

//�޸�˵��
//�������ж��е��ó�����ѭ���Ĵ���
//��ֹ��ʱ��׼ȷ,����do while�ṹ
//////////////////////////////////////////////////////////////////////////////////	 
static u8  fac_us=0;//us��ʱ������
static u16 fac_ms=0;//ms��ʱ������
//��ʼ���ӳٺ���
//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
//SYSCLK:ϵͳʱ��
void delay_init(u8 SYSCLK)
{
//	SysTick->CTRL&=0xfffffffb;//bit2���,ѡ���ⲿʱ��  HCLK/8
	SYSTICK_ClockSourceConfig(SYSTICK_SRC_STCLK);	//ѡ���ⲿʱ��  HCLK/8
	fac_us=SYSCLK/8;		    
	fac_ms=(u16)fac_us*1000;
}
								    
//��ʱnms
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��72M������,nms<=1864 
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	//SYSTICK_SetReloadValue((u32)nms*fac_ms);//ʱ�����(SysTick->LOADΪ24bit)
	//SYSTICK_CounterCmd(SYSTICK_COUNTER_CLEAR);           //��ռ�����
	//SYSTICK_CounterCmd(SYSTICK_COUNTER_ENABLE);          //��ʼ����  
	SysTick->LOAD=(u32)nms*fac_ms;//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           //��ռ�����
	SysTick->CTRL=0x01 ;          //��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}while(temp&0x01&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	  	   
	//SYSTICK_CounterCmd(SYSTICK_COUNTER_DISABLE);       //�رռ�����
	//SYSTICK_CounterCmd(SYSTICK_COUNTER_CLEAR);       //��ռ�����	  	    
}   

//��ʱnus
//nusΪҪ��ʱ��us��.		    								   
void delay_us(u32 nus)
{		
	u32 temp;		   
	//SYSTICK_SetReloadValue((u32)nus*fac_us);//ʱ�����(SysTick->LOADΪ24bit)
	//SYSTICK_CounterCmd(SYSTICK_COUNTER_CLEAR);           //��ռ�����
	//SYSTICK_CounterCmd(SYSTICK_COUNTER_ENABLE);          //��ʼ����  
	SysTick->LOAD=nus*fac_us; //ʱ�����	  		 
	SysTick->VAL=0x00;        //��ռ�����
	SysTick->CTRL=0x01 ;      //��ʼ���� 	 
	do
	{
		temp=SysTick->CTRL;
	}while(temp&0x01&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��  
	//SYSTICK_CounterCmd(SYSTICK_COUNTER_DISABLE);       //�رռ�����
	//SYSTICK_CounterCmd(SYSTICK_COUNTER_CLEAR);       //��ռ�����	
	SysTick->CTRL=0x00;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	   
}

































