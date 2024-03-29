/*********************************************************************************************************//**
 * @file    project_template/IP/Example/main.c
 * @version V1.0
 * @date    09/08/2011
 * @brief   Main program.
 *************************************************************************************************************
 *
 * <h2><center>Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f175x_275x.h"
#include "ht32f175x_275x_board.h"
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "timer.h"
#include "touch.h"
#include "lcd.h"
#include "main.h"
#include "disp.h"
#include "TN9.h"
#include "rtc.h"
#include "24bitAD.h"
#include "fan.h"
#include "24cxx.h"
#include "myiic.h"
#include "buzzer.h"
/** @addtogroup Project_Template Project Template
  * @{
  */

/** @addtogroup Template
  * @{
  */

/* Private typedef -----------------------------------------------------------------------------------------*/

/* Private define ------------------------------------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------------------------------------*/
void SysClockConfig_72MHz(void);


unsigned char ans[4]={0,0,0,'\0'};  //按键功能存放数组输出
unsigned char num;          //按键功能，用0-15之间的数字代表16个按键
unsigned int finaltime;     //剩余时间，大致范围在0-107之间，由finalTN9temp和finalselecttemp两个变量计算得到
unsigned int finalTN9temp;  //红外温度，用于计算剩余时间
unsigned int finalselecttemp;  //设定的温度，用于计算剩余时间
unsigned int finalsurroundtemp;
volatile unsigned int finalwater;      //本次测得的水量与上次水量之差
volatile unsigned int finalwaterlast;  //上一次测得的水量
volatile unsigned int needwater=1000;       //还需要的喝水量
unsigned char finalwaterdata[5]={'0','0','0','0','\0'};   //数组输出
volatile unsigned char config[4]={0,0,0,0};         //配置存放
unsigned char selecttemp[3]={51,51,'\0'};           //设定温度，数组存放用于12864显示，第一个是十位，第二个是个位，存放方式为ASCII
unsigned char const tempdata1[4][4]={{51,51,51,51},{52,51,52,52},{52,51,52,52},{52,52,52,53}};  //人群和季节对应的推荐设定温度，十位
unsigned char const tempdata2[4][4]={{51,48,52,54},{51,55,48,55},{53,53,50,55},{53,48,50,48}};  //人群和季节对应的推荐设定温度，个位
unsigned int const needdrink[4][4]={{1000,1200,1500,1200},{1500,1800,2000,1200},{1700,2000,2200,1500},{1200,1800,1800,1500}};//人群和季节对应的理想喝水量
unsigned char needdata[6]={'0','0','0','0','g','\0'};   //存放需要的喝水量数组
unsigned char table_mbtemp[8]={'0','0','.','0','0','^','C','\0'};   //红外测得的水温
unsigned char dN1[8]={'0','0','.','0','0','^','C','\0'};   //红外测得的室温
unsigned char finaltimedata[4]={'0','0','0','\0'}; //剩余时间，数组存放用于12864显示
unsigned char waterflagdata[2]={'0','\0'};

