/*************************************************** 
  ��Ŀ���ƣ��ǽӴ�ʽ������£�Ҷ���¶ȴ�������

**************************************************/
/*
sbit TN_Data = P1^0; //����TN9�ӿ�
sbit TN_Clk  = P1^2;
sbit TN_ACK  = P1^4;

*/
#include "ht32f175x_275x.h"
#include "ht32f175x_275x_board.h"
#include "TN9.h"
#include "sys.h" 
#include "delay.h"
#include "main.h"


unsigned char ReadData[5];

//==========================================================================
//	C��ʽ��		int TN_ReadData(void);
//	ʵ�ֹ��ܣ�	���������
//==========================================================================	
void TN_ReadData(unsigned char flag)
{
        unsigned char i,j,k;
	unsigned char BitState = 0;					//ÿ�η���֡
        unsigned long outtime;
	outtime=0;
	for(k=0;k<3;k++)
	{
	   	 for(j=0;j<5;j++)			   //ÿ֡5���ֽ�
		 {
		    for(i=0;i<8;i++)
			{
			   while(TN_CLK==1)
				 {
					outtime++;
					if(outtime==4000000)
					{
							outtime=0;
							break;
					}
				 }
			   BitState = TN_Data;
			   ReadData[j]= ReadData[j]<<1;
			   ReadData[j]= ReadData[j]|BitState;
			   while(TN_CLK==0)				 
				 {
					outtime++;
					if(outtime==4000000)
					{
							outtime=0;
							break;
					}
				 }
			}
                    
		 }
      if(ReadData[0]==flag)  k=4;
		 
	}
	TN_ACK = 1;
}

/*****************Ŀ���¶�ֵMBtemp�����ӳ���*************/
void TN_GetData_Target(void)   
{   
    int Temp;   
    Temp=(ReadData[1]<<8)|ReadData[2];   
    Temp = (int)((float)Temp/16 - 273.15);   
    Temp=Temp*100;                               //�¶�ֵ��100���Է������С�������λ    
    Temp=Temp+100;
    table_mbtemp[0]=(Temp/1000);                            
    table_mbtemp[0]=table_mbtemp[0]%10+48;                          
    table_mbtemp[1]=(Temp/100);                             
    table_mbtemp[1]=table_mbtemp[1]%10+48;    //fix
    table_mbtemp[3]=(Temp/10);             
    table_mbtemp[3]=table_mbtemp[3]%10+48;    
    table_mbtemp[4]=(Temp);                                       
    table_mbtemp[4]=table_mbtemp[4]%10+48;
    finalTN9temp=(table_mbtemp[0]-48)*10+(table_mbtemp[1]-48);
}   

void TN_GetData_Surround(void)   
{   
    int Temp;   
    Temp=(ReadData[1]<<8)|ReadData[2];   
    Temp = (int)((float)Temp/16 - 273.15);   
    Temp=Temp*100;                               //�¶�ֵ��100���Է������С�������λ    
    Temp=Temp-100;
    dN1[0]=(Temp/1000);                            
    dN1[0]=dN1[0]%10+48;                          
    dN1[1]=(Temp/100);                             
    dN1[1]=dN1[1]%10+48;    
    dN1[3]=(Temp/10);         
    dN1[3]=dN1[3]%10+48;    
    dN1[4]=(Temp);                                       
    dN1[4]=dN1[4]%10+48;
    //finalsurroundtemp=(dN1[0]-48)*10+(dN1[1]-48);
}   

void TN9init(void)
{
	CKCU_APBPerip0ClockConfig(CKCU_APBEN0_PE |CKCU_APBEN0_AFIO,ENABLE);
	
	AFIO_GPEConfig(AFIO_PIN_0|AFIO_PIN_1|AFIO_PIN_2,AFIO_MODE_DEFAULT);//����GPIOA���Ÿ���ģʽ
	
	GPIO_DriveConfig(GPIOE, (GPIO_PIN_0|GPIO_PIN_1), GPIO_DV_8MA);//����������������
	GPIO_DirectionConfig(GPIOE,(GPIO_PIN_0|GPIO_PIN_1),GPIO_DIR_IN);
	GPIO_PullResistorConfig(GPIOE,(GPIO_PIN_0|GPIO_PIN_1),GPIO_PR_DISABLE);
	GPIO_InputConfig(GPIOE,(GPIO_PIN_0|GPIO_PIN_1),ENABLE);
	
	GPIO_DriveConfig(GPIOE, (GPIO_PIN_2), GPIO_DV_8MA);//����������������
	GPIO_DirectionConfig(GPIOE,(GPIO_PIN_2),GPIO_DIR_OUT);
  GPIO_OpenDrainConfig(GPIOE,GPIO_PIN_2,DISABLE);//�������
	GPIO_WriteOutBits(GPIOE, GPIO_PIN_2,SET);//PB.0 �����
}

void TN9COV(void)
{
			//switch(TN9flag)
			{
				//case 0 : 
					{
					 TN_ACK = 0; 
								 
					 TN_ReadData(0x4c);                //Ŀ���¶ȵĵ�һ���ֽ�Ϊ0x4c    
									
						if((ReadData[0]==0x4c)&&(ReadData[4]==0x0d))         //ÿ֡�����һ���ֽ�Ϊ0x0d    
					 {   
									 //if((ReadData[0]+ReadData[1]+ReadData[2])==ReadData[3])
									TN_GetData_Target();   
					 }
					 TN9flag=1;
					 //break;
				 }
				//case 1 :
					{
					  ReadData[0]=0;
						ReadData[1]=0;
						ReadData[2]=0;
						ReadData[3]=0;
						ReadData[4]=0;
					  TN_ACK = 0; 
								 
					  TN_ReadData(0x66);                //�����¶ȵĵ�һ���ֽ�Ϊ0x66    
									
					  if((ReadData[0]==0x66)&&(ReadData[4]==0x0d))         //ÿ֡�����һ���ֽ�Ϊ0x0d    
					  {   
									 //if((ReadData[0]+ReadData[1]+ReadData[2])==ReadData[3])
									TN_GetData_Surround();   
					  }
					  TN9flag=0;
					 // break;

				 }
	 }
}
