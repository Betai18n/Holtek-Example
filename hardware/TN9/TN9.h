#include "ht32f175x_275x.h"
#include "ht32f175x_275x_board.h"

void TN9init(void);
void TN9COV(void);
void TN_GetData_Target(void);
void TN_ReadData(unsigned char flag);

/*
#define TN_DATA (P6IN & BIT0)

#define TN_CLK (P6IN & BIT1)

#define TN_ACK1 (P6OUT |= BIT2)
#define TN_ACK0 (P6OUT &= ~BIT2)*/

#define TN_Data PEin(0)
#define TN_CLK PEin(1)
#define TN_ACK PEout(2)
