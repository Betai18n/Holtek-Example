#include "sys.h"
#include "ht32f175x_275x.h"
#include "ht32f175x_275x_board.h"

/*



    MDK-ARM:  
       - Under 'DVB_OFFSET_0x0'
         - In the project option menu, select 'Linker' window and enter 0x00000000 
           as R/O base address
         - In the project option menu, select 'C/C++' window and add 'DVB_OFFSET_0x0' 
           as Preprocessor Symbols Define
           
       - Under 'DVB_OFFSET_0x1000'
         - In the project option menu, select 'Linker' window and enter 0x00001000 
           as R/O base address
         - In the project option menu, select 'C/C++' window and add 'DVB_OFFSET_0x1000' 
           as Preprocessor Symbols Define

*/
#define NVIC_PRIORITY_GROUP_3          3 /* Preemption: 4 bits / Subpriority: 0 bits */
#define NVIC_PRIORITY_GROUP_4          4 /* Preemption: 3 bits / Subpriority: 1 bits */
#define NVIC_PRIORITY_GROUP_5          5 /* Preemption: 2 bits / Subpriority: 2 bits */
#define NVIC_PRIORITY_GROUP_6          6 /* Preemption: 1 bits / Subpriority: 3 bits */
#define NVIC_PRIORITY_GROUP_7          7 /* Preemption: 0 bits / Subpriority: 4 bits */

CKCU_ClocksTypeDef ClockFreq;
CKCU_CKOUTInitTypeDef CKOUTInit;
CKCU_PLLInitTypeDef PLLInit;

void SysClockConfig_72MHz(void)
{
  ErrStatus ClockStatus;

  /* Reset CKCU, SYSCLK = HSI */
  CKCU_DeInit();

  /* Enable HSE */
  CKCU_HSECmd(ENABLE);

  /* Wait until HSE is ready or time-out */
  ClockStatus = CKCU_WaitHSEReady();

  if(ClockStatus == SUCCESS)
  {
    /* PLL configuration, PLLCLK = 144MHz */
    PLLInit.ClockSource = CKCU_PLLSRC_HSE;
    PLLInit.CFG = CKCU_PLL_8M_144M;
    PLLInit.BYPASSCmd = DISABLE;
    CKCU_PLLInit(&PLLInit);

    CKCU_PLLCmd(ENABLE);

    /* Wait until PLL is ready */
    while(CKCU_GetClockReadyStatus(CKCU_FLAG_PLLRDY) == RESET);

    /* FLASH wait state configuration */
    FLASH_SetWaitState(FLASH_WAITSTATE_2);  /* FLASH two wait clock */

    /* HCLK = SYSCLK/2 */
    CKCU_SetHCLKPrescaler(CKCU_SYSCLK_DIV2);

    /* Configure PLL as system clock */
    ClockStatus = CKCU_SysClockConfig(CKCU_SW_PLL);

    if(ClockStatus != SUCCESS)
    {
      while(1);
    }
  }
  else
  {
    /* HSE is failed. User can handle this situation here. */
    while(1);
  }
}

void NVIC_Configuration(void)
{

    //NVIC_SetVectorTable(NVIC_VECTTABLE_FLASH, 0x0);	
    NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP_5);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级

}

/*********************************************************************************************************//**
  * @brief  Configures the system clocks.
  * @retval None
  ***********************************************************************************************************/
void CKCU_Configuration(void)
{
  /*--------------------------------------------------------------------------------------------------------*/
  /* APB Peripheral 0 Enable                                                                                */
  /* - CKCU_APBEN0_I2C0,   CKCU_APBEN0_I2C1, CKCU_APBEN0_SPI0, CKCU_APBEN0_SPI1, CKCU_APBEN0_USART0         */
  /* - CKCU_APBEN0_USART1, CKCU_APBEN0_AFIO, CKCU_APBEN0_EXTI, CKCU_APBEN0_PA,   CKCU_APBEN0_PB             */
  /* - CKCU_APBEN0_PC,     CKCU_APBEN0_PD,   CKCU_APBEN0_PE,   CKCU_APBEN0_SCI                              */
  /*--------------------------------------------------------------------------------------------------------*/
  //CKCU_APBPerip0ClockConfig(CKCU_APBEN0_PA | CKCU_APBEN0_PB | CKCU_APBEN0_PC | CKCU_APBEN0_PD | CKCU_APBEN0_PE, ENABLE);
	CKCU_APBPerip0ClockConfig(CKCU_APBEN0_AFIO  , ENABLE);
  /*--------------------------------------------------------------------------------------------------------*/
  /* APB Peripheral 1 Enable                                                                                */
  /* - CKCU_APBEN1_MCTM, CKCU_APBEN1_WDT,   CKCU_APBEN1_RTC,   CKCU_APBEN1_GPTM0, CKCU_APBEN1_GPTM1         */
  /* - CKCU_APBEN1_USB,  CKCU_APBEN1_BFTM0, CKCU_APBEN1_BFTM1, CKCU_APBEN1_OPA0,  CKCU_APBEN1_OPA1          */
  /* - CKCU_APBEN1_ADC                                                                                      */
  /*--------------------------------------------------------------------------------------------------------*/
  CKCU_APBPerip1ClockConfig(CKCU_APBEN1_RTC , ENABLE);

  /*--------------------------------------------------------------------------------------------------------*/
  /* AHB Peripheral Enable                                                                                  */
  /* - CKCU_AHBEN_PDMA, CKCU_AHBEN_CSIF, CKCU_AHBEN_CSIFM                                                   */
  /*--------------------------------------------------------------------------------------------------------*/
  //CKCU_AHBPeripClockConfig(CKCU_AHBEN_PDMA, ENABLE);

#if (ENABLE_CKOUT == 1)
  CKOUTConfig();
#endif
}

#if (ENABLE_CKOUT == 1)
/*********************************************************************************************************//**
  * @brief  Configures the debug output clock, PC8.
  * @retval None
  ***********************************************************************************************************/
void CKOUTConfig(void)
{
  CKCU_CKOUTInitTypeDef CKOUTInit;

  AFIO_GPCConfig(AFIO_PIN_8, AFIO_MODE_1);
  CKOUTInit.CKOUTSRC = CKCU_CKOUTSRC_HCLK_DIV16;
  CKCU_CKOUTConfig(&CKOUTInit);
}
#endif
