#ifndef __LED_H
#define __LED_H	 
#include "ht32f175x_275x.h"
#include "ht32f175x_275x_board.h"
#include "sys.h"

//LED��������			 


//LED�˿ڶ���
#define LED1 PAout(15)// PA15
#define LED2 PBout(0)// PB0	
#define LED3 PBout(1)// PB1	

void LED_Init(void);//��ʼ��

		 				    
#endif
