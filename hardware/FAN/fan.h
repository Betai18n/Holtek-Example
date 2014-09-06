#ifndef __FAN_H
#define __FAN_H	 
#include "ht32f175x_275x.h"
#include "ht32f175x_275x_board.h"
#include "sys.h"

#define fan1 PAout(0)		//风扇正电压
#define fan0 PAout(1)		//风扇负电压

void faninit(void);
void fanon(void);
void fanoff(void);

#endif
