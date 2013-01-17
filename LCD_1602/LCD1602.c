#include "LCD1602.h"

/********************1602对51的引脚设定********************/
sbit RS=P2^7;						//寄存器选择信号
sbit RW=P2^6;						//读写信号
sbit E=P2^5;						//使能信号
#define DB0_DB7 P0					//数据信号

/********************内部函数********************/
void Delay1602(uint N)//延迟
{
	int i;
	for(i=0;i<N;i++)i=i;
}

void CheckBusy1602()//检查屏幕是否忙
{
	uchar TEMP;
	DB0_DB7=0xff;
	RW=1;
	RS=0;
	E=0;
	nop;
	E=1;
	do{
		nop;
        	TEMP=DB0_DB7;
	}while((TEMP&0x80)==0x80);
	RW=0;
}

void Write1602(uchar tempdata)//在tmpdata设定指令
{
	DB0_DB7=tempdata;
	RS=0;
	RW=0;
	E=0;
	nop;
	E=1;
	nop;
	CheckBusy1602();
}

/********************接口函数********************/
#ifdef _HAVE_INITSCREEN_1602
void InitScreen1602()//初始化显示屏
{
	RS=0;
	RW=0;
	E=1;
	Write1602(0x38);// 0011 1000
	Delay1602(1000);
	Write1602(0x38);// 0011 1000
	Delay1602(1000);
	Write1602(0x38);// 0011 1000 设定8bits汇流排，显示两行，使用5*7的字形
	Write1602(0x0E);// 0000 1110 设定显示器开，光标开，光标闪烁
	Write1602(0x06);// 0000 0110 设定字符不动光标右移
	Write1602(0x01);// 0000 0001 清屏
}
#endif //end of _HAVE_INITSCREEN_1602

#ifdef _HAVE_CLEARSCREEN_1602
void ClearScreen1602()//清屏
{
	RS=0;
	RW=0;
	DB0_DB7=1;
	E=0;
	nop;
	E=1;
	nop;
	CheckBusy1602();
}
#endif //end of _HAVE_CLEARSCREEN_1602

#ifdef _HAVE_CURSORBACK_1602
void CursorBack1602()//光标归位
{
	RS=0;
	RW=0;
	DB0_DB7=2;
	E=0;
	nop;
	E=1;
	nop;
	CheckBusy1602();
}
#endif //end of _HAVE_CURSORBACK_1602

#ifdef _HAVE_SETMODE_1602
void SetMode1602(uchar mode)//光标模式设定
{
	RS=0;
	RW=0;
	if(mode>3)
	{
		DB0_DB7=2;//默认模式：AC自加，光标右移
	}
	else
	{
		DB0_DB7=4+mode;//设定模式
		//0:光标左移AC自减
		//1:显示器字符右移，光标不动
		//2:光标右移AC自加
		//3:显示器字符左移，光标不动
	}
	E=0;
	nop;
	E=1;
	nop;
	CheckBusy1602();
}
#endif //end of _HAVE_SETMODE_1602

#ifdef _HAVE_SETSCREEN_1602
void SetScreen(uchar mode)//显示模式设定
{
	RS=0;
	RW=0;
	if(mode>7)
	{
		DB0_DB7=0x0F;//默认模式：显示光标/光标闪烁/显示开
	}
	else
	{
		DB0_DB7=8+mode;//设定模式
		//0:不显示光标/光标不闪烁/显示关
		//1:不显示光标/光标闪烁/显示关
		//2:显示光标/光标不闪烁/显示关
		//3:显示光标/光标闪烁/显示关
		//4:不显示光标/光标不闪烁/显示开
		//5:不显示光标/光标闪烁/显示开
		//6:显示光标/光标不闪烁/显示开
		//7:显示光标/光标闪烁/显示开
	}
	E=0;
	nop;
	E=1;
	nop;
	CheckBusy1602();
}
#endif //end of _HAVE_SETSCREEN_1602

#ifdef _HAVE_SETCURSOR_1602
void SetCursor1602(uchar action)//光标操作
{
	RS=0;
	RW=0;
	if(action>3){
		DB0_DB7=1;//默认操作：光标右移
	}
	else{
		DB0_DB7=0x10+action;//设定模式
		//0:光标左移AC自减
		//4:光标右移AC自加
		//8:显示器字符左移，光标不动
		//C:显示器字符右移，光标不动
	}
	E=0;
	nop;
	E=1;
	nop;
	CheckBusy1602();	
}
#endif //end of _HAVE_SETCURSOR_1602

#ifdef _HAVE_GETRAM_1602
uchar GetRam1602(uchar address)//获取DDRAM或CGRAM的内容
{
	uchar Ret;
	RS=1;
	RW=1;
	DB0_DB7=address;
	E=0;
	nop;
	E=1;
	nop;
	Ret=DB0_DB7;
	CheckBusy1602();
	return Ret;
}
#endif //end of _HAVE_GETRAM_1602

#ifdef _HAVE_SETCGNEXT_1602
void SetCG_Next1602(uchar address)//设定下一个要存入CGRAM的地址(范围0x00--0x3F)
{
	RS=0;
	RW=0;
	if(address>0x3F){
		DB0_DB7=0x40;
	}
	else{
		DB0_DB7=0x40+address;
	}
	E=0;
	nop;
	E=1;
	nop;
	CheckBusy1602();
}
#endif //end of _HAVE_SETCGNEXT_1602

#ifdef _HAVE_SETDDNEXT_1602
void SetDD_Next1602(uchar address)//设定下一个要存入DDRAM的地址(范围0x00--0x7F)
{
	RS=0;
	RW=0;
	if(address>0x7F){
		DB0_DB7=0x80;
	}
	else{
		DB0_DB7=0x80+address;
	}
	E=0;
	nop;
	E=1;
	nop;
	CheckBusy1602();
}
#endif //end of _HAVE_SETDDNEXT_1602

#ifdef _HAVE_PUTCHAR_1602
void PutChar1602(uchar tempdata)//输出字符
{
	DB0_DB7=tempdata;
	RS=1;
	nop;
	RW=0;
	E=0;
	nop;
	E=1;
	nop;
	CheckBusy1602();
}
#endif //end of _HAVE_PUTCHAR_1602

#ifdef _HAVE_PRINTSTR_1602
void PrintStr1602(char * Str){
	while(*Str){
		PutChar1602(*Str);
		Str++;
	}
}
#endif //end of _HAVE_PRINTSTR_1602

#ifdef _HAVE_GETAC_1602
uchar GetAC1602()//获取AC的值
{
	uchar TEMP;
	uchar Ret;
	RW=1;
	RS=0;
	E=0;
	nop;
	E=1;
	do{
		nop;
		TEMP=DB0_DB7;
	}while((TEMP&0x80)==0x80);
	Ret=TEMP&0x7F;
	RW=0;
	return Ret;
}
#endif //end of _HAVE_GETAC_1602
