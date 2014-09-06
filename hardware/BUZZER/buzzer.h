#ifndef __BUZZER_H
#define __BUZZER_H	 
#include "ht32f175x_275x.h"
#include "ht32f175x_275x_board.h"
#include "sys.h"

//LED驱动代码			 


//LED端口定义
#define buzzer PAout(14)// PA15


void buzzerinit(void);//初始化
void buzzeron(void);
		 				    
#endif
