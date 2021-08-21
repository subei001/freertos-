#ifndef _module_H
#define _module_H
#include "sys.h"


extern char * dest_string;
extern char * dest_string1;
extern u8 lorasendflag;
extern u8 IrRecSendflag;
extern u8 Voiceflag;



////1 baud  2=10s/oport  3=deserve  4turn off vtg  5.gsa 6.gll 7.gsv
//unsigned char gpstest1[37];
//unsigned char gpstest2[22];
//unsigned char gpstest3[21];
//unsigned char gpstest4[26];
//unsigned char gpstest5[26];
//unsigned char gpstest6[26];
//unsigned char gpstest7[26];



void Jion_Net(void);
void Usart_Receive(void);
void IR_Poll(void);	
void Gps_RecToSend(void);
void Nrf_RecToSend(void);
void Nrf_Send(void);
void GPS_LogIn(void);
void VoiceSend(void);

#endif
