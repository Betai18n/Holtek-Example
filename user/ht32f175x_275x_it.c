/*********************************************************************************************************//**
 * @file    project_template/IP/Example/ht32f175x_275x_it.c
 * @version V1.0
 * @date    09/08/2011
 * @brief   This file provides all interrupt service routine.
 *************************************************************************************************************
 *
 * <h2><center>Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f175x_275x_it.h"
#include "ht32f175x_275x.h"
#include "ht32f175x_275x_board.h"
#include "usart.h"
#include "timer.h"
#include "touch.h"
#include "main.h"
#include "led.h"
#include "disp.h"

u16 rxtemp,outdata;
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
/* Private functions ---------------------------------------------------------------------------------------*/

/*********************************************************************************************************//**
 * @brief   This function handles NMI exception.
 * @retval  None
 ************************************************************************************************************/
void NMI_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles Hard Fault exception.
 * @retval  None
 ************************************************************************************************************/
void HardFault_Handler(void)
{
  while (1);
}

/*********************************************************************************************************//**
 * @brief   This function handles Memory Manage exception.
 * @retval  None
 ************************************************************************************************************/
void MemManage_Handler(void)
{
  while (1);
}

/*********************************************************************************************************//**
 * @brief   This function handles Bus Fault exception.
 * @retval  None
 ************************************************************************************************************/
void BusFault_Handler(void)
{
  while (1);
}

/*********************************************************************************************************//**
 * @brief   This function handles Usage Fault exception.
 * @retval  None
 ************************************************************************************************************/
void UsageFault_Handler(void)
{
  while (1);
}

/*********************************************************************************************************//**
 * @brief   This function handles SVCall exception.
 * @retval  None
 ************************************************************************************************************/
void SVC_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles Debug Monitor exception.
 * @retval  None
 ************************************************************************************************************/
void DebugMon_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles PendSVC exception.
 * @retval  None
 ************************************************************************************************************/
void PendSV_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles SysTick Handler.
 * @retval  None
 ************************************************************************************************************/
void SysTick_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles Clock Ready interrupt.
 * @retval  None
 ************************************************************************************************************/
void CKRDY_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles Low Voltage Detection interrupt.
 * @retval  None
 ************************************************************************************************************/
void LVD_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles Brown Out Detection interrupt.
 * @retval  None
 ************************************************************************************************************/
void BOD_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles WDT interrupt.
 * @retval  None
 ************************************************************************************************************/
void WDT_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles RTC interrupt.
 * @retval  None
 ************************************************************************************************************/
/*void RTC_IRQHandler(void)
{
	
}*/

/*********************************************************************************************************//**
 * @brief   This function handles Flash interrupt.
 * @retval  None
 ************************************************************************************************************/
void FLASH_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles Event Wake Up interrupt.
 * @retval  None
 ************************************************************************************************************/
void EVWUP_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles WAKEUP pin interrupt.
 * @retval  None
 ************************************************************************************************************/
void LPWUP_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles EXTI0 interrupt.
 * @retval  None
 ************************************************************************************************************/
void EXTI0_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles EXTI1 interrupt.
 * @retval  None
 ************************************************************************************************************/
void EXTI1_IRQHandler(void)
{
	//EXTI1_ISR();
}

/*********************************************************************************************************//**
 * @brief   This function handles EXTI2 interrupt.
 * @retval  None
 ************************************************************************************************************/
void EXTI2_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles EXTI3 interrupt.
 * @retval  None
 ************************************************************************************************************/
void EXTI3_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles EXTI4 interrupt.
 * @retval  None
 ************************************************************************************************************/
void EXTI4_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles EXTI5 interrupt.
 * @retval  None
 ************************************************************************************************************/
void EXTI5_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles EXTI6 interrupt.
 * @retval  None
 ************************************************************************************************************/
void EXTI6_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles EXTI7 interrupt.
 * @retval  None
 ************************************************************************************************************/
void EXTI7_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles EXTI8 interrupt.
 * @retval  None
 ************************************************************************************************************/
void EXTI8_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles EXTI9 interrupt.
 * @retval  None
 ************************************************************************************************************/
void EXTI9_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles EXTI10 interrupt.
 * @retval  None
 ************************************************************************************************************/
void EXTI10_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles EXTI11 interrupt.
 * @retval  None
 ************************************************************************************************************/
void EXTI11_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles EXTI12 interrupt.
 * @retval  None
 ************************************************************************************************************/
void EXTI12_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles EXTI13 interrupt.
 * @retval  None
 ************************************************************************************************************/
void EXTI13_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles EXTI14 interrupt.
 * @retval  None
 ************************************************************************************************************/
void EXTI14_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles EXTI15 interrupt.
 * @retval  None
 ************************************************************************************************************/
void EXTI15_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles Comparator interrupt.
 * @retval  None
 ************************************************************************************************************/
void COMP_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles ADC interrupt.
 * @retval  None
 ************************************************************************************************************/
