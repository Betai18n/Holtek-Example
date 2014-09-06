#ifndef __KEY_H
#define __KEY_H	 
#include "ht32f175x_275x.h"
#include "ht32f175x_275x_board.h"

//////////////////////////////////////////////////////////////////////////////////	 

//修改说明
//修改按键扫描函数，使整个代码可以支持SWD下载。
//////////////////////////////////////////////////////////////////////////////////	 
typedef enum 
{  
	Button_KEY0 = 0,
	Button_KEY1 = 1,
	Button_WAKEUP = 2
} Button_TypeDef;

typedef struct  
{   GPIO_TypeDef*       BUTTON_PORT ;
    uint16_t            BUTTON_PIN ;
    //GPIOMode_TypeDef    BUTTON_MODE;
}Button_PinModeDef;	

#define KEY1 PEin(10)   //PE10
#define KEY2 PEin(9)	//PE9
//#define KEY0 PBin(6)	//PB6  WK_UP
	 
void KEY_Init(void);//IO初始化
u8 KEY_Scan(void);  //按键扫描函数			
void touchkey(void);
#endif
