#include "ht32f175x_275x.h"
#include "ht32f175x_275x_board.h"
#include "sys.h"
#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
 

//初始化PA8和PD2为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
 
 //GPIO_InitTypeDef  GPIO_InitStructure;
	
	
 	/*
 CKCU_APBPerip0ClockConfig(CKCU_APBEN0_PA,ENABLE);	 //使能PA端口时钟

 GPIO_DirectionConfig(GPIOA,GPIO_PIN_15,GPIO_DIR_OUT);
 GPIO_OpenDrainConfig(GPIOA,GPIO_PIN_15,DISABLE);//推挽输出
 GPIO_WriteOutBits(GPIOA, GPIO_PIN_15,SET);//PA.15 输出高*/

 CKCU_APBPerip0ClockConfig(CKCU_APBEN0_PB,ENABLE);	 //使能PB端口时钟

 GPIO_DirectionConfig(GPIOB,GPIO_PIN_0,GPIO_DIR_OUT);
 GPIO_OpenDrainConfig(GPIOB,GPIO_PIN_0,DISABLE);//推挽输出
 GPIO_WriteOutBits(GPIOB, GPIO_PIN_0,SET);//PB.0 输出高
	
 //CKCU_APBPerip0ClockConfig(CKCU_APBEN0_PB,ENABLE);   //使能PB端口时钟

 GPIO_DirectionConfig(GPIOB,GPIO_PIN_1,GPIO_DIR_OUT);
 GPIO_OpenDrainConfig(GPIOB,GPIO_PIN_1,DISABLE);//推挽输出
 GPIO_WriteOutBits(GPIOB, GPIO_PIN_1,SET);//PB.1 输出高


}
 