unsigned char const timedata[70][70]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{8,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{13,8,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{17,13,8,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{21,17,13,8,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{24,20,16,11,7,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{27,23,19,14,10,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{30,26,22,17,13,9,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{33,29,25,20,16,12,9,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{36,32,28,23,19,15,12,9,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{39,35,31,26,22,18,15,12,9,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{42,38,34,29,25,21,18,15,12,9,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{44,40,36,32,27,23,20,17,14,11,8,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{46,42,38,34,30,25,22,19,16,13,10,7,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{49,44,40,36,32,28,25,22,19,16,13,10,7,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{51,47,42,38,34,30,27,24,21,18,15,12,9,7,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{53,49,45,40,36,32,29,26,23,20,17,14,11,9,7,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{55,51,47,43,38,34,31,28,25,22,19,16,13,11,9,7,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{57,53,48,44,40,36,33,30,27,24,21,18,15,13,10,8,6,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{58,54,50,46,42,37,34,31,28,25,22,19,16,14,12,10,8,5,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{60,56,52,47,43,39,36,33,30,27,24,21,18,16,14,11,9,7,5,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{62,57,53,49,45,41,38,35,32,29,26,23,20,17,15,13,11,9,6,5,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{63,59,55,51,46,42,39,36,33,30,27,24,21,19,17,15,12,10,8,6,5,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{65,61,56,52,48,44,41,38,35,32,29,26,23,21,18,16,14,12,10,8,6,5,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{66,62,58,54,50,45,42,39,36,33,30,27,24,22,20,18,16,13,11,10,8,6,5,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{68,64,60,55,51,47,44,41,38,35,32,29,26,24,22,19,17,15,13,11,10,8,6,5,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{70,65,61,57,53,49,46,43,40,37,34,31,28,25,23,21,19,17,14,13,11,10,8,6,5,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{71,67,63,59,54,50,47,44,41,38,35,32,29,27,25,23,20,18,16,14,13,11,10,8,6,5,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{73,69,64,60,56,52,49,46,43,40,37,34,31,29,26,24,22,20,18,16,14,13,11,10,8,6,5,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{74,70,66,62,58,53,50,47,44,41,38,35,32,30,28,26,24,21,19,18,16,14,13,11,10,8,6,5,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{76,71,67,63,59,55,52,49,46,43,40,37,34,31,29,27,25,23,20,19,17,16,14,12,11,9,8,6,4,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{77,73,68,64,60,56,53,50,47,44,41,38,35,33,30,28,26,24,22,20,18,17,15,14,12,10,9,7,6,4,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{78,74,70,65,61,57,54,51,48,45,42,39,36,34,32,29,27,25,23,21,20,18,16,15,13,12,10,8,7,5,4,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{79,75,71,67,62,58,55,52,49,46,43,40,37,35,33,31,28,26,24,22,21,19,18,16,14,13,11,10,8,6,5,4,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{80,76,72,68,64,59,56,53,50,47,44,41,38,36,34,32,30,27,25,24,22,20,19,17,16,14,12,11,9,8,6,5,4,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{82,77,73,69,65,61,58,55,52,49,46,43,40,37,35,33,31,29,26,25,23,22,20,18,17,15,14,12,10,9,7,6,5,4,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{83,79,74,70,66,62,59,56,53,50,47,44,41,39,36,34,32,30,28,26,24,23,21,20,18,16,15,13,12,10,8,7,6,5,4,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{84,80,76,71,67,63,60,57,54,51,48,45,42,40,38,35,33,31,29,27,26,24,22,21,19,18,16,14,13,11,10,8,7,6,5,4,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{85,81,77,72,68,64,61,58,55,52,49,46,43,41,39,36,34,32,30,28,27,25,23,22,20,19,17,15,14,12,11,9,8,7,6,5,3,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{86,82,78,73,69,65,62,59,56,53,50,47,44,42,40,37,35,33,31,29,28,26,24,23,21,20,18,16,15,13,12,10,9,8,7,6,4,3,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{87,83,79,74,70,66,63,60,57,54,51,48,45,43,41,38,36,34,32,30,29,27,25,24,22,21,19,17,16,14,13,11,10,9,8,7,5,4,3,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{88,84,80,75,71,67,64,61,58,55,52,49,46,44,42,39,37,35,33,31,30,28,26,25,23,22,20,18,17,15,14,12,11,10,9,8,6,5,4,3,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{89,85,81,76,72,68,65,62,59,56,53,50,47,45,43,40,38,36,34,32,31,29,27,26,24,23,21,19,18,16,15,13,12,11,10,9,7,6,5,4,3,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{90,86,81,77,73,69,66,63,60,57,54,51,48,46,43,41,39,37,35,33,31,30,28,27,25,23,22,20,19,17,15,14,13,12,11,9,8,7,6,5,4,3,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{91,86,82,78,74,70,67,64,61,58,55,52,49,46,44,42,40,38,35,34,32,31,29,27,26,24,23,21,19,18,16,15,14,13,11,10,9,8,7,6,5,4,3,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{91,87,83,79,75,70,67,64,61,58,55,52,49,47,45,43,41,38,36,35,33,31,30,28,27,25,23,22,20,19,17,16,15,13,12,11,10,9,7,6,5,4,3,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{92,88,84,80,75,71,68,65,62,59,56,53,50,48,46,44,41,39,37,35,34,32,31,29,27,26,24,23,21,19,18,17,15,14,13,12,11,9,8,7,6,5,4,3,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{93,89,85,80,76,72,69,66,63,60,57,54,51,49,47,44,42,40,38,36,35,33,31,30,28,27,25,23,22,20,19,17,16,15,14,13,11,10,9,8,7,6,5,4,3,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{94,90,85,81,77,73,70,67,64,61,58,55,52,50,47,45,43,41,39,37,35,34,32,31,29,27,26,24,23,21,19,18,17,16,15,13,12,11,10,9,8,7,6,5,4,3,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{94,90,86,82,78,73,70,67,64,61,58,55,52,50,48,46,44,41,39,38,36,34,33,31,30,28,26,25,23,22,20,19,18,16,15,14,13,12,10,9,8,7,6,5,5,4,3,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{95,91,87,82,78,74,71,68,65,62,59,56,53,51,49,46,44,42,40,38,37,35,33,32,30,29,27,25,24,22,21,19,18,17,16,15,13,12,11,10,9,8,7,6,5,4,4,3,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{96,91,87,83,79,75,72,69,66,63,60,57,54,51,49,47,45,43,40,39,37,36,34,32,31,29,28,26,24,23,21,20,19,18,16,15,14,13,12,11,10,9,8,7,6,5,4,3,3,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{96,92,88,84,79,75,72,69,66,63,60,57,54,52,50,48,45,43,41,39,38,36,35,33,31,30,28,27,25,23,22,21,19,18,17,16,15,13,12,11,10,9,8,7,6,6,5,4,3,2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{97,93,88,84,80,76,73,70,67,64,61,58,55,53,50,48,46,44,42,40,38,37,35,34,32,30,29,27,26,24,22,21,20,19,18,16,15,14,13,12,11,10,9,8,7,6,5,5,4,3,2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{97,93,89,85,81,76,73,70,67,64,61,58,55,53,51,49,47,44,42,41,39,37,36,34,33,31,29,28,26,25,23,22,21,19,18,17,16,15,13,12,11,10,9,8,8,7,6,5,4,4,3,2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{98,94,90,85,81,77,74,71,68,65,62,59,56,54,52,49,47,45,43,41,40,38,36,35,33,32,30,28,27,25,24,22,21,20,19,18,16,15,14,13,12,11,10,9,8,7,7,6,5,4,4,3,2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{98,94,90,86,81,77,74,71,68,65,62,59,56,54,52,50,47,45,43,41,40,38,37,35,33,32,30,29,27,25,24,23,21,20,19,18,17,15,14,13,12,11,10,9,8,8,7,6,5,4,4,3,3,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{99,94,90,86,82,78,75,72,69,66,63,60,57,54,52,50,48,46,43,42,40,39,37,35,34,32,31,29,27,26,24,23,22,21,19,18,17,16,15,14,13,12,11,10,9,8,7,6,6,5,4,4,3,2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
{99,95,91,86,82,78,75,72,69,66,63,60,57,55,53,50,48,46,44,42,41,39,37,36,34,33,31,29,28,26,25,23,22,21,20,19,17,16,15,14,13,12,11,10,9,8,8,7,6,5,5,4,3,3,2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
{99,95,91,87,83,78,75,72,69,66,63,60,57,55,53,51,49,46,44,43,41,39,38,36,35,33,31,30,28,27,25,24,23,21,20,19,18,17,15,14,13,12,11,10,10,9,8,7,6,6,5,4,4,3,3,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
{100,96,91,87,83,79,76,73,70,67,64,61,58,56,53,51,49,47,45,43,41,40,38,37,35,33,32,30,29,27,25,24,23,22,21,19,18,17,16,15,14,13,12,11,10,9,8,8,7,6,5,5,4,4,3,2,2,2,1,1,0,0,0,0,0,0,0,0,0,0},
{100,96,92,88,83,79,76,73,70,67,64,61,58,56,54,52,49,47,45,43,42,40,39,37,35,34,32,31,29,27,26,25,23,22,21,20,19,17,16,15,14,13,12,11,10,10,9,8,7,6,6,5,5,4,3,3,2,2,2,1,1,0,0,0,0,0,0,0,0,0},
{101,96,92,88,84,80,77,74,71,68,65,62,59,56,54,52,50,48,45,44,42,41,39,37,36,34,33,31,29,28,26,25,24,23,21,20,19,18,17,16,15,14,13,12,11,10,9,8,8,7,6,6,5,4,4,3,3,2,2,2,1,1,0,0,0,0,0,0,0,0},
{101,97,93,88,84,80,77,74,71,68,65,62,59,57,55,52,50,48,46,44,43,41,39,38,36,35,33,31,30,28,27,25,24,23,22,21,19,18,17,16,15,14,13,12,11,10,10,9,8,7,7,6,5,5,4,4,3,3,2,2,2,1,1,0,0,0,0,0,0,0},
{101,97,93,89,85,80,77,74,71,68,65,62,59,57,55,53,51,48,46,45,43,41,40,38,37,35,33,32,30,29,27,26,25,23,22,21,20,19,17,16,15,14,13,12,12,11,10,9,8,8,7,6,6,5,5,4,3,3,3,2,2,2,1,1,0,0,0,0,0,0},
{102,98,93,89,85,81,78,75,72,69,66,63,60,58,55,53,51,49,47,45,43,42,40,39,37,35,34,32,31,29,27,26,25,24,23,21,20,19,18,17,16,15,14,13,12,11,10,10,9,8,7,7,6,6,5,4,4,4,3,3,2,2,2,1,1,0,0,0,0,0},
{102,98,94,90,85,81,78,75,72,69,66,63,60,58,56,54,51,49,47,45,44,42,41,39,37,36,34,33,31,29,28,27,25,24,23,22,21,19,18,17,16,15,14,13,12,12,11,10,9,8,8,7,7,6,5,5,4,4,4,3,3,2,2,2,1,1,0,0,0,0},
{103,98,94,90,86,82,79,76,73,70,67,64,61,58,56,54,52,50,47,46,44,43,41,39,38,36,35,33,31,30,28,27,26,25,23,22,21,20,19,18,17,16,15,14,13,12,11,10,10,9,8,8,7,6,6,5,5,4,4,4,3,3,2,2,2,1,1,0,0,0},
{103,99,95,90,86,82,79,76,73,70,67,64,61,59,57,54,52,50,48,46,45,43,41,40,38,37,35,33,32,30,29,27,26,25,24,23,21,20,19,18,17,16,15,14,13,12,12,11,10,9,9,8,7,7,6,6,5,5,4,4,4,3,3,2,2,2,1,1,0,0}};


unsigned int count1;//定时器计数器1,用于18B20的800ms延迟定时
unsigned int count2;//定时器计数器2,用于显示刷新和按键识别
unsigned int count3;//定时器计数器3,TN9定时
unsigned char count3flag;
unsigned int count4;//定时器计数器4，动作识别计时
unsigned int count5;
unsigned int count6;
volatile unsigned char flag18B20;//18B20状态识别，1表示18B20完成一次温度转换
unsigned char TN9flag;
volatile unsigned char startflag;//测温剩余时间开始标志，1表示开始计时
volatile unsigned char lockflag; //废水锁定标志，1表示锁定数值
volatile unsigned char fanflag;  //冷却风扇标志，1表示开启风扇
volatile unsigned char waterflag;//喝水动作判定，0表示水杯在杯座上，1表示拿起水杯，2表示喝完水后放回杯座
volatile unsigned char adflag;//24bitAD用于喝水动作的判定
unsigned char buzzerflag;
unsigned char keyflag;//按键标志，暂时未使用
float T0,T1,dt;//剩余时间计算，暂时未使用 

//void CKCU_Configuration(void);
u8 key=0;

#if (ENABLE_CKOUT == 1)
void CKOUTConfig(void);
#endif

/* Private functions ---------------------------------------------------------------------------------------*/

void Load_Drow_Dialog(void)
{
	LCD_Clear(WHITE);//清屏   
 	POINT_COLOR=BLUE;//设置字体为蓝色 
	LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//显示清屏区域
	LCD_ShowString(lcddev.width-24,lcddev.height-24,200,16,16,"OK");
  	POINT_COLOR=RED;//设置画笔蓝色 
}   					

void Fix_touch(void)
{
					if(key==1)//KEY0按下,则执行校准程序
					{
						LCD_Clear(WHITE);//清屏
							TP_Adjust();  //屏幕校准 
						TP_Save_Adjdata();	 
						Load_Drow_Dialog();
						TP_Get_Adjdata();	
					}
}
/*
void get_touch(void)
{
		if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
		{	
		 	if(tp_dev.x<lcddev.width&&tp_dev.y<lcddev.height)
			{	
				if(tp_dev.x>(lcddev.width-24)&&tp_dev.y<16)Load_Drow_Dialog();//清除
				else TP_Draw_Big_Point(tp_dev.x,tp_dev.y,RED);		//画图	  			   
			}
		}else delay_ms(10);	//没有按键按下的时候 	
}
*/

void keyfind(void)
{
					key=KEY_Scan();
					tp_dev.scan(0); 		 
					if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
					{	
						if(tp_dev.x<lcddev.width&&tp_dev.y<lcddev.height)
						{	
							/*
							if(tp_dev.x>(lcddev.width-24)&&tp_dev.y<16)Load_Drow_Dialog();//清除
							else TP_Draw_Big_Point(tp_dev.x,tp_dev.y,RED);		//画图	 */
							touchkey();
							/*************************/
							if(dispconfig[0]!=255)
							{
								configchanged();							
								Display();
							}
							/*************************/
							/*
							if(dispconfig[2]==5)
							{
									configchanged();//按键识别
									if(dispconfig[0]!=255)
									Display();
							}
							else if(dispconfig[0]!=255)
							{
									configchanged();//按键识别
									Display();//显示
							}*/
						}
					}
					else delay_ms(10);	//没有按键按下的时候
					
					if(key==1)	//KEY_RIGHT按下,则执行校准程序
					{
						dispconfig[2]=0;
						LCD_Clear(WHITE);//清屏
							TP_Adjust();  //屏幕校准 
						TP_Save_Adjdata();	 
						//Load_Drow_Dialog();
						Display_menu();
					}
}

void LoadData(void)
{
		config[1]=AT24CXX_ReadOneByte(60);
		config[2]=AT24CXX_ReadOneByte(61);
		selecttemp[0]=AT24CXX_ReadOneByte(62);
		selecttemp[1]=AT24CXX_ReadOneByte(63);
	  needwater=needdrink[config[1]][config[2]];
}

void SaveData(void)
{
		AT24CXX_WriteOneByte(60,config[1]);
		AT24CXX_WriteOneByte(61,config[2]);
		AT24CXX_WriteOneByte(62,selecttemp[0]);
		AT24CXX_WriteOneByte(63,selecttemp[1]);
}
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/

int main(void)
{

#if (HT32_LIB_DEBUG == 1)
  debug();
#endif

		//SysClockConfig_72MHz();
		NVIC_Configuration();               /* NVIC configuration                                                 */
		CKCU_Configuration();               /* System Related configuration                                       */
		delay_init(72);
		LED_Init();
		
	
		delay_ms(20);

		LCD_Init();

		/*
		POINT_COLOR=RED;//设置字体为蓝色	   
		//LCD_ShowxNum(100,100,123,3,16,1);//显示2个数字
		//LCD_ShowxNum(100,120,456,3,16,1);//显示2个数字
		LCD_ShowString(60,50,200,16,16,"HOLTEK");	
		LCD_ShowString(60,70,200,16,16,"Smart Cup Base");	
		LCD_ShowString(60,90,200,16,16,"CAUC");
		LCD_ShowString(60,110,200,16,16,"2014/05/10");*/
		delay_ms(20);
		
		Display_init();
		

		
		
		tp_dev.init();
		LoadData();
		delay_ms(1500);
		delay_ms(1500);
		delay_ms(1500);
		//Load_Drow_Dialog();
		
			
		KEY_Init();
		initAD();
		TN9init();
		faninit();
		buzzerinit();
		
		
		
		timer1.w_year=2014;
		timer1.w_month=5;
		timer1.w_date=10;
		timer1.hour=8;
		timer1.min=59;
		timer1.sec=50;
		
		count1=0;
		count2=0;
		count3=0;
		count4=0;
		count5=0;
    flag18B20=0;
    keyflag=0;
		startflag=0;
    ad_data=0;
    ad_datalast=0;
		def=8034484;
		TN9flag=0;
		dispconfig[2]=5;
		dispconfig[0]=255;
		
		//Display_menu();
		Display_index2();
		rtc_init();
		
		usart_init(USART1,9600);
		
		Timerx_Init(GPTM0,1000,7199);
		Timerx_Init(GPTM1,10,7199);
		while(1)                           /* Infinite loop                                                      */
		{
					keyfind();
					//if(adflag)
					{
						adflag=0;
						CovAD();
					}
					//buzzer=!buzzer;
					if(count3flag)
					{
						count3flag=0;
						if(dispconfig[2]==5)
						TN9COV();//TN9的测温函数
						
					}
		}
}


/*********************************************************************************************************//**
  * @brief  Configures the GPIO ports.
  * @retval None
  ***********************************************************************************************************/
/*void GPIO_Configuration(void)
{
#if (RETARGET_PORT == RETARGET_USART0)
  AFIO_GPCConfig(AFIO_PIN_8 | AFIO_PIN_10, AFIO_MODE_3);  // TX (PC8), RX (PC10)
#endif

#if (RETARGET_PORT == RETARGET_USART1)
  AFIO_GPCConfig(AFIO_PIN_4 | AFIO_PIN_5, AFIO_MODE_1);  // TX (PC4), RX (PC5)
#endif
}
*/
/*********************************************************************************************************//**
  * @brief  Configures USART.
  * @retval None
  ***********************************************************************************************************/
/*void USART_Configuration(void)
{
  USART_InitTypeDef USART_InitStructure;

  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
  USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
  USART_InitStructure.USART_Parity = USART_PARITY_NO;
  USART_InitStructure.USART_Mode = USART_MODE_NORMAL;
  USART_Init(RETARGET_USART_PORT, &USART_InitStructure);

  USART_TxCmd(RETARGET_USART_PORT, ENABLE);
  USART_RxCmd(RETARGET_USART_PORT, ENABLE);
}
*/



#if (HT32_LIB_DEBUG == 1)
/*********************************************************************************************************//**
  * @brief  Reports both the error name of the source file and the source line number.
  * @param  filename: pointer to the source file name.
  * @param  uline: error line source number.
  * @retval None
  ***********************************************************************************************************/
void assert_error(u8* filename, u32 uline)
{
  /*
     This function is called by IP library that the invalid parameters has been passed to the library API.
     Debug message can be added here.
  */

  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */
