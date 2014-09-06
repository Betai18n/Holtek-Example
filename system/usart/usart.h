/*********************************************************************************************************//**
 * @file    USART/HyperTerminal_TxRx_Interrupt/usart_int.h
 * @version V1.0
 * @date    09/12/2012
 * @brief   The header file of the USART interrupt functions.
 *************************************************************************************************************
 *
 * <h2><center>Copyright (C) 2012 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __USART_INT_H
#define __USART_INT_H

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f175x_275x.h"

/* Exported types ------------------------------------------------------------------------------------------*/
typedef enum
{
  USART_TX_INT = 1,
  USART_RX_INT = 2,
  USART_ALL_INT = 3
}USART_INT_Mode;

/* Exported constants --------------------------------------------------------------------------------------*/
#define USART_BUFSIZE   128

extern u8 UR0TxBuf[USART_BUFSIZE];
extern u8 UR0RxBuf[USART_BUFSIZE];
extern vu32 UR0TxReadIndex, UR0TxWriteIndex;
extern vu32 UR0RxReadIndex, UR0RxWriteIndex;
extern u8 UR1TxBuf[USART_BUFSIZE];
extern u8 UR1RxBuf[USART_BUFSIZE];
extern vu32 UR1TxReadIndex, UR1TxWriteIndex;
extern vu32 UR1RxReadIndex, UR1RxWriteIndex;

/* Exported macro ------------------------------------------------------------------------------------------*/
#define IS_BUFFER_FULL(ridx, widx)		((widx + 1) % USART_BUFSIZE == ridx)
#define IS_BUFFER_EMPTY(ridx, widx)   (ridx == widx)

/* Exported functions --------------------------------------------------------------------------------------*/
void USART_Interrupt_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStructure, USART_INT_Mode Mode);
void UR0_TX(void);
void UR1_TX(u8 out);
void UR2_TX(u8 out);
void UR0_RX(void);
void UR1_RX(void);
void usart_init(USART_TypeDef* USARTx,vu32 baud);

#endif /* __USART_INT_H ------------------------------------------------------------------------------------*/
