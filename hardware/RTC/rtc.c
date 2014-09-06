#include "rtc.h"
#include "led.h"

tm timer;//ʱ�ӽṹ��
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
		RTC_Set(2014,5,10,8,55,50);  //���ó�ʼʱ��
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
		RTC_Set(syear,smon,sday,hour,min,sec);  //���ó�ʼʱ��
    PWRCU_WriteBackupRegister(PWRCU_BAKREG_0, 0xA5A5);
    RTC_Cmd(ENABLE) ;
  }	
}

void RTC_IRQHandler(void)//�жϴ�����
{
  u8 bFlags ;

  bFlags = RTC_GetFlagStatus();
  if((bFlags & 0x2) != 0x0) /* Match flag */
  {
    /* Reset RTC init time when Time is 23:59:59 */
    RTC_SetCompare(86400) ;
    PWRCU_WriteBackupRegister(PWRCU_BAKREG_1, 0);//���
  }
	RTC_Get();
  //GPIOA->DOUTR ^= GPIO_PIN_15;

}


//�ж��Ƿ������꺯��
//�·�   1  2  3  4  5  6  7  8  9  10 11 12
//����   31 29 31 30 31 30 31 31 30 31 30 31
//������ 31 28 31 30 31 30 31 31 30 31 30 31
u8 Is_Leap_Year(u16 year)
{			  
	if(year%4==0) //�����ܱ�4����
		{ 
		if(year%100==0) 
			{
			if(year%400==0)return 1;//�����00��β,��Ҫ�ܱ�400���� 	   
			else return 0;   
			}else return 1;   
		}else return 0;	
}	

//����ʱ��
//�������ʱ��ת��Ϊ����
//��1970��1��1��Ϊ��׼
//1970~2099��Ϊ�Ϸ����										 
u8 const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //���������ݱ�	  

const u8 mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};//ƽ����·����ڱ�

void RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec)
{
	u16 t;
	u32 seccount=0;
	//if(syear<1970||syear>2099)return;	   
	for(t=1970;t<syear;t++)	//��������ݵ��������
	{
		if(Is_Leap_Year(t))seccount+=31622400;//�����������
		else seccount+=31536000;			  //ƽ���������
	}
	smon-=1;
	for(t=0;t<smon;t++)	   //��ǰ���·ݵ����������
	{
		seccount+=(u32)mon_table[t]*86400;//�·����������
		if(Is_Leap_Year(syear)&&t==1)seccount+=86400;//����2�·�����һ���������	   
	}
	seccount+=(u32)(sday-1)*86400;//��ǰ�����ڵ���������� 
	seccount+=(u32)hour*3600;//Сʱ������
	seccount+=(u32)((min-16)*60);	 //����������
	seccount+=sec;//�������Ӽ���ȥ

	PWRCU_WriteBackupRegister(PWRCU_BAKREG_1, seccount);	//����RTC��������ֵ
	RTC_SetCompare(86400 - seccount) ;

}

//������������ڼ�
//��������:���빫�����ڵõ�����(ֻ����1901-2099��)
//������������������� 
//����ֵ�����ں�																						 
u8 RTC_Get_Week(u16 year,u8 month,u8 day)
{	
	u16 temp2;
	u8 yearH,yearL;
	
	yearH=year/100;	yearL=year%100; 
	// ���Ϊ21����,�������100  
	if (yearH>19)yearL+=100;
	// ����������ֻ��1900��֮���  
	temp2=yearL+yearL/4;
	temp2=temp2%7; 
	temp2=temp2+day+table_week[month-1];
	if (yearL%4==0&&month<3)temp2--;
	return(temp2%7);
} 


//�õ���ǰ��ʱ��
//����ֵ:0,�ɹ�;����:�������.
void RTC_Get(void)
{
	static u16 daycnt=0;
	u32 timecount=0; 
	u32 temp=0;
	u16 temp1=0;	  
	   
	timecount=(RTC_GetCounter() + PWRCU_ReadBackupRegister(PWRCU_BAKREG_1));//�õ��������е�ֵ(������)
//	timecount<<=16;
//	timecount+=(RTC_GetCounter() + PWRCU_ReadBackupRegister(PWRCU_BAKREG_1));			 

	temp=timecount/86400;   //�õ�����(��������Ӧ��)
	if(daycnt!=temp)//����һ����
	{
		daycnt=temp;
		temp1=1970;	//��1970�꿪ʼ
		while(temp>=365)
		{				 
			if(Is_Leap_Year(temp1))//������
			{
				if(temp>=366)temp-=366;//�����������
				else {temp1++;break;}  
			}
			else temp-=365;	  //ƽ�� 
			temp1++;  
		}   
		timer.w_year=temp1;//�õ����
		temp1=0;
		while(temp>=28)//������һ����
		{
			if(Is_Leap_Year(timer.w_year)&&temp1==1)//�����ǲ�������/2�·�
			{
				if(temp>=29)temp-=29;//�����������
				else break; 
			}
			else 
			{
				if(temp>=mon_table[temp1])temp-=mon_table[temp1];//ƽ��
				else break;
			}
			temp1++;  
		}
		timer.w_month=temp1+1;//�õ��·�
		timer.w_date=temp+1;  //�õ����� 
	}
	temp=timecount%86400;     //�õ�������   	   
	timer.hour=temp/3600;     //Сʱ
	timer.min=(temp%3600)/60; //����	
	timer.sec=(temp%3600)%60; //����
	timer.week=RTC_Get_Week(timer.w_year,timer.w_month,timer.w_date);//��ȡ����   
	
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


