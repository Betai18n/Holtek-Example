#ifndef __BUZZER_H
#define __BUZZER_H	 
#include "ht32f175x_275x.h"
#include "ht32f175x_275x_board.h"
#include "sys.h"

//LED��������			 


//LED�˿ڶ���
#define buzzer PAout(14)// PA15


void buzzerinit(void);//��ʼ��
void buzzeron(void);
		 				    
#endif
