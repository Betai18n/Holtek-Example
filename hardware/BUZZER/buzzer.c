#include "ht32f175x_275x.h"
#include "ht32f175x_275x_board.h"
#include "buzzer.h"

void buzzerinit(void)
{
	 CKCU_APBPerip0ClockConfig(CKCU_APBEN0_PA,ENABLE);	 //使能PB端口时钟

	 GPIO_DirectionConfig(GPIOA,GPIO_PIN_14,GPIO_DIR_OUT);
	 GPIO_OpenDrainConfig(GPIOA,GPIO_PIN_14,DISABLE);//推挽输出
	 GPIO_WriteOutBits(GPIOA, GPIO_PIN_14,SET);//PB.0 输出高
	
}

void buzzeron(void)
{
	buzzer=!buzzer;
}
