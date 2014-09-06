#ifndef __SYS_H
#define __SYS_H	
#include "ht32f175x_275x.h"
#include "ht32f175x_275x_board.h"

//位带操作，Cortex-M3权威指南 P86
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+32) //0x4001A000+0x20
#define GPIOB_ODR_Addr    (GPIOB_BASE+32) //0x4001B000+0x20
#define GPIOC_ODR_Addr    (GPIOC_BASE+32) //0x4001C000+0x20
#define GPIOD_ODR_Addr    (GPIOD_BASE+32) //0x4001D000+0x20
#define GPIOE_ODR_Addr    (GPIOE_BASE+32) //0x4001E000+0x20


#define GPIOA_IDR_Addr    (GPIOA_BASE+28) //0x4001A000+0x1C
#define GPIOB_IDR_Addr    (GPIOB_BASE+28) //0x4001B000+0x1C
#define GPIOC_IDR_Addr    (GPIOC_BASE+28) //0x4001C000+0x1C
#define GPIOD_IDR_Addr    (GPIOD_BASE+28) //0x4001D000+0x1C
#define GPIOE_IDR_Addr    (GPIOE_BASE+28) //0x4001E000+0x1C

 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入


void NVIC_Configuration(void);
void CKCU_Configuration(void);
void SysClockConfig_72MHz(void);

#endif
