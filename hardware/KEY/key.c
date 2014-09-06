#include "ht32f175x_275x.h"
#include "ht32f175x_275x_board.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
#include "disp.h"
#include "touch.h"
#include "lcd.h"
#include "main.h"
#include "24bitAD.h"

//////////////////////////////////////////////////////////////////////////////////	 


void KEY_Init(void) //IO初始化
{
 	//GPIO_InitTypeDef GPIO_InitStructure;

	//init GPIOE.09,GPIOE.10  上拉输入  按键另一端接地

 	CKCU_APBPerip0ClockConfig(CKCU_APBEN0_PE,ENABLE);
	
	GPIO_DirectionConfig(GPIOE,(GPIO_PIN_9|GPIO_PIN_10),GPIO_DIR_IN);
	GPIO_PullResistorConfig(GPIOE,(GPIO_PIN_9|GPIO_PIN_10),GPIO_PR_DISABLE);
	GPIO_InputConfig(GPIOE,(GPIO_PIN_9|GPIO_PIN_10),ENABLE);

	//init GPIOB.6	  下拉输入   按键另一端接VCC
 	/*CKCU_APBPerip0ClockConfig(CKCU_APBEN0_PB,ENABLE);
	
	GPIO_DirectionConfig(GPIOB,GPIO_PIN_6,GPIO_DIR_IN);
	GPIO_PullResistorConfig(GPIOB,GPIO_PIN_6,GPIO_PR_DISABLE);
	GPIO_InputConfig(GPIOB,GPIO_PIN_6,ENABLE);*/
		 

}

u8 KEY_Scan(void)
{	 
	u8 key_up=1;//按键按松开标志	
 
 	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	if(key_up&&(KEY1==0||KEY2==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY1==0)
		{
	 	 
	     	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
			return 1;
		}
		else if(KEY2==0)
		{
	 
	    	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
			return 2;
		}
		
	}else if(KEY1==1&&KEY2==1)key_up=1; 	    
 
 	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	return 0;// 无按键按下
}

