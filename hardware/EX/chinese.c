#include "chinese.h"
#include "chfont.h"
#include "lcd.h"	   

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32�����塪����չʵ��
//�Զ��庺����ʾ  ����			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/7/6
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  
			    
					
#define MOVIE_XSIZE	100 
#define MOVIE_YSIZE 40  
#define FRAME_SIZE MOVIE_XSIZE*MOVIE_YSIZE/8  

//��LCD�ϵģ�x��y��������
//color�������ɫ
void LCD_Draw_Point1(u16 x,u16 y,u16 color)
{
	u16 temp;
	temp=POINT_COLOR;
	POINT_COLOR=color;
    LCD_DrawPoint(x,y);
	POINT_COLOR=temp;
}

//��ָ��λ�� ��ʾ1��16*16�ĺ���
//(x,y):������ʾ��λ��
//index:tfont��������ĵڼ�������
//color:������ֵ���ɫ
void Test_Show_CH_Font16(u16 x,u16 y,u8 index,u16 color)
{   			    
	u8 temp,t,t1;
	u16 y0=y;				   
    for(t=0;t<32;t++)//ÿ��16*16�ĺ��ֵ��� ��32���ֽ�
    {   
		if(t<16)temp=tfont16[index*2][t];      //ǰ16���ֽ�
		else temp=tfont16[index*2+1][t-16];    //��16���ֽ�	                          
        for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)LCD_Draw_Point1(x,y,color);//��ʵ�ĵ�
			else LCD_Draw_Point1(x,y,BACK_COLOR);   //���հ׵㣨ʹ�ñ���ɫ��
			temp<<=1;
			y++;
			if((y-y0)==16)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }          
}

void Test_Show_CH_Font24(u16 x,u16 y,u8 index,u16 color)
{   			    
	u8 temp,t,t1;
	u16 y0=y;				   
    for(t=0;t<72;t++)//ÿ��24*24�ĺ��ֵ��� ��72���ֽ�
    {   
		if(t<24)temp=tfont24[index*3][t];           //ǰ24���ֽ�
		else if(t<48)temp=tfont24[index*3+1][t-24]; //��24���ֽ�	                          
        else temp=tfont24[index*3+2][t-48];         //��24���ֽ�
	    for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)LCD_Draw_Point1(x,y,color);//��ʵ�ĵ�
			else LCD_Draw_Point1(x,y,BACK_COLOR);   //���հ׵㣨ʹ�ñ���ɫ��
			temp<<=1;
			y++;
			if((y-y0)==24)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }          
}

void Test_Show_CH1_Font48(u16 x,u16 y,u8 index,u16 color)
{   			    
	u8 temp,t,t1;
	u16 y0=y;				   
    for(t=0;t<64;t++)//ÿ��48*48�ĺ��ֵ��� ��144���ֽ�
    {   
		if(t<32)temp=tfont48_1[index*2][t];           //ǰ24���ֽ�
		else temp=tfont48_1[index*2+1][t-32]; //��24���ֽ�	                                             
	    for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)LCD_Draw_Point1(x,y,color);//��ʵ�ĵ�
			else LCD_Draw_Point1(x,y,BACK_COLOR);   //���հ׵㣨ʹ�ñ���ɫ��
			temp<<=1;
			y++;
			if((y-y0)==32)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }          
}

//����2��������ʾ����
void TEST_FONT1(void)
{
	u8 t;
	u8 x;
	x=30;
	for(t=0;t<6;t++)//6������
	{
		Test_Show_CH1_Font48(x ,30,t,BLUE);
		x+=32;
	}
}

void Test_Show_CH2_Font48(u16 x,u16 y,u8 index,u16 color)
{   			    
	u8 temp,t,t1;
	u16 y0=y;				   
    for(t=0;t<64;t++)//ÿ��48*48�ĺ��ֵ��� ��144���ֽ�
    {   
		if(t<32)temp=tfont48_2[index*2][t];           //ǰ48���ֽ�
		else  temp=tfont48_2[index*2+1][t-32]; //��48���ֽ�	                          
	    for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)LCD_Draw_Point1(x,y,color);//��ʵ�ĵ�
			else LCD_Draw_Point1(x,y,BACK_COLOR);   //���հ׵㣨ʹ�ñ���ɫ��
			temp<<=1;
			y++;
			if((y-y0)==32)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }          
}

