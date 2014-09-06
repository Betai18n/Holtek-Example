#include "ht32f175x_275x.h"
#include "ht32f175x_275x_board.h"
#include "disp.h"
#include "TN9.h"
#include "24bitAD.h"
#include "lcd.h"
#include "sys.h" 
#include "delay.h"
#include "rtc.h"
#include "main.h"
#include "chinese.h"




//������12864����ʾ��λ��Ӧ������ֵ��4��*8��
/*
0x80 ~ 0x87
0x90 ~ 0x97
0x88 ~ 0x8f
0x98 ~ 0x9f
*/

/*
dispconfig�д����ʾ��������ã�������������Ϊ���ж�
0�д�ŵ��ǰ�������ֵ��0-15��ʾ16����ͬ�İ���
1�д�ŵ��ǵ�ǰ�ļ�ͷλ��
2�д�ŵ��ǵ�ǰ��Ļ��ʾ��ҳ�棬Ŀǰ�����7����ͬ��ҳ�棬��0-6��ʾ
3��ʱδʹ��
*/
volatile unsigned char dispconfig[4]={0,0,0,0};
void Display_first(void)
{
			//LCD_ShowString(60,50,200,16,16,"���ڳ�ʼ��");

}
void Display_init(void)//����ʱ����ʼ����
{
      LCD_Clear(WHITE);//����   
			POINT_COLOR=BLUE;//��������Ϊ��ɫ 
			//LCD_ShowString(140,150,200,16,16,"HOLTEK");	
			//LCD_ShowString(120,210,200,16,16,"Smart Cup Base");	
			TEST_FONT1();
			TEST_FONT2();
			TEST_FONT3();
			TEST_FONT4();
			TEST_FONT5();
			TEST_FONT6();
			//LCD_ShowString(150,250,200,16,16,"CAUC");
			//LCD_ShowString(130,290,200,16,16,"2014/05/10");
}

void Display_menu(void)//��ʼѡ��˵����棬����0
{
      LCD_Clear(WHITE);
			POINT_COLOR=BLUE;//��������Ϊ��ɫ
      LCD_ShowString(60,50,200,16,16,"Main menu:");
      LCD_ShowString(60,90,200,16,16,"People categories");
      LCD_ShowString(60,130,200,16,16,"Seasonal Option");
      LCD_ShowString(60,170,200,16,16,"Ideal temperature");
			LCD_ShowString(lcddev.width-48,lcddev.height-24,200,16,16,"Save");
			LCD_ShowString(24,lcddev.height-24,200,16,16,"Fix Weight");
			LCD_DrawRectangle(55,85,220,110);
			LCD_DrawRectangle(55,125,220,150);
			LCD_DrawRectangle(55,165,220,190);
			LCD_ShowString(60,200,200,16,16,"The Option Selected");
	    LCD_ShowString(60,220,200,16,16,"People:");
      LCD_ShowString(60,240,200,16,16,"Season:");
			LCD_ShowString(60,260,200,16,16,"Ideal temperature:");
			LCD_ShowString(230,260,200,16,16,selecttemp);
			LCD_ShowString(250,260,200,16,16,"^C");
			 switch(config[1])//��֮ǰ��ѡ�������ʾ�жϣ���ͬ����ֵ��ʾ��ͬ�Ľ��
      {
          case 0: LCD_ShowString(170,220,200,16,16,"Child");break;
          case 1: LCD_ShowString(170,220,200,16,16,"Teen");break;
          case 2: LCD_ShowString(170,220,200,16,16,"Middle age");break;
          case 3: LCD_ShowString(170,220,200,16,16,"The aged");break;
      }
      switch(config[2])
      {
           case 0: LCD_ShowString(170,240,200,16,16,"Spring");break;
           case 1: LCD_ShowString(170,240,200,16,16,"Summer");break;
           case 2: LCD_ShowString(170,240,200,16,16,"Autumn");break;
           case 3: LCD_ShowString(170,240,200,16,16,"Winter");break;
      }
			LCD_ShowString(lcddev.width-24,0,200,16,16,"RTC");
}

