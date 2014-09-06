#ifndef __DELAY_H
#define __DELAY_H 			   
#include "ht32f175x_275x.h"
#include "ht32f175x_275x_board.h"


//V1.2修改说明
//修正了中断中调用出现死循环的错误
//防止延时不准确,采用do while结构!
////////////////////////////////////////////////////////////////////////////////// 
void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif





