void ADC_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles MCTM BRK interrupt.
 * @retval  None
 ************************************************************************************************************/
void MCTMBRK_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles MCTM UP interrupt.
 * @retval  None
 ************************************************************************************************************/
void MCTMUP_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles MCTM TR interrupt.
 * @retval  None
 ************************************************************************************************************/
void MCTMTR_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles MCTM CC interrupt.
 * @retval  None
 ************************************************************************************************************/
void MCTMCC_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles General Purpose Timer 0 interrupt.
 * @retval  None
 ************************************************************************************************************/
void GPTM0_IRQHandler(void)
{
	GPTM0_ISR();
}

/*********************************************************************************************************//**
 * @brief   This function handles General Purpose Timer 1 interrupt.
 * @retval  None
 ************************************************************************************************************/
void GPTM1_IRQHandler(void)
{
	GPTM1_ISR();
}

/*********************************************************************************************************//**
 * @brief   This function handles Basic Function Timer 0 interrupt.
 * @retval  None
 ************************************************************************************************************/
void BFTM0_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles Basic Function Timer 1 interrupt.
 * @retval  None
 ************************************************************************************************************/
void BFTM1_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles I2C0 interrupt.
 * @retval  None
 ************************************************************************************************************/
void I2C0_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles I2C1 interrupt.
 * @retval  None
 ************************************************************************************************************/
void I2C1_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles SPI0 interrupt.
 * @retval  None
 ************************************************************************************************************/
void SPI0_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles SPI1 interrupt.
 * @retval  None
 ************************************************************************************************************/
void SPI1_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles USART0 interrupt.
 * @retval  None
 ************************************************************************************************************/
void USART0_IRQHandler(void)
{
	  u32 i;
  
  /* Tx, move data from buffer to USART FIFO */
  if ( ( (USART0->IIR) & USART_IID_THRE ) == USART_IID_THRE )
  {
    if (IS_BUFFER_EMPTY(UR0TxReadIndex, UR0TxWriteIndex))
    {
      USART_IntConfig(USART0, USART_IER_THREIE, DISABLE);
    }
    else
    {
      for (i = 0; i < 8; i++)
      {
        USART_SendData(USART0, UR0TxBuf[UR0TxReadIndex]);
        UR0TxReadIndex = (UR0TxReadIndex + 1) % USART_BUFSIZE;
		//HT32F_DVB_LEDOff(LED1);
		if (IS_BUFFER_EMPTY(UR0TxReadIndex, UR0TxWriteIndex))
        {
          break;
        }
      }
    }    
  }

  /* Rx, move data from USART FIFO to buffer */
  if ( ( (USART0->IIR) & USART_IID_RDA ) == USART_IID_RDA )
  {
    if (IS_BUFFER_FULL(UR0RxReadIndex, UR0RxWriteIndex))
    {
      /* USART Rx buffer is full */
      return;
    }

    UR0RxBuf[UR0RxWriteIndex] = USART_ReceiveData(USART0);      
    UR0RxWriteIndex = (UR0RxWriteIndex + 1) % USART_BUFSIZE;
	}
}

/*********************************************************************************************************//**
 * @brief   This function handles USART1 interrupt.
 * @retval  None
 ************************************************************************************************************/
