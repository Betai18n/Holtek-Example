#include "rtc.h"
#include "led.h"

tm timer;//时钟结构体
tm timer1;
void rtc_init(void)
{
  CKCU_APBPerip1ClockConfig(CKCU_APBEN1_RTC, ENABLE);
  while(PWRCU_CheckReadyAccessed() != PWRCU_OK)
  {
    while(1);
  }
	NVIC_SetPriority(RTC_IRQn,NVIC_EncodePriority(5,0,3));
  NVIC_EnableIRQ(RTC_IRQn);
  if(PWRCU_ReadBackupRegister(PWRCU_BAKREG_0) != 0xA5A5)
  {
		
    RTC_Configuration();		
		RTC_Set(2014,5,10,8,55,50);  //设置初始时间
    PWRCU_WriteBackupRegister(PWRCU_BAKREG_0, 0xA5A5);
    RTC_Cmd(ENABLE) ;
  }	
}

void rtc_return(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec)
{
	//RTC_DeInit();
  //CKCU_APBPerip1ClockConfig(CKCU_APBEN1_RTC, ENABLE);
  while(PWRCU_CheckReadyAccessed() != PWRCU_OK)
  {
    while(1);
  }
	//NVIC_SetPriority(RTC_IRQn,NVIC_EncodePriority(5,0,3));
  //NVIC_EnableIRQ(RTC_IRQn);
	RTC_Cmd(DISABLE);
  if(PWRCU_ReadBackupRegister(PWRCU_BAKREG_0) != 0xA5A5)
  {
		
    RTC_Configuration();		
		RTC_Set(syear,smon,sday,hour,min,sec);  //设置初始时间
    PWRCU_WriteBackupRegister(PWRCU_BAKREG_0, 0xA5A5);
    RTC_Cmd(ENABLE) ;
  }	
}

void RTC_IRQHandler(void)//中断处理函数
{
  u8 bFlags ;

  bFlags = RTC_GetFlagStatus();
  if((bFlags & 0x2) != 0x0) /* Match flag */
  {
    /* Reset RTC init time when Time is 23:59:59 */
    RTC_SetCompare(86400) ;
    PWRCU_WriteBackupRegister(PWRCU_BAKREG_1, 0);//如果
  }
	RTC_Get();
  //GPIOA->DOUTR ^= GPIO_PIN_15;

}


//判断是否是闰年函数
//月份   1  2  3  4  5  6  7  8  9  10 11 12
//闰年   31 29 31 30 31 30 31 31 30 31 30 31
//非闰年 31 28 31 30 31 30 31 31 30 31 30 31
u8 Is_Leap_Year(u16 year)
{			  
	if(year%4==0) //必须能被4整除
		{ 
		if(year%100==0) 
			{
			if(year%400==0)return 1;//如果以00结尾,还要能被400整除 	   
			else return 0;   
			}else return 1;   
		}else return 0;	
}	

//设置时钟
//把输入的时钟转换为秒钟
//以1970年1月1日为基准
//1970~2099年为合法年份										 
u8 const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //月修正数据表	  

const u8 mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};//平年的月份日期表

void RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec)
{
	u16 t;
	u32 seccount=0;
	//if(syear<1970||syear>2099)return;	   
	for(t=1970;t<syear;t++)	//把所有年份的秒钟相加
	{
		if(Is_Leap_Year(t))seccount+=31622400;//闰年的秒钟数
		else seccount+=31536000;			  //平年的秒钟数
	}
	smon-=1;
	for(t=0;t<smon;t++)	   //把前面月份的秒钟数相加
	{
		seccount+=(u32)mon_table[t]*86400;//月份秒钟数相加
		if(Is_Leap_Year(syear)&&t==1)seccount+=86400;//闰年2月份增加一天的秒钟数	   
	}
	seccount+=(u32)(sday-1)*86400;//把前面日期的秒钟数相加 
	seccount+=(u32)hour*3600;//小时秒钟数
	seccount+=(u32)((min-16)*60);	 //分钟秒钟数
	seccount+=sec;//最后的秒钟加上去

	PWRCU_WriteBackupRegister(PWRCU_BAKREG_1, seccount);	//设置RTC计数器的值
	RTC_SetCompare(86400 - seccount) ;

}

//获得现在是星期几
//功能描述:输入公历日期得到星期(只允许1901-2099年)
//输入参数：公历年月日 
//返回值：星期号																						 
u8 RTC_Get_Week(u16 year,u8 month,u8 day)
{	
	u16 temp2;
	u8 yearH,yearL;
	
	yearH=year/100;	yearL=year%100; 
	// 如果为21世纪,年份数加100  
	if (yearH>19)yearL+=100;
	// 所过闰年数只算1900年之后的  
	temp2=yearL+yearL/4;
	temp2=temp2%7; 
	temp2=temp2+day+table_week[month-1];
	if (yearL%4==0&&month<3)temp2--;
	return(temp2%7);
} 


//得到当前的时间
//返回值:0,成功;其他:错误代码.
void RTC_Get(void)
{
	static u16 daycnt=0;
	u32 timecount=0; 
	u32 temp=0;
	u16 temp1=0;	  
	   
	timecount=(RTC_GetCounter() + PWRCU_ReadBackupRegister(PWRCU_BAKREG_1));//得到计数器中的值(秒钟数)
//	timecount<<=16;
//	timecount+=(RTC_GetCounter() + PWRCU_ReadBackupRegister(PWRCU_BAKREG_1));			 

	temp=timecount/86400;   //得到天数(秒钟数对应的)
	if(daycnt!=temp)//超过一天了
	{
		daycnt=temp;
		temp1=1970;	//从1970年开始
		while(temp>=365)
		{				 
			if(Is_Leap_Year(temp1))//是闰年
			{
				if(temp>=366)temp-=366;//闰年的秒钟数
				else {temp1++;break;}  
			}
			else temp-=365;	  //平年 
			temp1++;  
		}   
		timer.w_year=temp1;//得到年份
		temp1=0;
		while(temp>=28)//超过了一个月
		{
			if(Is_Leap_Year(timer.w_year)&&temp1==1)//当年是不是闰年/2月份
			{
				if(temp>=29)temp-=29;//闰年的秒钟数
				else break; 
			}
			else 
			{
				if(temp>=mon_table[temp1])temp-=mon_table[temp1];//平年
				else break;
			}
			temp1++;  
		}
		timer.w_month=temp1+1;//得到月份
		timer.w_date=temp+1;  //得到日期 
	}
	temp=timecount%86400;     //得到秒钟数   	   
	timer.hour=temp/3600;     //小时
	timer.min=(temp%3600)/60; //分钟	
	timer.sec=(temp%3600)%60; //秒钟
	timer.week=RTC_Get_Week(timer.w_year,timer.w_month,timer.w_date);//获取星期   
	
}	 

void RTC_Configuration(void)
{
  PWRCU_DeInit();
  RTC_LSESMConfig(RTC_LSESM_FAST);
  RTC_LSECmd(ENABLE);
  while(CKCU_GetClockReadyStatus(CKCU_FLAG_LSERDY) == RESET);
  RTC_ClockSourceConfig(RTC_SRC_LSE) ;
  RTC_IntConfig(RTC_INT_CSEC, ENABLE);
  RTC_SetPrescaler(RTC_RPRE_32768);
  RTC_CMPCLRCmd(ENABLE) ;
}


