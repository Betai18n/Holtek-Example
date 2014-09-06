extern unsigned char ans[4];
extern unsigned char num;
extern unsigned int finaltep;


extern unsigned int count1;
extern volatile unsigned char flag18B20;
extern unsigned int count2;
extern unsigned int count3;
extern unsigned char count3flag;
extern unsigned int count4;
extern unsigned int count5;
extern unsigned int count6;
extern volatile unsigned char config[4];
extern volatile unsigned char startflag;
extern volatile unsigned char lockflag;
extern volatile unsigned char fanflag;
extern volatile unsigned char waterflag;
extern volatile unsigned char adflag;
extern unsigned char buzzerflag;

extern unsigned char keyflag;
extern unsigned char TN9flag;
extern unsigned char selecttemp[3];
extern unsigned char table_mbtemp[8];
extern unsigned char dN1[8];
extern unsigned char const tempdata1[4][4];
extern unsigned char const tempdata2[4][4];
extern unsigned int const needdrink[4][4];
extern unsigned char needdata[6];
extern unsigned char waterflagdata[2];

extern float T0,T1,dt;

extern unsigned int finaltime;
extern unsigned char const timedata[70][70];
extern unsigned int finalTN9temp;
extern unsigned int finalselecttemp;
extern unsigned char finaltimedata[4];
extern volatile unsigned int finalwater;
extern volatile unsigned int finalwaterlast;
extern volatile unsigned int needwater;
extern unsigned int finalsurroundtemp;


void keyfind(void);
void LoadData(void);
void SaveData(void);