void Display_menupeople(void)//��Ⱥ����趨���棬����1
{
      LCD_Clear(WHITE);
			POINT_COLOR=BLUE;//��������Ϊ��ɫ
      LCD_ShowString(60,50,200,16,16,"Child");
      LCD_ShowString(60,90,200,16,16,"Teen");
      LCD_ShowString(60,130,200,16,16,"Middle age");
      LCD_ShowString(60,170,200,16,16,"The aged");
			LCD_DrawRectangle(55,45,220,70);
			LCD_DrawRectangle(55,85,220,110);
			LCD_DrawRectangle(55,125,220,150);
			LCD_DrawRectangle(55,165,220,190);
			LCD_ShowString(24,lcddev.height-24,200,16,16,"Back");
}

void Display_menuseason(void)//����ѡ���趨���棬����2
{
      LCD_Clear(WHITE);
			POINT_COLOR=BLUE;//��������Ϊ��ɫ
      LCD_ShowString(60,50,200,16,16,"Spring");
      LCD_ShowString(60,90,200,16,16,"Summer");
      LCD_ShowString(60,130,200,16,16,"Autumn");
      LCD_ShowString(60,170,200,16,16,"Winter");
			LCD_DrawRectangle(55,45,220,70);
			LCD_DrawRectangle(55,85,220,110);
			LCD_DrawRectangle(55,125,220,150);
			LCD_DrawRectangle(55,165,220,190);
			LCD_ShowString(24,lcddev.height-24,200,16,16,"Back");
}

void Display_temp(void)//�趨ˮ�½��棬����3
{
      LCD_Clear(WHITE);
			POINT_COLOR=BLUE;//��������Ϊ��ɫ
      LCD_ShowString(60,50,200,16,16,"Ideal temperature");
      LCD_ShowString(60,70,200,16,16,selecttemp);
      LCD_ShowString(90,70,200,16,16,"^C");
			LCD_ShowString(60,130,200,16,16,"+10");
			LCD_DrawRectangle(55,125,220,150);
			LCD_ShowString(60,170,200,16,16,"-10");
			LCD_DrawRectangle(55,165,220,190);
			LCD_ShowString(60,210,200,16,16,"+1");
			LCD_DrawRectangle(55,205,220,230);
			LCD_ShowString(60,250,200,16,16,"-1");
			LCD_DrawRectangle(55,245,220,270);
			LCD_ShowString(24,lcddev.height-24,200,16,16,"Back");
}

void Display_index1(void)//������ʱ�ӵ�У׼������4
{
      LCD_Clear(WHITE);
      LCD_ShowString(60,50,200,16,16,"The Current Time");
			LCD_ShowxNum(30,70,timer.w_year,16,16,0x01);
			LCD_ShowxNum(50,70,timer.w_month,16,16,0x01);
			LCD_ShowxNum(70,70,timer.w_date,16,16,0x01);
			LCD_ShowxNum(90,70,timer.hour,16,16,0x01);
			LCD_ShowxNum(110,70,timer.min,16,16,0x01);
			LCD_ShowxNum(130,70,timer.sec,16,16,0x01);
			LCD_ShowString(60,90,200,16,16,"The Setting Time");
			LCD_ShowxNum(30,110,timer1.w_year,16,16,0x01);
			LCD_ShowxNum(50,110,timer1.w_month,16,16,0x01);
			LCD_ShowxNum(70,110,timer1.w_date,16,16,0x01);
			LCD_ShowxNum(90,110,timer1.hour,16,16,0x01);
			LCD_ShowxNum(110,110,timer1.min,16,16,0x01);
			LCD_ShowxNum(130,110,timer1.sec,16,16,0x01);
			LCD_ShowString(60,130,75,16,16,"year+1");
			LCD_DrawRectangle(55,125,130,150);
			LCD_ShowString(60,170,75,16,16,"year-1");
			LCD_DrawRectangle(55,165,130,190);
			LCD_ShowString(60,210,75,16,16,"month+1");
			LCD_DrawRectangle(55,205,130,230);
			LCD_ShowString(60,250,75,16,16,"month-1");
			LCD_DrawRectangle(55,245,130,270);
			LCD_ShowString(60,290,75,16,16,"day+1");
			LCD_DrawRectangle(55,285,130,310);
			LCD_ShowString(60,330,75,16,16,"day-1");
			LCD_DrawRectangle(55,325,130,350);
			LCD_ShowString(150,130,75,16,16,"hour+1");
			LCD_DrawRectangle(145,125,220,150);
			LCD_ShowString(150,170,75,16,16,"hour-1");
			LCD_DrawRectangle(145,165,220,190);
			LCD_ShowString(150,210,75,16,16,"min+1");
			LCD_DrawRectangle(145,205,220,230);
			LCD_ShowString(150,250,75,16,16,"min-1");
			LCD_DrawRectangle(145,245,220,270);
			LCD_ShowString(150,290,75,16,16,"sec+1");
			LCD_DrawRectangle(145,285,220,310);
			LCD_ShowString(150,330,75,16,16,"sec-1");
			LCD_DrawRectangle(145,325,220,350);
			LCD_ShowString(24,lcddev.height-24,75,16,16,"Back");
			LCD_ShowString(lcddev.width-48,lcddev.height-24,200,16,16,"Save");
}

