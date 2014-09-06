/*********************************************************************************************************//**
 * @file    ht32f175x_275x_pdma.h
 * @version V1.0
 * @date    09/08/2011
 * @brief   The header file of the PDMA library.
 *************************************************************************************************************
 *
 * <h2><center>Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F175x_275x_PDMA_H
#define __HT32F175x_275x_PDMA_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f175x_275x.h"

/** @addtogroup HT32F175x_275x_Peripheral_Driver
  * @{
  */

/** @addtogroup PDMA
  * @{
  */

/* Exported types ------------------------------------------------------------------------------------------*/

/** @defgroup PDMA_Exported_Types PDMA exported types
  * @{
  */

/**
 * @brief Definition of PDMA channel Init Structure
 */
typedef struct
{
  u32 PDMACH_SrcAddr;         /*!< source address                                                           */
  u32 PDMACH_DstAddr;         /*!< destination address                                                      */
  u32 PDMACH_BlkCnt;          /*!< number of blocks for a PDMA transfer (1 ~ 65,535)                        */
  u32 PDMACH_BlkLen;          /*!< number of data for a block (1 ~ 65,535)                                  */
  u32 PDMACH_DataSize;        /*!< number of bits for a data (8-bit/16-bit/32-bit)                          */
  u32 PDMACH_Priority;        /*!< software priority for a PDMA transfer (L/M/H/VH)                         */
  u32 PDMACH_AdrMod;          /*!< address mode (LIN_INC/LIN_DEC/CIR_INC/CIR_DEC/FIX/AUTO_RELOAD)           */
} PDMACH_InitTypeDef;

/**
  * @}
  */  /* End of PDMA_Exported_Types */

/* Exported constants --------------------------------------------------------------------------------------*/

/** @defgroup PDMA_Exported_Constants PDMA exported constants
  * @{
  */
#define L_PRIO                    (0)                           /*!< low priority                           */
#define M_PRIO                    (1UL << 8)                    /*!< medium priority                        */
#define H_PRIO                    (2UL << 8)                    /*!< high priority                          */
#define VH_PRIO                   (3UL << 8)                    /*!< very high priority                     */

#define IS_PDMA_PRIO(PRIO)        ((PRIO >> 8) < 4)             /*!< check channel priority parameter       */

#define AUTO_RELOAD               (1UL << 11)                   /*!< enable auto reload                     */
#define ADR_FIX                   (1UL << 10)                   /*!< enable address fix                     */

#define SRC_ADR_LIN_INC           (0)                           /*!< source address linear increment        */
#define SRC_ADR_LIN_DEC           (1UL << 6)                    /*!< source address linear decrement        */
#define SRC_ADR_CIR_INC           (2UL << 6)                    /*!< source address circular increment      */
#define SRC_ADR_CIR_DEC           (3UL << 6)                    /*!< source address circular decrement      */
#define SRC_ADR_FIX               (ADR_FIX | SRC_ADR_CIR_INC)   /*!< source address fix                     */

#define DST_ADR_LIN_INC           (0)                           /*!< destination address linear increment   */
#define DST_ADR_LIN_DEC           (1UL << 4)                    /*!< destination address linear decrement   */
#define DST_ADR_CIR_INC           (2UL << 4)                    /*!< destination address circular increment */
#define DST_ADR_CIR_DEC           (3UL << 4)                    /*!< destination address circular decrement */
#define DST_ADR_FIX               (ADR_FIX | DST_ADR_CIR_INC)   /*!< destination address fix                */

#define IS_PDMA_ADR_MOD(MOD)      ((MOD & 0xFFFFF30F) == 0)     /*!< check address mode parameters          */

#define WIDTH_8BIT                (0)                           /*!< 8-bit transfer width                   */
#define WIDTH_16BIT               (1UL << 2)                    /*!< 16-bit transfer width                  */
#define WIDTH_32BIT               (2UL << 2)                    /*!< 32-bit transfer width                  */

#define IS_PDMA_WIDTH(WIDTH)      ((WIDTH >> 2) < 3)            /*!< check transfer width parameter         */

#define PDMA_CH0                  (0)                           /*!< channel 0 number                       */
#define PDMA_CH1                  (1UL)                         /*!< channel 1 number                       */
#define PDMA_CH2                  (2UL)                         /*!< channel 2 number                       */
#define PDMA_CH3                  (3UL)                         /*!< channel 3 number                       */
#define PDMA_CH4                  (4UL)                         /*!< channel 4 number                       */
#define PDMA_CH5                  (5UL)                         /*!< channel 5 number                       */
#define PDMA_CH6                  (6UL)                         /*!< channel 6 number                       */
#define PDMA_CH7                  (7UL)                         /*!< channel 7 number                       */
#define PDMA_CH8                  (8UL)                         /*!< channel 8 number                       */
#define PDMA_CH9                  (9UL)                         /*!< channel 9 number                       */
#define PDMA_CH10                 (10UL)                        /*!< channel 10 number                      */
#define PDMA_CH11                 (11UL)                        /*!< channel 11 number                      */

#define IS_PDMA_CH(CH)            (CH < 12)                     /*!< check channel number parameter         */

#define PDMA_CSIF                 PDMA_CH0                      /*!< CSIF PDMA channel number               */

#define PDMA_ADC                  PDMA_CH1                      /*!< ADC PDMA channel number                */

#define PDMA_SCI_TX               PDMA_CH10                     /*!< SCI_TX PDMA channel number             */
#define PDMA_SCI_RX               PDMA_CH11                     /*!< SCI_RX PDMA channel number             */

#define PDMA_I2C0_TX              PDMA_CH10                     /*!< I2C0_TX PDMA channel number            */
#define PDMA_I2C0_RX              PDMA_CH11                     /*!< I2C0_RX PDMA channel number            */
#define PDMA_I2C1_TX              PDMA_CH0                      /*!< I2C1_TX PDMA channel number            */
#define PDMA_I2C1_RX              PDMA_CH1                      /*!< I2C1_RX PDMA channel number            */

#define PDMA_SPI0_TX              PDMA_CH2                      /*!< SPI0_TX PDMA channel number            */
#define PDMA_SPI0_RX              PDMA_CH3                      /*!< SPI0_RX PDMA channel number            */
#define PDMA_SPI1_TX              PDMA_CH6                      /*!< SPI1_TX PDMA channel number            */
#define PDMA_SPI1_RX              PDMA_CH7                      /*!< SPI1_RX PDMA channel number            */

#define PDMA_USART0_TX            PDMA_CH4                      /*!< USART0_TX PDMA channel number          */
#define PDMA_USART0_RX            PDMA_CH5                      /*!< USART0_RX PDMA channel number          */
#define PDMA_USART1_TX            PDMA_CH8                      /*!< USART1_TX PDMA channel number          */
#define PDMA_USART1_RX            PDMA_CH9                      /*!< USART1_RX PDMA channel number          */

#define PDMA_GPTM0_CH1            PDMA_CH7                      /*!< GPTM0_CH1 PDMA channel number          */
#define PDMA_GPTM0_CH2            PDMA_CH0                      /*!< GPTM0_CH2 PDMA channel number          */
#define PDMA_GPTM0_CH3            PDMA_CH1                      /*!< GPTM0_CH3 PDMA channel number          */
#define PDMA_GPTM0_CH4            PDMA_CH0                      /*!< GPTM0_CH4 PDMA channel number          */
#define PDMA_GPTM0_TRIG           PDMA_CH7                      /*!< GPTM0_TRIG PDMA channel number         */
#define PDMA_GPTM0_UP             PDMA_CH2                      /*!< GPTM0_UP PDMA channel number           */

#define PDMA_GPTM1_CH1            PDMA_CH8                      /*!< GPTM1_CH1 PDMA channel number          */
#define PDMA_GPTM1_CH2            PDMA_CH10                     /*!< GPTM1_CH2 PDMA channel number          */
#define PDMA_GPTM1_CH3            PDMA_CH9                      /*!< GPTM1_CH3 PDMA channel number          */
#define PDMA_GPTM1_CH4            PDMA_CH11                     /*!< GPTM1_CH4 PDMA channel number          */
#define PDMA_GPTM1_TRIG           PDMA_CH11                     /*!< GPTM1_TRIG PDMA channel number         */
#define PDMA_GPTM1_UP             PDMA_CH9                      /*!< GPTM1_UP PDMA channel number           */

