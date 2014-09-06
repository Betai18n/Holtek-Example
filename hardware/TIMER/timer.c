#include "timer.h"
#include "led.h"
#include "main.h"
#include "disp.h"
#include "24bitAD.h"
#include "TN9.h"
#include "rtc.h"
#include "fan.h"
#include "buzzer.h"
#include "usart.h"

//////////////////////////////////////////////////////////////////////////////////	 
////////////////////////////////////////////////////////////////////////////////// 	  
#define TIM_IT_Update  0x100
#define TIM_IT_Trigger  0x400

//ͨ�ö�ʱ���жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//arr��ֵΪ5000ʱ �жϴ������Ϊ500ms

void configchanged(void);//������������
void timermain(void);//��ʱ�����庯��

void Timerx_Init(GPTM_TypeDef* GPTMx,u16 arr,u16 psc)
{
   GPTM_TimeBaseInitTypeDef  GPTM_TimeBaseStructure;
	//NVIC_InitTypeDef NVIC_InitStructure;
	Assert_Param(IS_GPTM(GPTMx));
		if(GPTMx==GPTM0)
	{
		CKCU_APBPerip1ClockConfig(CKCU_APBEN1_GPTM0,ENABLE);
	}
	else if(GPTMx==GPTM1)
	{
		CKCU_APBPerip1ClockConfig(CKCU_APBEN1_GPTM1,ENABLE);
	}
	
	GPTM_DeInit(GPTMx);

	GPTM_TimeBaseStructure.CounterReload = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	GPTM_TimeBaseStructure.Prescaler =(7200-1); //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	GPTM_TimeBaseStructure.PSCReloadTime = GPTM_PSC_RLD_UPDATE;//���¼��������ȴ���һ������//TIM �ж�Դ
	GPTM_TimeBaseStructure.CounterMode = GPTM_CNT_MODE_UP;  //TIM���ϼ���ģʽ
	GPTM_TimeBaseInit(GPTMx, &GPTM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	/* TIM IT enable */
	GPTM_IntConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		GPTMx, //TIMx
		TIM_IT_Update  |  //TIM �ж�Դ
		TIM_IT_Trigger,   //TIM �����ж�Դ 
		ENABLE  //ʹ��
		);
		/* Enable the TIMx global Interrupt */

	if(GPTMx==GPTM0)
	{
		NVIC_SetPriority(GPTM0_IRQn,NVIC_EncodePriority(5,0,3));
		NVIC_EnableIRQ(GPTM0_IRQn);
		GPTM_IntConfig(GPTM0,GPTM_INT_UEV,ENABLE);
	}
	else
	if(GPTMx==GPTM1)
	{
		NVIC_SetPriority(GPTM1_IRQn,NVIC_EncodePriority(5,0,3));
		NVIC_EnableIRQ(GPTM1_IRQn);
		GPTM_IntConfig(GPTM1,GPTM_INT_UEV,ENABLE);
	}		
		/*
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
*/
	GPTM_Cmd(GPTMx, ENABLE);  //ʹ��TIMx����
							 
}

