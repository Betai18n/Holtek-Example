#ifndef __KEY_H
#define __KEY_H	 
#include "ht32f175x_275x.h"
#include "ht32f175x_275x_board.h"

//////////////////////////////////////////////////////////////////////////////////	 

//�޸�˵��
//�޸İ���ɨ�躯����ʹ�����������֧��SWD���ء�
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
	 
void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(void);  //����ɨ�躯��			
void touchkey(void);
#endif
