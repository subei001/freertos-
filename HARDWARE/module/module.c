#include "function.h"
#include "string.h"
#include "stdarg.h"
#include "stdio.h"
#include "string.h"
#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "module.h"
#include "hwjs.h"
#include "nrf24l01.h"
#include "spi.h"
#include "gps.h"
u8 netflag=1;
u8 netflag1=1;
u8 netflag2=1;
u8 netflag3=1;
char string[]="";
char *dest_string="";
char *dest_string1="";
char*p;
char*NetMessage;
u8 i,s;
int fport,bytes_length;
u8 lorasendflag=0;	
u8 IrRecSendflag=0;
u8 Voiceflag=0;
u8 data=0;
u8  y=0;
u8 port=0;
u16 USART1_RX_STA=0;       //����״̬���	
u8 USART1_RX_BUF[USART1_REC_LEN]; 
u8 test=2;
u8 count=0;
u8 count1=0;
u8 beat_count=0;
u8 INITFLAG=1;
uint32_t jk=0;
u8 Res;
		u8 netdata[]={22,61,97,78,78,0x01,0xc8,62};
char *delim=",";
char dest[10] = {""};
char dest1[10] = {""};	
uint8_t converted[8];
u8 rx_buf[33]={0};
u16 color=0;

char str[20]="";
char str1[20]="";
char str2[20]="";
char str3[20]="";
char str0[20]="";
char str4[100]="";
char str5[100]="";
u8 a[40]={0};
char *ret;
u8 kkkk;
 char *merged;
 char joinCmd [] = "at+join\r\n";
 char testCmd [] = "at+send=lora:1:5A00\r\n";
char atCmd [] ="at+set_config=lora:confirm:1\r\n";
	char position []	= "at+send=lora:1:008000002e3e04d109980d1201c88a\r\n";
//	char position1 []	= "at+send=lora:1:008000002e58119309bd1964007b8a\r\n";
char FeedbackOrder[]="OK Join Success\r\n";
//char FeedbackOrder1[]="OK \r\nat";
char FeedbackOrder1[]="OK";
const int bufferSize1=15;
const int bufferSize2=6;
	unsigned char buffer1[]={0x00,0x80,0x00,0x00,0x43,0x53,0x12,0xF6,0x10,0xEC,0x1B,0x0E,0x01,0xc8,0x8A};
	unsigned char buffer2[]={0x40,0x01,0xc8,0x01,0xc8,0x5b};

//一条入网。一条信息，判断是否收到正确的反馈；
void Jion_Net(){
//join the net initial
//initial
delay_ms(1500);
delay_ms(1500);

delay_ms(1000);
//清除标志位，否则第一位会丢失
USART_ClearFlag(USART1,USART_FLAG_TC); 
USART1_printf("%s",joinCmd);
while(netflag==1){
if(USART1_FINISH){
//		ret=strstr(string ,FeedbackOrder);
//		USART1_printf("%d",strncmp(string ,FeedbackOrder,2));
if(strncmp(string ,FeedbackOrder,2)==0)
{							

netflag=0;
//判断完成需要将消息数组清零，以便再次接收;
for(jk=0;jk<jkl;jk++)
{
string[jk]=0x00;
}
jkl = 0;

}else{
delay_ms(1500);
delay_ms(1000);
delay_ms(1500);

USART1_printf("%s",joinCmd);
delay_ms(1000);
for(jk=0;jk<jkl;jk++)
{
string[jk]=0x00;
}
jkl = 0;
}
USART1_FINISH = 0;
}

}

delay_ms(1000);
delay_ms(1500);
delay_ms(1000);

USART1_printf("%s",position);
while(netflag1==1){



if(USART1_FINISH){
//		ret=strstr(string ,FeedbackOrder);
//		USART1_printf("%d",strncmp(string ,FeedbackOrder1,4));
if(strncmp(string ,FeedbackOrder1,2)==0)
{							

netflag1=0;
for(jk=0;jk<jkl;jk++)
{
string[jk]=0x00;
}
jkl = 0;
}else{
delay_ms(1500);
delay_ms(1000);
delay_ms(1500);
delay_ms(1000);
USART1_printf("%s",position);

for(jk=0;jk<jkl;jk++)
{
string[jk]=0x00;
}
jkl = 0;
}	
USART1_FINISH = 0;
}
}


}






/* 串口接收中断，时序问题会导致接收的不完整；这里用的是空闲中断；接收完整的一帧（完整的一帧，好像根据标志位电平）；
如果收到带“：”的则是网关下行信息，需要对其进行处理分割，收到的是ascii码需要在对其进行转换 */
void Usart_Receive(){
//lora recevive
if(USART1_FINISH)
{


//USART3_printf("111 : %s\r\n",string);

if(strstr(string,":"))//如果sring含有““：”则返回包含”：“后的字符串
{
lorasendflag=1;
dest_string = strstr(string,":");
strncpy(dest, dest_string+1, 6);//指定比较的位置，数目
//USART1_printf("333 : %s\r\n",dest);
bytes_length=strlen(dest) / 2;
strHexToUint8Array(dest,converted,bytes_length);//此为冒号后内容，即网关下行信息
//USART1_printf("converted:%d\r\n",converted[0]);
}
if(strstr(string,"at"))
{
dest_string1 = strstr(string,"=");
p=strtok(dest_string1, delim);
//	printf("string : %s\r\n",p);
strncpy(dest1, p+1, 16);
fport=atoi(dest1);    //得到端口号，需要atoi一次，字符转整数
//USART1_printf("fport:%d\r\n",fport);
//printf("222 : %s\r\n",dest1);
}

for(jk=0;jk<jkl;jk++)
{
string[jk]=0x00;
}

jkl = 0;
USART1_FINISH = 0;
}
}

//红外接收处理，通过标志位的传递判断是否接受；
void IR_Poll(){
//irRemote receive	
if(hw_jsbz==1)	//接收完成标志位
{
hw_jsbz=0;	   //清零
	

//信息存储在u32 hw_jsm 需要将其转存为单个字节存储
data_u8[0] = (hw_jsm >> 24) & 0xff;	 
data_u8[1] = (hw_jsm >> 16) & 0xff; 	   
data_u8[2] = (hw_jsm >> 8)  & 0xff;
data_u8[3] =  hw_jsm       & 0xff;	
			
//大小端变化
data_u8[0]= reverse_bit8(data_u8[0]);
data_u8[1]= reverse_bit8(data_u8[1]);
data_u8[2]= reverse_bit8(data_u8[2]);
data_u8[3]= reverse_bit8(data_u8[3]);
//USART3_printf("%d\n",hw_jsm);
//USART3_printf("%d\n",data_u8[0]);
//USART3_printf("%d\n",data_u8[1]);
//USART3_printf("%d\n",data_u8[2]);
//USART3_printf("%d\n",data_u8[3]);	
//红外信息32位但是我们暂时只用16位搭载士兵的编号；
buffer2[1]=data_u8[0];//0x01
buffer2[2]=data_u8[1];//0xc8
	
//buffer2[3]=data_u8[2];//00
//buffer2[4]=data_u8[3];//123
//	IrRecSendflag=irflag;
//	Voiceflag=1;

//irflag表示击中的不同部位；并发送头盔发出声音
// forward 80; back  40;	r_leg 20;l_leg 10; right 08; left 04; 
	NRF24L01_TX_Mode();
	switch(irflag){
	case 5:
			buffer2[0]=0x80;
			buffer1[2]++;
	netdata[0]=22;netdata[4]=	irflag;NRF24L01_TxPacket( netdata );
			break;
	case 0:
			buffer2[0]=0x08;
			buffer1[2]++;
netdata[0]=22;netdata[4]=	irflag;NRF24L01_TxPacket( netdata );
			break;
	case 4:
			buffer2[0]=0x10;
			buffer1[2]++;
	netdata[0]=22;netdata[4]=	irflag;NRF24L01_TxPacket( netdata );
			break;
	case 3:
			buffer2[0]=0x20;
			buffer1[2]++;
	netdata[0]=22;netdata[4]=	irflag;NRF24L01_TxPacket( netdata );
			break;
	case 2:
			buffer2[0]=0x04;
			buffer1[2]++;
	netdata[0]=22;netdata[4]=	irflag;NRF24L01_TxPacket( netdata );
			break;
	case 1:
			buffer2[0]=0x40;
			buffer1[2]++;
	netdata[0]=22;netdata[4]=	irflag;NRF24L01_TxPacket( netdata );
			break;

}	

//拼接函数，将其转化为符合格式的指令
merged=newMergedData(buffer2,bufferSize2);
USART1_printf("%s",merged);
irflag=0;
free(merged);//动态分配需要及时清除
//USART3_printf("%d",3);
NRF24L01_RX_Mode();

//这是一个反馈重发，lora处理时间较长，过快发送，网络会显示正忙，丢失
//beat_count++;

//while(beat_count!=0){

////USART1_printf("%jaksjd");

//if(USART1_FINISH){

////		ret=strstr(string ,FeedbackOrder);
////		USART1_printf("%d",strncmp(string ,FeedbackOrder1,4));
//if(strncmp(string ,FeedbackOrder1,4)==0)
//{							

//beat_count--;
//for(jk=0;jk<jkl;jk++)
//{
//string[jk]=0x00;
//}
//jkl = 0;
//}else{
////delay_ms(1500);
////delay_ms(1000);
////delay_ms(1500);
//delay_ms(1000);
//USART1_printf("%s\n",merged);

//for(jk=0;jk<jkl;jk++)
//{
//string[jk]=0x00;
//}
//jkl = 0;
//}	
//USART1_printf("final:%d\n",beat_count);
//USART1_FINISH = 0;
//}
//}


}
}


