#include "uart.h"

//**********晶振设定(仅可选择一个)**********//
//#define CRYSTAL_6M
#define CRYSTAL_110592
//#define CRYSTAL_12M

//**********波特率设定(仅可选择一个)**********//
//#define RATE62500
//#define RATE19200
#define RATE9600
//#define RATE4800
//#define RATE2400
//#define RATE1200

#ifdef _HAVE_INIT_UART
void InitUART(){
	TMOD=(TMOD&0x0F)|0x20;//Timer0模式不变，Timer1为8位自动加载(For UART)
	#if defined(CRYSTAL_110592)
		#if defined(RATE19200)
			TL1=0xFD;
			TH1=0xFD;
			PCON=0x80;
		#elif defined(RATE9600)
			TL1=0xFD;
			TH1=0xFD;
			PCON=0x00;
		#elif defined(RATE4800)
			TL1=0xFA;
			TH1=0xFA;
			PCON=0x00;
		#elif defined(RATE2400)
			TL1=0xF4;
			TH1=0xF4;
			PCON=0x00;
		#elif defined(RATE1200)
			TL1=0xE8;
			TH1=0xE8;
			PCON=0x00;
		#else
			#error Unknow Rate
		#endif
	#elif defined(CRYSTAL_12M)
		#if defined(RATE62500)
			TL1=0xFF;
			TH1=0xFF;
			PCON=0x80;
		#elif defined(RATE4800)//可能产生误码
			TL1=0xF3;
			TH1=0xF3;
			PCON=0x80;
		#elif defined(RATE2400)
			TL1=0xE6;
			TH1=0xE6;
			PCON=0x80;
		#elif defined(RATE1200)
			TL1=0xE6;
			TH1=0xE6;
			PCON=0x00;
		#else
			#error Unknow Rate
		#endif
	#elif defined(CRYSTAL_6M)
		#if defined(RATE2400)
			TL1=0xF3;
			TH1=0xF3;
			PCON=0x80;
		#elif defined(RATE1200)
			TL1=0xF3;
			TH1=0xF3;
			PCON=0x00;
		#else
			#error Unknow Rate
		#endif
	#else
		#error Unknow Crystal
	#endif
	SCON=0x58;
	TR1=1;
}
#endif //end of _HAVE_INIT_UART

#ifdef _HAVE_SENDSTR_UART
void SendStrUART(char * Str){
	while(*Str){
		SBUF=*Str;
		while(TI==0)
			nop;
		TI=0;
		Str++;
	}
}
#endif //end of _HAVE_SENDSTR_UART

#ifdef _HAVE_SENDBYTE_UART
void SendByteUART(uchar Data){
	SBUF=Data;
	while(TI==0)
		nop;
	TI=0;
}
#endif //end of _HAVE_SENDBYTE_UART

#ifdef _HAVE_RECIVEBYTE_UART
uchar ReciveByteUART(){
	uchar tmp;
	while(RI==0)
		nop;
	tmp=SBUF;
	RI=0;
	return tmp;
}
#endif //end of _HAVE_RECIVEBYTE_UART