void USART1_IRQHandler(void)
{
	  u32 i;
		u8 testtemp;
  /* Tx, move data from buffer to USART FIFO */
  if ( ( (USART1->IIR) & USART_IID_THRE ) == USART_IID_THRE )
  {
    if (IS_BUFFER_EMPTY(UR1TxReadIndex, UR1TxWriteIndex))
    {
      USART_IntConfig(USART1, USART_IER_THREIE, DISABLE);
    }
    else
    {
      for (i = 0; i < 20; i++)
      {
        USART_SendData(USART1, UR1TxBuf[UR1TxReadIndex]);
        UR1TxReadIndex = (UR1TxReadIndex + 1) % USART_BUFSIZE;
				//HT32F_DVB_LEDOff(LED2);
        if (IS_BUFFER_EMPTY(UR1TxReadIndex, UR1TxWriteIndex))
        {
          break;
        }
      }
			USART_IntConfig(USART1, USART_IER_THREIE, DISABLE);
    }    
  }

  /* Rx, move data from USART FIFO to buffer */
  if ( ( (USART1->IIR) & USART_IID_RDA ) == USART_IID_RDA )
  {
    if (IS_BUFFER_FULL(UR1RxReadIndex, UR1RxWriteIndex))
    {
      /* USART Rx buffer is full */
      return;
    }
		//LED3=!LED3;
		rxtemp=USART_ReceiveData(USART1);
	switch(rxtemp)
  {
		case 98 : 
			{
				UR1RxWriteIndex=0;
				UR1RxReadIndex=0;
			}
			break;
		case 99 : SaveData();break;
    case 50 : outdata=finaltime;break;
    case 49 : outdata=(table_mbtemp[0]-48)*10+(table_mbtemp[1]-48);break;
    case 48 : outdata=(dN1[0]-48)*10+(dN1[1]-48);break;
  }
	
	//USART1->RBR=(u8)outdata;
    UR1RxBuf[UR1RxWriteIndex] = USART_ReceiveData(USART1);      
    UR1RxWriteIndex = (UR1RxWriteIndex + 1) % USART_BUFSIZE;
		UR1TxReadIndex=0;
		UR1TxWriteIndex=0;
		if((rxtemp!=97)&&(rxtemp!=98)&&(rxtemp!=99)&&(rxtemp!=100)&&(rxtemp!=101)&&(rxtemp!=102)&&(rxtemp!=103))
		{
			config[1]=UR1RxBuf[1];
			config[2]=UR1RxBuf[2];
			//SaveData();
			needwater=(UR1RxBuf[3]-48)*1000+(UR1RxBuf[4]-48)*100+(UR1RxBuf[5]-48)*10+(UR1RxBuf[6]-48);
		}
		else if(rxtemp==97)
		{
			if(count5!=0)
			{
				testtemp=0;
				UR1RxWriteIndex=0;
				UR1RxReadIndex=0;
				UR1TxBuf[0]=48;
				UR1TxBuf[1]=table_mbtemp[0];
				UR1TxBuf[2]=table_mbtemp[1];
				UR1TxBuf[3]=dN1[0];
				UR1TxBuf[4]=dN1[1];
				UR1TxBuf[5]=finaltime;
				UR1TxBuf[6]=startflag+48;
				UR1TxBuf[7]=selecttemp[0];
				UR1TxBuf[8]=selecttemp[1];
				UR1TxBuf[9]=needdata[0];
				UR1TxBuf[10]=needdata[1];
				UR1TxBuf[11]=needdata[2];
				UR1TxBuf[12]=needdata[3];
				UR1TxBuf[13]=config[1];
				UR1TxBuf[14]=config[2];
				UR1TxBuf[15]=fanflag+48;
				//UR1TxWriteIndex=4;
				UR2_TX(testtemp);
			}
		}
		else if(rxtemp==100)
		{
				if(startflag==0)
				{
					if(dispconfig[2]==5)
					{
						dispconfig[0]=1;
						configchanged();
						Display_update3();
						dispconfig[0]=255;
					}
				}
		}
		else if(rxtemp==101)
		{
				if(startflag)
				{
					if(dispconfig[2]==5)
					{
						dispconfig[0]=1;
						configchanged();			
						Display_update3();
						dispconfig[0]=255;
					}
				}
		}
		else if(rxtemp==102)
		{
				if(!fanflag)
				{
					if(dispconfig[2]==5)
					{
						dispconfig[0]=2;
						configchanged();				
						Display_update3();
						dispconfig[0]=255;
					}
				}
		}
		else if(rxtemp==103)
		{
				if(fanflag)
				{
					if(dispconfig[2]==5)
					{
						dispconfig[0]=2;
						configchanged();
						Display_update3();
						dispconfig[0]=255;
					}
					
				}
		}
	}
}

/*********************************************************************************************************//**
 * @brief   This function handles Smart Card interrupt.
 * @retval  None
 ************************************************************************************************************/
void SCI_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles USB interrupt.
 * @retval  None
 ************************************************************************************************************/
void USB_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles PDMA_CH0 interrupt.
 * @retval  None
 ************************************************************************************************************/
void PDMA_CH0_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles PDMA_CH1 interrupt.
 * @retval  None
 ************************************************************************************************************/
void PDMA_CH1_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles PDMA_CH2 interrupt.
 * @retval  None
 ************************************************************************************************************/
void PDMA_CH2_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles PDMA_CH3 interrupt.
 * @retval  None
 ************************************************************************************************************/
void PDMA_CH3_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles PDMA_CH4 interrupt.
 * @retval  None
 ************************************************************************************************************/
void PDMA_CH4_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles PDMA_CH5 interrupt.
 * @retval  None
 ************************************************************************************************************/
void PDMA_CH5_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles PDMA_CH6 interrupt.
 * @retval  None
 ************************************************************************************************************/
void PDMA_CH6_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles PDMA_CH7 interrupt.
 * @retval  None
 ************************************************************************************************************/
void PDMA_CH7_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles PDMA_CH8 interrupt.
 * @retval  None
 ************************************************************************************************************/
void PDMA_CH8_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles PDMA_CH9 interrupt.
 * @retval  None
 ************************************************************************************************************/
void PDMA_CH9_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles PDMA_CH10 interrupt.
 * @retval  None
 ************************************************************************************************************/
void PDMA_CH10_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles PDMA_CH11 interrupt.
 * @retval  None
 ************************************************************************************************************/
void PDMA_CH11_IRQHandler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles CMOS Sensor interrupt.
 * @retval  None
 ************************************************************************************************************/
void CSIF_IRQHandler(void)
{
}


/**
  * @}
  */

/**
  * @}
  */
