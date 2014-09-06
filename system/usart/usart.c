#include "sys.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 
//串口1初始化		   
//********************************************************************************
//修改说明 
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
////////////////////////////////////////////////////////////////////////////////// 	  
#define USART_TIMEOUT_ON          ((u32)0x00000080)


  USART_InitTypeDef USART_InitStructure;
  
  u8 temp[64] = {0}, temp1[64] = {0};

/* USART0 definitions */
u8 UR0TxBuf[USART_BUFSIZE];
u8 UR0RxBuf[USART_BUFSIZE];
vu32 UR0TxReadIndex = 0, UR0TxWriteIndex = 0;
vu32 UR0RxReadIndex = 0, UR0RxWriteIndex = 0;

/* USART1 definitions */
u8 UR1TxBuf[USART_BUFSIZE];
u8 UR1RxBuf[USART_BUFSIZE];
vu32 UR1TxReadIndex = 0, UR1TxWriteIndex = 0;
vu32 UR1RxReadIndex = 0, UR1RxWriteIndex = 0;

void usart_init(USART_TypeDef* USARTx,vu32 baud)
{
  /* Enable peripheral clock of AFIO, USART0, USART1 */
	Assert_Param(IS_USART(USARTx));
	
  if(USARTx==USART0)
  CKCU_APBPerip0ClockConfig(CKCU_APBEN0_AFIO | CKCU_APBEN0_USART0 , ENABLE);
  else if(USARTx==USART1)
  CKCU_APBPerip0ClockConfig(CKCU_APBEN0_AFIO | CKCU_APBEN0_USART1 , ENABLE);
  /* 
		USARTx configured as follow:
			- BaudRate =  baud  
			- Word Length = 8 Bits
			- One Stop Bit
			- None parity bit
  */
  
  /* Config AFIO mode as USART0_Rx and USART0_Tx function. */
  if(USARTx==USART0)
  AFIO_GPCConfig(AFIO_PIN_8 | AFIO_PIN_10, AFIO_MODE_3);
     
  /* Config AFIO mode as USART1_Rx and USART1_Tx function. */
  else if(USARTx==USART1)
  AFIO_GPCConfig(AFIO_PIN_4 | AFIO_PIN_5, AFIO_MODE_1);
      
  /* Config AFIO mode as USARTx function */
  //if((USARTx==USART0)||(USARTx==USART1))
  {
		USART_InitStructure.USART_BaudRate = baud;
		USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B ;
		USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
		USART_InitStructure.USART_Parity = USART_PARITY_NO ;
		USART_InitStructure.USART_Mode = USART_MODE_NORMAL;
  }
 	
  /* Configure USART0 & USART1 interrupt */
  /*if(USARTx==USART0)
  USART_Interrupt_Init(USART0, &USART_InitStructure, USART_ALL_INT);*/
  //else if(USARTx==USART1)
  USART_Interrupt_Init(USART1, &USART_InitStructure, USART_ALL_INT);
}

void USART_Interrupt_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStructure, USART_INT_Mode Mode)
{
  /* Configures USARTx */
  USART_Init(USARTx, USART_InitStructure);  
  USART_FIFOReset(USARTx, USART_FIFO_TX | USART_FIFO_RX);
  
  if (Mode == USART_TX_INT)
  {
    /* Set TX FIFO Level, empty in FIFO */
	USART_TFITLConfig(USARTx, USART_TFITL_00);          
    USART_TxCmd(USARTx, ENABLE);
  }
  else if (Mode == USART_RX_INT)
  { 
	/* Set RX FIFO Level, 1 byte in FIFO */
    USART_RFITLConfig(USARTx, USART_RFITL_01);
	/* Enable RX FIFO Interrupt */         
    USART_IntConfig(USARTx, USART_IER_RDAIE, ENABLE);
	/* Set RX Timeout */   
    USARTx->TPR = USART_TIMEOUT_ON | 40;               
    USART_RxCmd(USARTx, ENABLE);
  }
  else if (Mode == USART_ALL_INT)										
  {
    USART_TFITLConfig(USARTx, USART_TFITL_00);
    USART_TxCmd(USARTx, ENABLE);    
    USART_RFITLConfig(USARTx, USART_RFITL_01);
		USART_IntConfig(USARTx, USART_IER_ALL, ENABLE);
    USARTx->TPR = USART_TIMEOUT_ON | 40;
    USART_RxCmd(USARTx, ENABLE);
  }
	
	if (USARTx == USART0)
	{
		NVIC_SetPriority(USART0_IRQn,NVIC_EncodePriority(5,3,3));
		NVIC_EnableIRQ(USART0_IRQn);
	}
	else if (USARTx == USART1)
	{
		NVIC_SetPriority(USART1_IRQn,NVIC_EncodePriority(5,3,3));
		NVIC_EnableIRQ(USART1_IRQn);
	}
}

void UR0_TX(void)
{
	int i;//i控制发送的字节数
	for (i = 0; i < 1; i++)
	{
		if (!IS_BUFFER_FULL(UR0TxReadIndex, UR0TxWriteIndex))
		{
			/* 0x30 = ASCII "0" */
			UR0TxBuf[UR0TxWriteIndex] = 0x30;
			UR0TxWriteIndex = (UR0TxWriteIndex + 1) % USART_BUFSIZE;
		}
	}
	USART_IntConfig(USART0, USART_IER_THREIE, ENABLE);
}

void UR1_TX(u8 out)
{
	int i;
	for (i = 0; i < 1; i++)
	{
		if (!IS_BUFFER_FULL(UR1TxReadIndex, UR1TxWriteIndex))
		{
			/* 0x41 = ASCII "A" */
			UR1TxBuf[UR1TxWriteIndex] = out;
			UR1TxWriteIndex = (UR1TxWriteIndex + 1) % USART_BUFSIZE;
		}
	}
	USART_IntConfig(USART1, USART_IER_THREIE, ENABLE);
}

void UR2_TX(u8 out)
{
	int i;
	for (i = 0; i < 16; i++)
	{
		if (!IS_BUFFER_FULL(UR1TxReadIndex, UR1TxWriteIndex))
		{
			/* 0x41 = ASCII "A" */
			//UR1TxBuf[UR1TxWriteIndex] = out;
			UR1TxWriteIndex = (UR1TxWriteIndex + 1) % USART_BUFSIZE;
		}
	}
	USART_IntConfig(USART1, USART_IER_THREIE, ENABLE);
}

void UR0_RX(void)
{
	int j=0;
	if (!IS_BUFFER_EMPTY(UR0RxReadIndex, UR0RxWriteIndex))
	{
		temp[j++] = UR0RxBuf[UR0RxReadIndex];
		UR0RxReadIndex = (UR0RxReadIndex + 1) % USART_BUFSIZE;
		if (j == 60)
		{
			j = 0;
		}
	}
}

void UR1_RX(void)
{
	int k=0;
	if (!IS_BUFFER_EMPTY(UR1RxReadIndex, UR1RxWriteIndex))
	{
		temp1[k++] = UR1RxBuf[UR1RxReadIndex];
		UR1RxReadIndex = (UR1RxReadIndex + 1) % USART_BUFSIZE;
		if (k == 60)
		{
			k = 0;
		}
	}
}