void GPTM0_ISR(void)   //TIM0�ж�
{
	if (GPTM_GetIntStatus(GPTM0, GPTM_INT_UEV) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		GPTM_ClearIntPendingBit(GPTM0, GPTM_INT_UEV  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		/* Pin PD.02 toggling with frequency = 10KHz */
		//GPIO_WriteBit(GPIOD, GPIO_Pin_2, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_2)));
		LED2=!LED2;
			
			/*
		if(dispconfig[2]==5)
			Display_update();
		TN9COV();*/
			
		timermain();
		}
}

void GPTM1_ISR(void)   //TIM1�ж�
{
	if (GPTM_GetIntStatus(GPTM1, GPTM_INT_UEV) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		GPTM_ClearIntPendingBit(GPTM1, GPTM_INT_UEV  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		/* Pin PD.02 toggling with frequency = 10KHz */
		//GPIO_WriteBit(GPIOD, GPIO_Pin_2, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_2)));
		
		//LED3=!LED3;
			if(startflag)
				    if((se>=70)&&((buzzerflag==1)||(buzzerflag==3)))//��������
            {
               //P1OUT ^=BIT5;
								buzzer=!buzzer;
            }
		}
}


void timermain(void)
{
	unsigned int watertemp;
	                    //1 count1 = 5ms 
	unsigned int finalTN9temp1=0;
    count1++;
    count2++;
    count3++;
    count4++;
		count5++;
    if(count1==20)
		{
			count1=0;
			ad_selast=ad_se;
      ad_se=se;
		}
    /*if(count2%5==0)
      if(num==255)
      {
        keyflag=1;
      }*/
    if(count2==10)
    {
        count2=0;
        //configchanged();//����ʶ��
        if(startflag)
        {
            if(finalTN9temp<=30)finalTN9temp1=30;//��ֹtimedata�еĳ�Ա���ָ�ֵ�������
						else finalTN9temp1=finalTN9temp;
            finalselecttemp=(selecttemp[0]-48)*10+(selecttemp[1]-48);
            finaltime=timedata[finalTN9temp1-30][finalselecttemp-30];//���������ʣ��ʱ��
        }
        if(fanflag)
          finaltime=finaltime/2;//���������ȴ���ȣ�ʣ��ʱ�����
				
				{
				if(dispconfig[2]==5)
					Display_update();
				else if (dispconfig[2]==6)
					Display_update1();
				else if(dispconfig[2]==4)
					Display_update2();
				}
				if((timer.hour==0)&&(timer.min==0)&&(timer.sec==0))
					needwater=needdrink[config[1]][config[2]];
        //Display();
        //Display_debug();
    }
    if(count3==30)
    {
        count3=0; 
        count3flag=1;
    }
    if(startflag)//�ж��Ƿ�ʼ���������ˮ��
    {          
      if(fanflag)
      {
          fanon();//����
      }
			else if(!fanflag)
			{
					fanoff();
			}
      {

          if(finaltime>5)//ʣ��ʱ��С��5min���̵���
          {
            //LED0ON;
            //LED1OFF;
          }
          else if(finaltime<=5)//ʣ��ʱ�����5min�������
          {
            //LED1ON;
            //LED0OFF;

          }
      }
      if(count4>=10)
      {
          count4=0;
             switch(waterflag)
             {
                 case 0: //ˮ�������ڱ�����
                   {
                     /*if(ad_se>70)
											 if(ad_selast<ad_se)
                       finalwaterlast=ad_selast;*/
										 if(ad_se>70)
											if(ad_selast==ad_se)
												finalwaterlast=ad_selast;
                     if(ad_se<20)
                       waterflag=1;
                   }
                   break;
                 case 1:  //ˮ�������
                   {
                     if(ad_se>20)
                       waterflag=2;     //The max water=500g    bottle=70g (ideally!!)
                   }                    //Need fix
                   break;
                 case 2:  //����ˮ���ˮ������
                   {
                     if(ad_se>70)
                     {
                       if(ad_se==ad_selast)
                       {
                         if((ad_se>420)&&(ad_se>=finalwaterlast))
                         {
                           finalwater=finalwaterlast; 
                           watertemp=finalwater;
                           needwater=needwater-watertemp;
                           waterflag=0;
                         }
                         else if(ad_se<finalwaterlast)
                         {
                           finalwater=finalwaterlast-ad_se;
                           watertemp=finalwater;
                           needwater=needwater-watertemp;
                           waterflag=0;
                         }
                         
                       }
                     }
                   break;
										}
								}
        }
				//if(count5==100)
				if((count5==100)&&(se>=70))
				{
					count5=0;
					//LED3=!LED3;
					UR1TxReadIndex=0;
					UR1TxWriteIndex=0;
					UR1TxBuf[0]=48;
					UR1TxBuf[1]=table_mbtemp[0];
					UR1TxBuf[2]=table_mbtemp[1];
					UR1TxBuf[3]=dN1[0];
					UR1TxBuf[4]=dN1[1];
					UR1TxBuf[5]=finaltime;
					UR1TxBuf[6]=startflag+48;
					UR1TxBuf[7]=selecttemp[0];
					UR1TxBuf[8]=selecttemp[1];
					UR1TxBuf[9]=127;
					UR1TxBuf[10]=127;
					UR1TxBuf[11]=127;
					UR1TxBuf[12]=127;
					UR1TxBuf[13]=127;
					UR1TxBuf[14]=127;
					UR1TxBuf[15]=127;
					UR2_TX(1);
				}
				if((finalTN9temp>=60)&&(buzzerflag!=0))
					buzzerflag=0;
				if((buzzerflag==0)&&((se>=70))&&(finalTN9temp<=(finalselecttemp+3)))
					buzzerflag=1;
				else if((buzzerflag==2)&&((se>=70))&&(finalTN9temp<=(finalselecttemp-3)))
					buzzerflag=3;
				if((buzzerflag==1)||(buzzerflag==3))
				{
					count6++;
				}
				if(count6==30)
				{
					count6=0;
					if(buzzerflag!=3)
						buzzerflag=2;
					else if(buzzerflag==3)
						buzzerflag=5;
				}
    }
    else if(!startflag)//���û�п���ʣ��ʱ���ʱ������ָʾ�ƶ��ر�
    {
        //LED1OFF;
        //LED0OFF;
    }
		if(count5==100)
			count5=0;
}


/*
      
��    15  11  07  03        ������    ��    null  null
��    14  10  06  02          ��      OK    ��    ��ҳ
��    13  09  05  01        �ط���    ��    null  ����
��    12  08  04  00        ����ˮ  �ط�ˮ  null  ����

*/

void configchanged(void)
{
        unsigned char tempconfig,configtemp1,configtemp2;
        if(dispconfig[2]==0)//������˵�ѡ��ʱ
        {
            switch(dispconfig[0])//�԰�����Ϊ�����ж�
            {
                case 2 : dispconfig[2]=1;break;
                case 3 : dispconfig[2]=2;break;
                case 4 : dispconfig[2]=3;break;
								case 5 : dispconfig[2]=5;SaveData();break;
								case 6 : dispconfig[2]=6;break;
								case 7 : dispconfig[2]=4;			
												timer1.w_year=2014;
												timer1.w_month=5;
												timer1.w_date=10;
												timer1.hour=8;
												timer1.min=59;
												timer1.sec=50;break;
                case 255 : break;
            }
        }
        else if((dispconfig[2]==1)||(dispconfig[2]==2))//��������Ⱥ�ͼ���ѡ��ʱ
        {
            switch(dispconfig[0])//�԰�����Ϊ�����ж�
            {
                   case 1 : 
                  {
                    tempconfig=dispconfig[2];
                    config[tempconfig]=dispconfig[0]-1;
                    dispconfig[2]=0;
                    dispconfig[1]=0;
                    configtemp1=config[1];
                    configtemp2=config[2];
                    needwater=needdrink[configtemp1][configtemp2];
                    selecttemp[0]=tempdata1[configtemp1][configtemp2];
                    selecttemp[1]=tempdata2[configtemp1][configtemp2];
                  }
                  break;
                  case 2 : 
                  {
                    tempconfig=dispconfig[2];
                    config[tempconfig]=dispconfig[0]-1;
                    dispconfig[2]=0;
                    dispconfig[1]=0;
                    configtemp1=config[1];
                    configtemp2=config[2];
                    needwater=needdrink[configtemp1][configtemp2];
                    selecttemp[0]=tempdata1[configtemp1][configtemp2];
                    selecttemp[1]=tempdata2[configtemp1][configtemp2];
                  }
                  break;
                  case 3 : 
                  {
                    tempconfig=dispconfig[2];
                    config[tempconfig]=dispconfig[0]-1;
                    dispconfig[2]=0;
                    dispconfig[1]=0;
                    configtemp1=config[1];
                    configtemp2=config[2];
                    needwater=needdrink[configtemp1][configtemp2];
                    selecttemp[0]=tempdata1[configtemp1][configtemp2];
                    selecttemp[1]=tempdata2[configtemp1][configtemp2];
                  }
                  break;
                  case 4 : 
                  {
                    tempconfig=dispconfig[2];
                    config[tempconfig]=dispconfig[0]-1;
                    dispconfig[2]=0;
                    dispconfig[1]=0;
                    configtemp1=config[1];
                    configtemp2=config[2];
                    needwater=needdrink[configtemp1][configtemp2];
                    selecttemp[0]=tempdata1[configtemp1][configtemp2];
                    selecttemp[1]=tempdata2[configtemp1][configtemp2];
                  }
                  break;
									case 0 : dispconfig[2]=0; break;
                case 255 : break;
            }
        }
        else if(dispconfig[2]==3)//�����������¶��趨
        {

            switch(dispconfig[0])//�԰�����Ϊ�����ж�
            {
                /*
                case 6 : if(dispconfig[1]==1)dispconfig[1]=0;else dispconfig[1]++;break;
                case 9 : if(dispconfig[1]==1)
                          {
                            if(selecttemp[1]==48)
                              selecttemp[1]=57;
                            else selecttemp[1]--;
                          }
                          else if(dispconfig[1]==0)
                          {
                            if(selecttemp[0]==51)
                              selecttemp[0]=57;
                            else selecttemp[0]--;
                          }break;
                case 10 : dispconfig[2]=0;dispconfig[1]=0;break;
                case 11 : if(dispconfig[1]==1)
                          {
                            if(selecttemp[1]==57)
                              selecttemp[1]=48;
                            else selecttemp[1]++;
                          }
                          else if(dispconfig[1]==0)
                          {
                            if(selecttemp[0]==57)
                              selecttemp[0]=51;
                            else selecttemp[0]++;
                          }break;
                case 14 : if(dispconfig[1]==0)dispconfig[1]=1;else dispconfig[1]--;break;*/
								case 0 : dispconfig[2]=0; break;
								case 1 :  {
                            if(selecttemp[0]==57)
                              selecttemp[0]=51;
                            else selecttemp[0]++;
                          }break;
							  case 2 :  {
                            if(selecttemp[0]==51)
                              selecttemp[0]=57;
                            else selecttemp[0]--;
                          }break;
								case 3 :  {
                            if(selecttemp[1]==57)
                              selecttemp[1]=48;
                            else selecttemp[1]++;
                          }break;
								case 5 :  {
                            if(selecttemp[1]==48)
                              selecttemp[1]=57;
                            else selecttemp[1]--;
                          }break;
                case 255 : break;
            }
        }
        else if(dispconfig[2]==4)//����RTC
        {
            switch(dispconfig[0])//�԰�����Ϊ�����ж�
            {
              case 0 : dispconfig[2]=0;dispconfig[1]=0;break;
							case 1 : timer1.w_year++;break;
							case 2 : timer1.w_year--;break;
							case 3 : timer1.w_month++;if(timer1.w_month==13)timer1.w_month=1;break;
							case 4 : timer1.w_month--;if(timer1.w_month==0)timer1.w_month=12;break;
							case 5 : timer1.w_date++;if(timer1.w_date==32)timer1.w_date=1;break;
							case 6 : timer1.w_date--;if(timer1.w_date==0)timer1.w_date=31;break;
							case 7 : timer1.hour++;if(timer1.hour==24)timer1.hour=0;break;
							case 8 : timer1.hour--;if(timer1.hour==255)timer1.hour=23;break;
							case 9 : timer1.min++;if(timer1.min==60)timer1.min=0;break;
							case 10 : timer1.min--;if(timer1.min==255)timer1.min=59;break;
							case 11 : timer1.sec++;if(timer1.sec==60)timer1.sec=0;break;
              case 12 : timer1.sec--;if(timer1.sec==255)timer1.sec=59;break;
							case 13 : RTC_Set(timer1.w_year,timer1.w_month,timer1.w_date,timer1.hour,timer1.min,timer1.sec);break;
							case 255 : break;
            }
        }
        else if(dispconfig[2]==5)//������ҳ2
        {
            switch(dispconfig[0])//�԰�����Ϊ�����ж�
            {
                case 0 : dispconfig[2]=0;dispconfig[1]=0;break;
								case 1 : if(startflag==0)
													{
														startflag=1;
														finalwater=0;
													}
													else if(startflag==1)
													{
														startflag=0;
														finalwater=0;
														waterflag=0;
														finaltime=0;
														buzzerflag=0;
													}
													LED3=!LED3;
													UR1TxReadIndex=0;
													UR1TxWriteIndex=0;
													UR1TxBuf[0]=48;
													UR1TxBuf[1]=table_mbtemp[0];
													UR1TxBuf[2]=table_mbtemp[1];
													UR1TxBuf[3]=dN1[0];
													UR1TxBuf[4]=dN1[1];
													UR1TxBuf[5]=finaltime;
													UR1TxBuf[6]=startflag+48;
													UR1TxBuf[7]=selecttemp[0];
													UR1TxBuf[8]=selecttemp[1];
													UR1TxBuf[9]=127;
													UR1TxBuf[10]=127;
													UR1TxBuf[11]=127;
													UR1TxBuf[12]=127;
													UR1TxBuf[13]=127;
													UR1TxBuf[14]=127;
													UR1TxBuf[15]=fanflag+48;
													UR2_TX(1);
													break;
								case 2 : if(fanflag==0)
													{
														fanflag=1;
														
													}
													else if(fanflag==1)
													{
														fanflag=0;
													}
													UR1TxReadIndex=0;
													UR1TxWriteIndex=0;
													UR1TxBuf[0]=48;
													UR1TxBuf[1]=table_mbtemp[0];
													UR1TxBuf[2]=table_mbtemp[1];
													UR1TxBuf[3]=dN1[0];
													UR1TxBuf[4]=dN1[1];
													UR1TxBuf[5]=finaltime;
													UR1TxBuf[6]=startflag+48;
													UR1TxBuf[7]=selecttemp[0];
													UR1TxBuf[8]=selecttemp[1];
													UR1TxBuf[9]=127;
													UR1TxBuf[10]=127;
													UR1TxBuf[11]=127;
													UR1TxBuf[12]=127;
													UR1TxBuf[13]=127;
													UR1TxBuf[14]=127;
													UR1TxBuf[15]=fanflag+48;
													UR2_TX(1);
													break;
                case 5 : dispconfig[2]=5;break;
								case 6 : dispconfig[2]=5;needwater=needdrink[config[1]][config[2]];break;
                case 255 : break;
            }
        }
        else if(dispconfig[2]==6)//�������У׼
        {
            switch(dispconfig[0])//�԰�����Ϊ�����ж�
            {
                case 0 : dispconfig[2]=0;dispconfig[1]=0;break;
                case 5 : if((def>ad_c))def=ad_c+7;break;//��ʼУ׼
								case 6 : dispconfig[2]=6;
                case 14 : if((def<ad_c))def+=50000;break;//���ݸ�λ
                case 255 : if(def<ad_c)def+=775;break;//�Զ���������bug��
            }
        }             
}







