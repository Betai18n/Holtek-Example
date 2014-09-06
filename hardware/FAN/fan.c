#include "ht32f175x_275x.h"
#include "ht32f175x_275x_board.h"
#include "fan.h"
#include "sys.h"

void faninit(void)
{
		 CKCU_APBPerip0ClockConfig(CKCU_APBEN0_PA,ENABLE);	 //使能PA端口时钟

		 GPIO_DirectionConfig(GPIOA,(GPIO_PIN_0|GPIO_PIN_1),GPIO_DIR_OUT);
		 GPIO_OpenDrainConfig(GPIOA,(GPIO_PIN_0|GPIO_PIN_1),DISABLE);//推挽输出
		 //GPIO_WriteOutBits(GPIOA, GPIO_PIN_15,SET);//PA.15 输出高
			fan1=0;
			fan0=0;
}

void fanon(void)
{
		fan1=1;
		fan0=0;
}

void fanoff(void)
{
		fan1=0;
		fan0=0;
}
