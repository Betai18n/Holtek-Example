#include "ht32f175x_275x.h"
#include "ht32f175x_275x_board.h"
#include "24bitAD.h"
#include "sys.h" 
#include "delay.h"

//#define ADCPort       P1OUT    //P3.0 CLK  P3.1 DO
//#define ADCIN         P1IN


unsigned char Data[8]={'0','0','0','0','.','0','g','\0'};
unsigned char Data1[8]={'0','0','0','0','0','0','0','\0'};
volatile long se;
volatile long se_last;
unsigned long ad_se;
unsigned long ad_selast;
float ad_data;
float ad_datalast;
unsigned long def;
unsigned long ad_c;
unsigned long ad_temp;
float ad_float;


unsigned long ReadCount(void)
{   
  unsigned long Count;   
  unsigned char i;   
  //ADSK=0;
  HX711_SCK = 0;
  Count=0;
  while(HX711_DOUT==1)
	{
		/*outtime++;
		if(outtime==20000)
		{
				outtime=0;
				break;
		}*/
	}
	{
		for (i=0;i<24;i++)
		{     
			//ADSK=1;
			HX711_SCK = 1;
			Count=Count<<1;
			//ADSK=0;
			HX711_SCK = 0;
			if(HX711_DOUT==1) 
				Count++;   
		}    
		//ADSK=1;
		HX711_SCK = 1;
		Count=Count^0x800000;
		//Count=Count>>8;
		//ADSK=0;  
		HX711_SCK = 0;
		/* if((Count & 0x800000) == 0x800000)
					 {
									 Count = ~(Count - 1);
					 }*/
		
	}
	return(Count); 
}

void initCovAD(void)
{
      do
      {
          ad_datalast=ad_data;
          ad_data = (ReadCount()*0.15)+ad_datalast*0.85;
      }
      while(ad_data!=ad_datalast);
      def=(unsigned long)(ad_data+3);
}

void initAD(void)
{
	CKCU_APBPerip0ClockConfig(CKCU_APBEN0_PE | CKCU_APBEN0_AFIO, ENABLE);//ʹ��APB0��Χʱ��
	
	AFIO_GPEConfig(AFIO_PIN_5|AFIO_PIN_6,AFIO_MODE_DEFAULT);//����GPIOA���Ÿ���ģʽ
	
	GPIO_DriveConfig(GPIOE, GPIO_PIN_5, GPIO_DV_8MA);//����������������
  GPIO_PullResistorConfig(GPIOE, GPIO_PIN_5, GPIO_PR_DISABLE);//���ø���ģʽ
  GPIO_DirectionConfig(GPIOE, GPIO_PIN_5,GPIO_DIR_OUT);//����IO����
	//GPIO_SetOutBits(GPIOB,GPIO_PIN_7);//�ø�
	
	GPIO_DriveConfig(GPIOE, GPIO_PIN_6, GPIO_DV_8MA);//����������������
  GPIO_PullResistorConfig(GPIOE, GPIO_PIN_6, GPIO_PR_DISABLE);//���ø���ģʽ
  GPIO_DirectionConfig(GPIOE, GPIO_PIN_6,GPIO_DIR_IN);//����IO����
	GPIO_InputConfig(GPIOE,GPIO_PIN_6,ENABLE);
}

void CovAD(void)
{
			
      ad_datalast=ad_data;//��¼��һ������
      ad_data = (ReadCount()*0.02)+ad_datalast*0.98;//�Ա������ݽ��л����˲�
      ad_c=(unsigned long)ad_data;
			se_last=se;
	/*
			se_last=se;
      se=(ReadCount()*0.1)+se_last*0.9;      */
	
      
			if(def<ad_c)
      {
        //def=ad_c;
        se=9999;//��ֵ���ʱ������������ʾ
        //def++;//���Խ����Զ�������δ����Ƿ���ȷ��
      }
      else
      {
          ad_temp=(def-ad_c);//����ֵ��������ת��
					ad_float=ad_temp*1.2427*0.001-6.7856;
          //ad_float=(0.118*ad_temp-1.1516); //Need to fix!!
          //ad_float+=4;   
          //se_last=se;//��¼��һ������
          se=(long)ad_float;
      }
			if(se>9999)
			{
					se=9999;
			}
      {
          Data[0]=se/1000+48;
          Data[1]=se%1000/100+48;
          Data[2]=se%1000%100/10+48;
          Data[3]=se%1000%100%10+48;
          Data[4]='.';
          Data[5]=(int)((ad_float-se)*10)+48;//С������
          Data[6]='g';
          Data[7]='\0';
      }
			{
          Data1[0]=ad_c/1000000+48;
          Data1[1]=ad_c%1000000/100000+48;
          Data1[2]=ad_c%1000000%100000/10000+48;
          Data1[3]=ad_c%1000000%100000%10000/1000+48;
          Data1[4]=ad_c%1000000%100000%10000%1000/100+48;
          Data1[5]=ad_c%1000000%100000%10000%1000%100/10+48;
          Data1[6]=ad_c%1000000%100000%10000%1000%100%10+48;
          Data1[7]='\0';
      }
}