void touchkey(void)
{
							dispconfig[0]=255;
							switch(dispconfig[2])
							{
								case 0 :
								{
									if((tp_dev.x>55)&&(tp_dev.x<220)&&(tp_dev.y>85)&&(tp_dev.y<110))dispconfig[0]=2;
									else if((tp_dev.x>55)&&(tp_dev.x<220)&&(tp_dev.y>125)&&(tp_dev.y<150))dispconfig[0]=3;
									else if((tp_dev.x>55)&&(tp_dev.x<220)&&(tp_dev.y>165)&&(tp_dev.y<190))dispconfig[0]=4;
									//else if((tp_dev.x>55)&&(tp_dev.x<220)&&(tp_dev.y>45)&&(tp_dev.y<70))dispconfig[0]=1;
									else if((tp_dev.x>(lcddev.width-72))&&(tp_dev.y>(lcddev.height-24)))dispconfig[0]=5;
									else if((tp_dev.x<40)&&(tp_dev.y>(lcddev.height-32)))dispconfig[0]=6;
									else if(tp_dev.x>(lcddev.width-24)&&tp_dev.y<16)dispconfig[0]=7;
									//else if((tp_dev.x<40)&&(tp_dev.y>(lcddev.height-32)))dispconfig[0]=0;
									break;
								}
								case 1 :
								{
									if((tp_dev.x>55)&&(tp_dev.x<220)&&(tp_dev.y>85)&&(tp_dev.y<110))dispconfig[0]=2;
									else if((tp_dev.x>55)&&(tp_dev.x<220)&&(tp_dev.y>125)&&(tp_dev.y<150))dispconfig[0]=3;
									else if((tp_dev.x>55)&&(tp_dev.x<220)&&(tp_dev.y>165)&&(tp_dev.y<190))dispconfig[0]=4;
									else if((tp_dev.x>55)&&(tp_dev.x<220)&&(tp_dev.y>45)&&(tp_dev.y<70))dispconfig[0]=1;
									//else if((tp_dev.x>(lcddev.width-48))&&(tp_dev.y>(lcddev.height-24)))dispconfig[0]=5;
									else if((tp_dev.x<40)&&(tp_dev.y>(lcddev.height-32)))dispconfig[0]=0;
									break;
								}
								case 2 :
								{
									if((tp_dev.x>55)&&(tp_dev.x<220)&&(tp_dev.y>85)&&(tp_dev.y<110))dispconfig[0]=2;
									else if((tp_dev.x>55)&&(tp_dev.x<220)&&(tp_dev.y>125)&&(tp_dev.y<150))dispconfig[0]=3;
									else if((tp_dev.x>55)&&(tp_dev.x<220)&&(tp_dev.y>165)&&(tp_dev.y<190))dispconfig[0]=4;
									else if((tp_dev.x>55)&&(tp_dev.x<220)&&(tp_dev.y>45)&&(tp_dev.y<70))dispconfig[0]=1;
									//else if((tp_dev.x>(lcddev.width-48))&&(tp_dev.y>(lcddev.height-24)))dispconfig[0]=5;
									else if((tp_dev.x<40)&&(tp_dev.y>(lcddev.height-32)))dispconfig[0]=0;
									break;
								}
								case 3 :
								{
									if((tp_dev.x>55)&&(tp_dev.x<220)&&(tp_dev.y>125)&&(tp_dev.y<150))dispconfig[0]=1;
									else if((tp_dev.x>55)&&(tp_dev.x<220)&&(tp_dev.y>165)&&(tp_dev.y<190))dispconfig[0]=2;
									else if((tp_dev.x>55)&&(tp_dev.x<220)&&(tp_dev.y>205)&&(tp_dev.y<230))dispconfig[0]=3;
									else if((tp_dev.x>55)&&(tp_dev.x<220)&&(tp_dev.y>245)&&(tp_dev.y<270))dispconfig[0]=5;									
									//else if((tp_dev.x>(lcddev.width-48))&&(tp_dev.y>(lcddev.height-24)))dispconfig[0]=5;
									else if((tp_dev.x<40)&&(tp_dev.y>(lcddev.height-32)))dispconfig[0]=0;
									break;
								}
								case 4 :
								{
									if((tp_dev.x>55)&&(tp_dev.x<130)&&(tp_dev.y>125)&&(tp_dev.y<150))dispconfig[0]=1;
									else if((tp_dev.x>55)&&(tp_dev.x<130)&&(tp_dev.y>165)&&(tp_dev.y<190))dispconfig[0]=2;
									else if((tp_dev.x>55)&&(tp_dev.x<130)&&(tp_dev.y>205)&&(tp_dev.y<230))dispconfig[0]=3;
									else if((tp_dev.x>55)&&(tp_dev.x<130)&&(tp_dev.y>245)&&(tp_dev.y<270))dispconfig[0]=4;									
									else if((tp_dev.x>55)&&(tp_dev.x<130)&&(tp_dev.y>285)&&(tp_dev.y<310))dispconfig[0]=5;
									else if((tp_dev.x>55)&&(tp_dev.x<130)&&(tp_dev.y>325)&&(tp_dev.y<350))dispconfig[0]=6;
									else if((tp_dev.x>145)&&(tp_dev.x<220)&&(tp_dev.y>125)&&(tp_dev.y<150))dispconfig[0]=7;
									else if((tp_dev.x>145)&&(tp_dev.x<220)&&(tp_dev.y>165)&&(tp_dev.y<190))dispconfig[0]=8;
									else if((tp_dev.x>145)&&(tp_dev.x<220)&&(tp_dev.y>205)&&(tp_dev.y<230))dispconfig[0]=9;
									else if((tp_dev.x>145)&&(tp_dev.x<220)&&(tp_dev.y>245)&&(tp_dev.y<270))dispconfig[0]=10;									
									else if((tp_dev.x>145)&&(tp_dev.x<220)&&(tp_dev.y>285)&&(tp_dev.y<310))dispconfig[0]=11;
									else if((tp_dev.x>145)&&(tp_dev.x<220)&&(tp_dev.y>325)&&(tp_dev.y<350))dispconfig[0]=12;
									else if((tp_dev.x>(lcddev.width-48))&&(tp_dev.y>(lcddev.height-24)))dispconfig[0]=13;
									else if((tp_dev.x<40)&&(tp_dev.y>(lcddev.height-32)))dispconfig[0]=0;
									break;
								}
								case 5 :
								{
									//if((tp_dev.x>55)&&(tp_dev.x<220)&&(tp_dev.y>85)&&(tp_dev.y<110))dispconfig[0]=2;
									//else if((tp_dev.x>55)&&(tp_dev.x<220)&&(tp_dev.y>125)&&(tp_dev.y<150))dispconfig[0]=3;
									//else if((tp_dev.x>55)&&(tp_dev.x<220)&&(tp_dev.y>165)&&(tp_dev.y<190))dispconfig[0]=4;
									//else if((tp_dev.x>55)&&(tp_dev.x<220)&&(tp_dev.y>45)&&(tp_dev.y<70))dispconfig[0]=1;
									//else if((tp_dev.x>(lcddev.width-48))&&(tp_dev.y>(lcddev.height-24)))dispconfig[0]=5;
									if((tp_dev.x<40)&&(tp_dev.y>(lcddev.height-32)))dispconfig[0]=0;
									else if((tp_dev.x>55)&&(tp_dev.x<200)&&(tp_dev.y>225)&&(tp_dev.y<250))dispconfig[0]=1;
									else if((tp_dev.x>55)&&(tp_dev.x<200)&&(tp_dev.y>265)&&(tp_dev.y<290))dispconfig[0]=2;
									else if((tp_dev.x>(lcddev.width-64))&&(tp_dev.y>(lcddev.height-24)))dispconfig[0]=5;
									else if((tp_dev.x>120)&&(tp_dev.x<180)&&(tp_dev.y>(lcddev.height-24)))dispconfig[0]=6;
									break;
								}
								case 6 :
								{
									//if((tp_dev.x>55)&&(tp_dev.x<220)&&(tp_dev.y>85)&&(tp_dev.y<110))dispconfig[0]=2;
									//else if((tp_dev.x>55)&&(tp_dev.x<220)&&(tp_dev.y>125)&&(tp_dev.y<150))dispconfig[0]=3;
									//else if((tp_dev.x>55)&&(tp_dev.x<220)&&(tp_dev.y>165)&&(tp_dev.y<190))dispconfig[0]=4;
									//else if((tp_dev.x>55)&&(tp_dev.x<220)&&(tp_dev.y>45)&&(tp_dev.y<70))dispconfig[0]=1;
									//else if((tp_dev.x>(lcddev.width-48))&&(tp_dev.y>(lcddev.height-24)))dispconfig[0]=5;
									if((tp_dev.x<40)&&(tp_dev.y>(lcddev.height-32)))dispconfig[0]=0;
									else if((tp_dev.x>(lcddev.width-32))&&(tp_dev.y>(lcddev.height-24)))
										{
											if(se==9999)def+=7758;
											else if(se>10)def-=7758;
											else if((se<0))def+=7758;
											else if(se<1)def-=77;
											else if(se<10)def-=775;
											dispconfig[0]=6;
										}
									break;
								}
							}
}