void Display_index2(void)//��ҳ2������5
{
      LCD_Fill(0,0,320,480,WHITE);
	    needdata[0]=needwater/1000+48;
      needdata[1]=needwater%1000/100+48;
      needdata[2]=needwater%1000%100/10+48;
      needdata[3]=needwater%1000%100%10+48;//����Ҫ�ĺ�ˮ������ASCIIת��
      if(startflag)
      {
        finaltimedata[0]=finaltime/100+48;
        finaltimedata[1]=finaltime%100/10+48;
        finaltimedata[2]=finaltime%100%10+48;//�ڿ�ʼ����ʣ��ʱ��󣬴˴�����ʣ��ʱ���ASCIIת��
      }
      else if(!startflag)
      {
        finaltimedata[0]=48;
        finaltimedata[1]=48;
        finaltimedata[2]=48;//��û�п�ʼ����ʣ��ʱ��ʱ����ʾ��ʣ��ʱ��Ϊ000
      }
      waterflagdata[0]=waterflag+48;
			LCD_ShowString(120,20,200,16,16,"Designed by CAUC");
      LCD_ShowString(60,50,200,16,16,"People:");
      LCD_ShowString(60,70,200,16,16,"Season:");
			LCD_ShowString(60,90,200,16,16,"Water temperature");
			LCD_ShowString(230,90,200,16,16,table_mbtemp);
			LCD_ShowString(60,110,200,16,16,"Ideal temperature");
			LCD_ShowString(230,110,200,16,16,selecttemp);
			LCD_ShowString(250,110,200,16,16,"^C");
			LCD_ShowString(60,130,200,16,16,"Room temperature");
      LCD_ShowString(230,130,200,16,16,dN1);
			
      switch(config[1])//��֮ǰ��ѡ�������ʾ�жϣ���ͬ����ֵ��ʾ��ͬ�Ľ��
      {
          case 0: LCD_ShowString(170,50,200,16,16,"Child");break;
          case 1: LCD_ShowString(170,50,200,16,16,"Teen");break;
          case 2: LCD_ShowString(170,50,200,16,16,"Middle age");break;
          case 3: LCD_ShowString(170,50,200,16,16,"The aged");break;
      }
      switch(config[2])
      {
           case 0: LCD_ShowString(170,70,200,16,16,"Spring");break;
           case 1: LCD_ShowString(170,70,200,16,16,"Summer");break;
           case 2: LCD_ShowString(170,70,200,16,16,"Autumn");break;
           case 3: LCD_ShowString(170,70,200,16,16,"Winter");break;
      }
			
			LCD_ShowString(60,150,200,16,16,"The current water");
			LCD_ShowString(230,150,200,16,16,Data);
      LCD_ShowString(60,170,200,16,16,"The required water");
			LCD_ShowString(230,170,200,16,16,needdata);
      LCD_ShowString(60,190,200,16,16,"Remaining Time");
			LCD_ShowString(230,190,200,16,16,finaltimedata);
			LCD_ShowString(260,190,32,16,16,"min");
			if(startflag==0)
				LCD_ShowString(60,230,200,16,16,"System on");
			else if(startflag==1)
				LCD_ShowString(60,230,200,16,16,"System off");
			LCD_DrawRectangle(55,225,200,250);
			if(fanflag==0)
				LCD_ShowString(60,270,200,16,16,"Fan on");
			else if(fanflag==1)
				LCD_ShowString(60,270,200,16,16,"Fan off");
			LCD_DrawRectangle(55,265,200,290);
			LCD_ShowString(300,350,200,16,16,waterflagdata);
			LCD_ShowxNum(40,310,timer.w_year,4,16,0x01);
			LCD_ShowString(80,310,8,16,16,"-");
			LCD_ShowxNum(90,310,timer.w_month,2,16,0x01);
			LCD_ShowString(110,310,8,16,16,"-");
			LCD_ShowxNum(120,310,timer.w_date,2,16,0x01);
			LCD_ShowxNum(150,310,timer.hour,2,16,0x01);
		  LCD_ShowString(170,310,8,16,16,"-");
			LCD_ShowxNum(180,310,timer.min,2,16,0x01);
			LCD_ShowString(200,310,8,16,16,"-");
			LCD_ShowxNum(210,310,timer.sec,2,16,0x01);
			LCD_ShowString(24,lcddev.height-24,200,16,16,"Setting");
			LCD_ShowString(lcddev.width-64,lcddev.height-24,200,16,16,"Refresh");
			LCD_ShowString(120,lcddev.height-24,60,16,16,"Reload");
}

