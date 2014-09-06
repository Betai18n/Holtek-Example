//#ifndef __24BITAD_H
//#define __24BITAD_H	 
#include "ht32f175x_275x.h"
#include "ht32f175x_275x_board.h"

extern unsigned char Data[8];
extern unsigned char Data1[8];
extern float ad_data;
extern float ad_datalast;


unsigned long ReadCount(void);
void CovAD(void);
void initCovAD(void);
void initAD(void);


extern unsigned long def;
extern volatile long se;
extern volatile long se_last;
extern unsigned long ad_se;
extern unsigned long ad_selast;
extern unsigned long ad_c;

#define HX711_SCK PEout(5)   //PE5
#define HX711_DOUT PEin(6)	//PE6

