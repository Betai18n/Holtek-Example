#ifndef __DELAY_H
#define __DELAY_H 			   
#include "ht32f175x_275x.h"
#include "ht32f175x_275x_board.h"


//V1.2�޸�˵��
//�������ж��е��ó�����ѭ���Ĵ���
//��ֹ��ʱ��׼ȷ,����do while�ṹ!
////////////////////////////////////////////////////////////////////////////////// 
void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif





