const u8* TheWeightFix="Now let's fix the weight.Andyou should keep all clean   on the weighing sensor";
void Display_index3(void)//����У�����棬����6
{
      LCD_Clear(WHITE);
      LCD_ShowString(60,50,200,16,16,"Weight fixed");
			LCD_ShowString(60,70,200,16,16,"The Correct Data");
      LCD_ShowString(230,70,200,16,16,Data1);
			LCD_ShowString(230,90,200,16,16,Data);
			LCD_ShowString(40,150,220,200,16,(u8*)TheWeightFix);
			LCD_ShowString(24,lcddev.height-24,200,16,16,"Back");
			LCD_ShowString(lcddev.width-24,lcddev.height-24,200,16,16,"Fix");
}

void Display_debug(void)//debugʱר�ý��棬���������������ʾ
{
        LCD_Clear(WHITE);
				LCD_ShowString(60,50,200,16,16,dN1);
				LCD_ShowString(60,70,200,16,16,ans);
        LCD_ShowString(60,90,200,16,16,Data);
        LCD_ShowString(70,110,200,16,16,"Mode:Debug");
}

//dispconfig  0 ���̶��� 1 ���λ�� 2 ҳ�� 3 undefined
void Display(void)      //��ʾ�������ڶ�ʱ���ж���ִ��
{
         
        /*-------------------------------------------------*/
        switch(dispconfig[2])//������ʾ��������ȷ��ҳ��λ��
        {
            case 0 : Display_menu();break;
            case 1 : Display_menupeople();break;
            case 2 : Display_menuseason();break;
            case 3 : Display_temp();break;
            case 4 : Display_index1();break;
            case 5 : Display_index2();break;
            case 6 : Display_index3();break;
        }
        /*-----------------------------------------------------
        �м�ԭ���Ƕ԰����������ж�ִ�У����ڵ������ɺ����ŵ���ʱ��
        �ж��У�λ��ִ���걾����֮ǰ��������configchanged()
          ---------------------------------------------------*/
        /*{
          //������ʾ��ͷ��λ��
            if(dispconfig[2]!=3)
            {
                if(dispconfig[2]==0)//�˵�ѡ����ֻ��Ҫ������ͷλ�ã��ӵ�2��λ�ÿ�ʼ
                  Display_arrows((dispconfig[1]+1));
                else if((dispconfig[2]==1)||(dispconfig[2]==2))//��Ⱥ�ͼ��ڽ�������Ҫ�ĸ���ͷλ��
                {
                  Display_arrows(dispconfig[1]);
                  Display_selected(dispconfig[2]);
                }
            }
            else if(dispconfig[2]==3)//�����������¶��趨����ʱ���Ҽ�ͷ�����ϼ�ͷ
              Display_uparrows(dispconfig[1]);
        }*/
}

void Display_update3(void)
{
			LCD_Fill(55,225,200,250,WHITE);
			LCD_Fill(55,265,200,290,WHITE);
			if(startflag==0)
				LCD_ShowString(60,230,200,16,16,"System on");
			else if(startflag==1)
				LCD_ShowString(60,230,200,16,16,"System off");
			LCD_DrawRectangle(55,225,200,250);
			if(fanflag==0)
				LCD_ShowString(60,270,200,16,16,"Fan on");
			else if(fanflag==1)
				LCD_ShowString(60,270,200,16,16,"Fan off");
			LCD_DrawRectangle(55,265,200,290);
}

void Display_update2(void)
{
			LCD_Fill(30,70,330,86,WHITE);
			LCD_ShowxNum(30,70,timer.w_year,16,16,0x01);
			LCD_ShowxNum(50,70,timer.w_month,16,16,0x01);
			LCD_ShowxNum(70,70,timer.w_date,16,16,0x01);
			LCD_ShowxNum(90,70,timer.hour,16,16,0x01);
			LCD_ShowxNum(110,70,timer.min,16,16,0x01);
			LCD_ShowxNum(130,70,timer.sec,16,16,0x01);

}

