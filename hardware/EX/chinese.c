#include "chinese.h"
#include "chfont.h"
#include "lcd.h"	   

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板——扩展实验
//自定义汉字显示  代码			   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/7/6
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  
			    
					
#define MOVIE_XSIZE	100 
#define MOVIE_YSIZE 40  
#define FRAME_SIZE MOVIE_XSIZE*MOVIE_YSIZE/8  

//在LCD上的（x，y）处画点
//color：点的颜色
void LCD_Draw_Point1(u16 x,u16 y,u16 color)
{
	u16 temp;
	temp=POINT_COLOR;
	POINT_COLOR=color;
    LCD_DrawPoint(x,y);
	POINT_COLOR=temp;
}

//在指定位置 显示1个16*16的汉字
//(x,y):汉字显示的位置
//index:tfont数组里面的第几个汉字
//color:这个汉字的颜色
void Test_Show_CH_Font16(u16 x,u16 y,u8 index,u16 color)
{   			    
	u8 temp,t,t1;
	u16 y0=y;				   
    for(t=0;t<32;t++)//每个16*16的汉字点阵 有32个字节
    {   
		if(t<16)temp=tfont16[index*2][t];      //前16个字节
		else temp=tfont16[index*2+1][t-16];    //后16个字节	                          
        for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)LCD_Draw_Point1(x,y,color);//画实心点
			else LCD_Draw_Point1(x,y,BACK_COLOR);   //画空白点（使用背景色）
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
    for(t=0;t<72;t++)//每个24*24的汉字点阵 有72个字节
    {   
		if(t<24)temp=tfont24[index*3][t];           //前24个字节
		else if(t<48)temp=tfont24[index*3+1][t-24]; //中24个字节	                          
        else temp=tfont24[index*3+2][t-48];         //后24个字节
	    for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)LCD_Draw_Point1(x,y,color);//画实心点
			else LCD_Draw_Point1(x,y,BACK_COLOR);   //画空白点（使用背景色）
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
    for(t=0;t<64;t++)//每个48*48的汉字点阵 有144个字节
    {   
		if(t<32)temp=tfont48_1[index*2][t];           //前24个字节
		else temp=tfont48_1[index*2+1][t-32]; //中24个字节	                                             
	    for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)LCD_Draw_Point1(x,y,color);//画实心点
			else LCD_Draw_Point1(x,y,BACK_COLOR);   //画空白点（使用背景色）
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

//测试2个汉字显示函数
void TEST_FONT1(void)
{
	u8 t;
	u8 x;
	x=30;
	for(t=0;t<6;t++)//6个汉字
	{
		Test_Show_CH1_Font48(x ,30,t,BLUE);
		x+=32;
	}
}

void Test_Show_CH2_Font48(u16 x,u16 y,u8 index,u16 color)
{   			    
	u8 temp,t,t1;
	u16 y0=y;				   
    for(t=0;t<64;t++)//每个48*48的汉字点阵 有144个字节
    {   
		if(t<32)temp=tfont48_2[index*2][t];           //前48个字节
		else  temp=tfont48_2[index*2+1][t-32]; //中48个字节	                          
	    for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)LCD_Draw_Point1(x,y,color);//画实心点
			else LCD_Draw_Point1(x,y,BACK_COLOR);   //画空白点（使用背景色）
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

//测试2个汉字显示函数
void TEST_FONT2(void)
{
	u8 t;
	u8 x;
	x=30;
	for(t=0;t<5;t++)//6个汉字
	{
		Test_Show_CH2_Font48(x ,100,t,BLUE);
		x+=32;
	}
}

void Test_Show_CH3_Font48(u16 x,u16 y,u8 index,u16 color)
{   			    
	u8 temp,t,t1;
	u16 y0=y;				   
    for(t=0;t<64;t++)//每个48*48的汉字点阵 有144个字节
    {   
		if(t<32)temp=tfont48_3[index*2][t];           //前48个字节
		else temp=tfont48_3[index*2+1][t-32]; //中48个字节	                          
	    for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)LCD_Draw_Point1(x,y,color);//画实心点
			else LCD_Draw_Point1(x,y,BACK_COLOR);   //画空白点（使用背景色）
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

//测试2个汉字显示函数
void TEST_FONT3(void)
{
	u8 t;
	u8 x;
	x=30;
	for(t=0;t<8;t++)//6个汉字
	{
		Test_Show_CH3_Font48(x ,170,t,BLUE);
		x+=32;
	}
}

void Test_Show_CH4_Font48(u16 x,u16 y,u8 index,u16 color)
{   			    
	u8 temp,t,t1;
	u16 y0=y;				   
    for(t=0;t<64;t++)//每个48*48的汉字点阵 有144个字节
    {   
		if(t<32)temp=tfont48_4[index*2][t];           //前48个字节
		else temp=tfont48_4[index*2+1][t-32]; //中48个字节	                          
	    for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)LCD_Draw_Point1(x,y,color);//画实心点
			else LCD_Draw_Point1(x,y,BACK_COLOR);   //画空白点（使用背景色）
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

//测试2个汉字显示函数
void TEST_FONT4(void)
{
	u8 t;
	u8 x;
	x=30;
	for(t=0;t<4;t++)//6个汉字
	{
		Test_Show_CH4_Font48(x ,240,t,BLUE);
		x+=32;
	}
}

void Test_Show_CH5_Font48(u16 x,u16 y,u8 index,u16 color)
{   			    
	u8 temp,t,t1;
	u16 y0=y;				   
    for(t=0;t<64;t++)//每个48*48的汉字点阵 有144个字节
    {   
		if(t<32)temp=tfont48_5[index*2][t];           //前48个字节
		else temp=tfont48_5[index*2+1][t-32]; //中48个字节	                          
	    for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)LCD_Draw_Point1(x,y,color);//画实心点
			else LCD_Draw_Point1(x,y,BACK_COLOR);   //画空白点（使用背景色）
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

//测试2个汉字显示函数
void TEST_FONT5(void)
{
	u8 t;
	u8 x;
	x=30;
	for(t=0;t<4;t++)//6个汉字
	{
		Test_Show_CH5_Font48(x ,310,t,BLUE);
		x+=32;
	}
}


void Test_Show_CH6_Font48(u16 x,u16 y,u8 index,u16 color)
{   			    
	u8 temp,t,t1;
	u16 y0=y;				   
    for(t=0;t<64;t++)//每个48*48的汉字点阵 有144个字节
    {   
		if(t<32)temp=tfont48_6[index*2][t];           //前48个字节
		else temp=tfont48_6[index*2+1][t-32]; //中48个字节	                          
	    for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)LCD_Draw_Point1(x,y,color);//画实心点
			else LCD_Draw_Point1(x,y,BACK_COLOR);   //画空白点（使用背景色）
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

//测试2个汉字显示函数
void TEST_FONT6(void)
{
	u8 t;
	u8 x;
	x=30;
	for(t=0;t<5;t++)//6个汉字
	{
		Test_Show_CH6_Font48(x ,380,t,BLUE);
		x+=32;
	}
}