#define PDMA_MCTM_CH1             PDMA_CH2                      /*!< MCTM_CH1 PDMA channel number           */
#define PDMA_MCTM_CH2             PDMA_CH3                      /*!< MCTM_CH2 PDMA channel number           */
#define PDMA_MCTM_CH3             PDMA_CH6                      /*!< MCTM_CH3 PDMA channel number           */
#define PDMA_MCTM_CH4             PDMA_CH4                      /*!< MCTM_CH4 PDMA channel number           */
#define PDMA_MCTM_TRIG            PDMA_CH4                      /*!< MCTM_TRIG PDMA channel number          */
#define PDMA_MCTM_COM             PDMA_CH4                      /*!< MCTM_COM PDMA channel number           */
#define PDMA_MCTM_UP              PDMA_CH5                      /*!< MCTM_UP PDMA channel number            */

#define PDMA_FLAG_GE              (1UL << 0)    /*!< PDMA channel global event flag                         */
#define PDMA_FLAG_BE              (1UL << 1)    /*!< PDMA channel block end flag                            */
#define PDMA_FLAG_HT              (1UL << 2)    /*!< PDMA channel half transfer flag                        */
#define PDMA_FLAG_TC              (1UL << 3)    /*!< PDMA channel transfer complete flag                    */
#define PDMA_FLAG_TE              (1UL << 4)    /*!< PDMA channeltransfer error flag                        */

#define IS_PDMA_FLAG(FLAG)        (((FLAG & 0xFFFFFFE0) == 0) && (FLAG != 0))   /*!<                        */
#define IS_PDMA_CLEAR_FLAG(FLAG)  (((FLAG & 0xFFFFFFE0) == 0) && (FLAG != 0))   /*!<                        */

#define PDMA_INT_GE               (1UL << 0)    /*!< PDMA channel global event interrupt                    */
#define PDMA_INT_BE               (1UL << 1)    /*!< PDMA channel block end interrupt                       */
#define PDMA_INT_HT               (1UL << 2)    /*!< PDMA channel half transfer interrupt                   */
#define PDMA_INT_TC               (1UL << 3)    /*!< PDMA channel transfer complete interrupt               */
#define PDMA_INT_TE               (1UL << 4)    /*!< PDMA channel transfer error interrupt                  */

#define IS_PDMA_INT(INT)          (((INT & 0xFFFFFFE0) == 0) && (INT != 0))     /*!<                        */

#define IS_PDMA_BLK_CNT(CNT)      ((CNT > 0) && (CNT < 65536))                  /*!<                        */
#define IS_PDMA_BLK_LEN(LEN)      ((LEN > 0) && (LEN < 65536))                  /*!<                        */

/**
  * @}
  */  /* End of PDMA_Exported_Constants */

/* Exported macro ------------------------------------------------------------------------------------------*/

/** @defgroup PDMA_Exported_Macro PDMA exported macros
  * @{
  */

/**
  * @}
  */  /* End of PDMA_Exported_Macro */

/* Exported functions --------------------------------------------------------------------------------------*/

/** @defgroup PDMA_Exported_Functions PDMA exported functions
  * @{
  */

void PDMA_Config(u32 PDMA_Ch, PDMACH_InitTypeDef *PDMACH_InitStruct);
void PDMA_TranSizeConfig(u32 PDMA_Ch, u32 BlkCnt, u32 BlkLen);
void PDMA_EnaCmd(u32 PDMA_Ch, ControlStatus NewState);
void PDMA_SwTrigCmd(u32 PDMA_Ch, ControlStatus NewState);

void PDMA_IntConig(u32 PDMA_Ch, u32 PDMA_Int, ControlStatus NewState);
FlagStatus PDMA_GetFlagStatus(u32 PDMA_Ch, u32 PDMA_Flag);
void PDMA_ClearFlag(u32 PDMA_Ch, u32 PDMA_Flag);

/**
  * @}
  */  /* End of PDMA_Exported_Functions group */

/**
  * @}
  */  /* End of PDMA group */

/**
  * @}
  */  /* End of HT32F175x_275x_Peripheral_Driver group */

#ifdef __cplusplus
}
#endif

#endif /* __HT32F175x_275x_PDMA_H --------------------------------------------------------------------------*/