//����2��������ʾ����
void TEST_FONT2(void)
{
	u8 t;
	u8 x;
	x=30;
	for(t=0;t<5;t++)//6������
	{
		Test_Show_CH2_Font48(x ,100,t,BLUE);
		x+=32;
	}
}

void Test_Show_CH3_Font48(u16 x,u16 y,u8 index,u16 color)
{   			    
	u8 temp,t,t1;
	u16 y0=y;				   
    for(t=0;t<64;t++)//ÿ��48*48�ĺ��ֵ��� ��144���ֽ�
    {   
		if(t<32)temp=tfont48_3[index*2][t];           //ǰ48���ֽ�
		else temp=tfont48_3[index*2+1][t-32]; //��48���ֽ�	                          
	    for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)LCD_Draw_Point1(x,y,color);//��ʵ�ĵ�
			else LCD_Draw_Point1(x,y,BACK_COLOR);   //���հ׵㣨ʹ�ñ���ɫ��
			temp<<=1;
			y++;
			if((y-y0)==32)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }          
}

//����2��������ʾ����
void TEST_FONT3(void)
{
	u8 t;
	u8 x;
	x=30;
	for(t=0;t<8;t++)//6������
	{
		Test_Show_CH3_Font48(x ,170,t,BLUE);
		x+=32;
	}
}

void Test_Show_CH4_Font48(u16 x,u16 y,u8 index,u16 color)
{   			    
	u8 temp,t,t1;
	u16 y0=y;				   
    for(t=0;t<64;t++)//ÿ��48*48�ĺ��ֵ��� ��144���ֽ�
    {   
		if(t<32)temp=tfont48_4[index*2][t];           //ǰ48���ֽ�
		else temp=tfont48_4[index*2+1][t-32]; //��48���ֽ�	                          
	    for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)LCD_Draw_Point1(x,y,color);//��ʵ�ĵ�
			else LCD_Draw_Point1(x,y,BACK_COLOR);   //���հ׵㣨ʹ�ñ���ɫ��
			temp<<=1;
			y++;
			if((y-y0)==32)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }          
}

//����2��������ʾ����
void TEST_FONT4(void)
{
	u8 t;
	u8 x;
	x=30;
	for(t=0;t<4;t++)//6������
	{
		Test_Show_CH4_Font48(x ,240,t,BLUE);
		x+=32;
	}
}

void Test_Show_CH5_Font48(u16 x,u16 y,u8 index,u16 color)
{   			    
	u8 temp,t,t1;
	u16 y0=y;				   
    for(t=0;t<64;t++)//ÿ��48*48�ĺ��ֵ��� ��144���ֽ�
    {   
		if(t<32)temp=tfont48_5[index*2][t];           //ǰ48���ֽ�
		else temp=tfont48_5[index*2+1][t-32]; //��48���ֽ�	                          
	    for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)LCD_Draw_Point1(x,y,color);//��ʵ�ĵ�
			else LCD_Draw_Point1(x,y,BACK_COLOR);   //���հ׵㣨ʹ�ñ���ɫ��
			temp<<=1;
			y++;
			if((y-y0)==32)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }          
}

//����2��������ʾ����
void TEST_FONT5(void)
{
	u8 t;
	u8 x;
	x=30;
	for(t=0;t<4;t++)//6������
	{
		Test_Show_CH5_Font48(x ,310,t,BLUE);
		x+=32;
	}
}


void Test_Show_CH6_Font48(u16 x,u16 y,u8 index,u16 color)
{   			    
	u8 temp,t,t1;
	u16 y0=y;				   
    for(t=0;t<64;t++)//ÿ��48*48�ĺ��ֵ��� ��144���ֽ�
    {   
		if(t<32)temp=tfont48_6[index*2][t];           //ǰ48���ֽ�
		else temp=tfont48_6[index*2+1][t-32]; //��48���ֽ�	                          
	    for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)LCD_Draw_Point1(x,y,color);//��ʵ�ĵ�
			else LCD_Draw_Point1(x,y,BACK_COLOR);   //���հ׵㣨ʹ�ñ���ɫ��
			temp<<=1;
			y++;
			if((y-y0)==32)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }          
}

//����2��������ʾ����
void TEST_FONT6(void)
{
	u8 t;
	u8 x;
	x=30;
	for(t=0;t<5;t++)//6������
	{
		Test_Show_CH6_Font48(x ,380,t,BLUE);
		x+=32;
	}
}