void Display_update1(void)
{
			//LCD_ShowString(60,90,200,16,16,"Room temperature:");
			LCD_Fill(230,70,300,86,WHITE);
			LCD_ShowString(230,70,200,16,16,Data1);
			//LCD_ShowString(60,130,200,16,16,"The current water");
			LCD_Fill(230,90,300,106,WHITE);
			LCD_ShowString(230,90,200,16,16,Data);
}

void Display_update(void)
{
			needdata[0]=needwater/1000+48;
      needdata[1]=needwater%1000/100+48;
      needdata[2]=needwater%1000%100/10+48;
      needdata[3]=needwater%1000%100%10+48;//����Ҫ�ĺ�ˮ������ASCIIת��
      if(startflag)
      {
        finaltimedata[0]=finaltime/100+48;
        finaltimedata[1]=finaltime%100/10+48;
        finaltimedata[2]=finaltime%100%10+48;//�ڿ�ʼ����ʣ��ʱ��󣬴˴�����ʣ��ʱ���ASCIIת��
      }
      else if(!startflag)
      {
        finaltimedata[0]=48;
        finaltimedata[1]=48;
        finaltimedata[2]=48;//��û�п�ʼ����ʣ��ʱ��ʱ����ʾ��ʣ��ʱ��Ϊ000
      }
      waterflagdata[0]=waterflag+48;
			//LCD_ShowString(60,90,200,16,16,"Room temperature:");
			LCD_Fill(230,90,300,106,WHITE);
			LCD_ShowString(230,90,200,16,16,table_mbtemp);

			
			//LCD_ShowString(60,130,200,16,16,"The current water");
			LCD_Fill(230,130,300,146,WHITE);
			LCD_ShowString(230,130,200,16,16,dN1);
			LCD_Fill(230,150,300,166,WHITE);
			LCD_ShowString(230,150,200,16,16,Data);
			LCD_Fill(230,170,300,186,WHITE);
			LCD_ShowString(230,170,200,16,16,needdata);
			LCD_Fill(230,190,260,206,WHITE);
			LCD_ShowString(230,190,200,16,16,finaltimedata);
			
      //LCD_ShowString(60,150,200,16,16,"The required water");
			
			
      //LCD_ShowString(60,170,200,16,16,"Remaining Time");
			
			
      //LCD_ShowString(60,190,200,16,16,"Water temperature");
			
      
			LCD_Fill(300,350,320,366,WHITE);
      LCD_ShowString(300,350,200,16,16,waterflagdata);
			LCD_Fill(170,50,240,66,WHITE);
			
			LCD_Fill(170,70,240,86,WHITE);
	    switch(config[1])//��֮ǰ��ѡ�������ʾ�жϣ���ͬ����ֵ��ʾ��ͬ�Ľ��
      {
          case 0: LCD_ShowString(170,50,200,16,16,"Child");break;
          case 1: LCD_ShowString(170,50,200,16,16,"Teen");break;
          case 2: LCD_ShowString(170,50,200,16,16,"Middle age");break;
          case 3: LCD_ShowString(170,50,200,16,16,"The aged");break;
      }
      switch(config[2])
      {
           case 0: LCD_ShowString(170,70,200,16,16,"Spring");break;
           case 1: LCD_ShowString(170,70,200,16,16,"Summer");break;
           case 2: LCD_ShowString(170,70,200,16,16,"Autumn");break;
           case 3: LCD_ShowString(170,70,200,16,16,"Winter");break;
      }
			LCD_Fill(30,310,310,346,WHITE);
			LCD_ShowxNum(40,310,timer.w_year,4,16,0x01);
			LCD_ShowString(80,310,8,16,16,"-");
			LCD_ShowxNum(90,310,timer.w_month,2,16,0x01);
			LCD_ShowString(110,310,8,16,16,"-");
			LCD_ShowxNum(120,310,timer.w_date,2,16,0x01);
			LCD_ShowxNum(150,310,timer.hour,2,16,0x01);
		  LCD_ShowString(170,310,8,16,16,"-");
			LCD_ShowxNum(180,310,timer.min,2,16,0x01);
			LCD_ShowString(200,310,8,16,16,"-");
			LCD_ShowxNum(210,310,timer.sec,2,16,0x01);
}
