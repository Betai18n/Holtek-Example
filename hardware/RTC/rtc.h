#ifndef __RTC_H_
#define __RTC_H_

#include "ht32f175x_275x.h"

//时间结构体
typedef struct 
{
	u8 hour;
	u8 min;
	u8 sec;

	u16 w_year;
	u8  w_month;
	u8  w_date;
	u8  week;
}tm;	



void rtc_init(void);
void rtc_return(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);

void RTC_Configuration(void);

/*
void Time_Display(void);
void set_time(void);
*/

u8 Is_Leap_Year(u16 year);//平年,闰年判断
void RTC_Get(void);         //更新时间
u8 RTC_Get_Week(u16 year,u8 month,u8 day);
void RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);//设置时间

extern tm timer;
extern tm timer1;
#endif