//gps信息再处理，将信息填充到数组
void Gps_RecToSend()
{
// send gps message 
if(gpssendflag==1){
gpssendflag=0;
	
//longtidu经度
buffer1[4] = gpsposition[6];
buffer1[5] = gpsposition[7];
buffer1[6] = gpsposition[4];
buffer1[7] = gpsposition[5];

//latitude纬度
buffer1[8] = gpsposition[2];
buffer1[9] = gpsposition[3];
buffer1[10] = gpsposition[0];
buffer1[11] = gpsposition[1];

merged=newMergedData(buffer1,bufferSize1);
USART1_printf("%s",merged);
free(merged);
}
}
//nrf接收到信息发送出去
void Nrf_RecToSend(){
//nrf24l01  receive

if(NRF24L01_RxPacket(rx_buf)==0) //收到信息
{
	if(rx_buf[0]==22&&rx_buf[5]==0x01&&rx_buf[6]==0xc8)
{
//head nrf send message	
rx_buf[32]=0;
buffer1[1]=rx_buf [1];
buffer1[2]++;
//position		头部中枪
buffer2[0]=0x01;
//gun people id		射击者
buffer2[1]=rx_buf[3];
buffer2[2]=rx_buf[4];			
//unsigned char buffer2[]={0x40,0x01,0xc8,0x00,0x7b,0x5b};//3 and 4 no change
merged=newMergedData(buffer2,bufferSize2);
USART1_printf("%s",merged);
free(merged);
}

//gun nrf send message  
if(rx_buf[0]==11&&rx_buf[5]==0x01&&rx_buf[6]==0xc8)
{
buffer1[1]=rx_buf [1];// gun egg number
buffer1[2]++;
//	USART3_printf("333%d\r\n",buffer1[1]);
}
}	
}

//收到网关下行信息，处理发送出去
void Nrf_Send(){

// send message from nrf2401
if(lorasendflag==1){

//22 means send to head;
//11 means send to gun;
//78 means people number
NRF24L01_TX_Mode();
netdata[1]=fport;
netdata[2]=	converted[0];

//send to gun 
if(fport==3)
{netdata[0]=22;
NRF24L01_TxPacket( netdata );	
}

//send to gun 
if(fport==5)
{netdata[0]=11;
NRF24L01_TxPacket( netdata );	
}
NRF24L01_RX_Mode();	
lorasendflag=0;
}



}

//gps处理
void GPS_LogIn()
{

parseGpsBuffer();
printGpsBuffer();
}





