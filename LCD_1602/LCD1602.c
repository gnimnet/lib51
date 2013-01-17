#include "LCD1602.h"

/********************1602��51�������趨********************/
sbit RS=P2^7;						//�Ĵ���ѡ���ź�
sbit RW=P2^6;						//��д�ź�
sbit E=P2^5;						//ʹ���ź�
#define DB0_DB7 P0					//�����ź�

/********************�ڲ�����********************/
void Delay1602(uint N)//�ӳ�
{
	int i;
	for(i=0;i<N;i++)i=i;
}

void CheckBusy1602()//�����Ļ�Ƿ�æ
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

void Write1602(uchar tempdata)//��tmpdata�趨ָ��
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

/********************�ӿں���********************/
#ifdef _HAVE_INITSCREEN_1602
void InitScreen1602()//��ʼ����ʾ��
{
	RS=0;
	RW=0;
	E=1;
	Write1602(0x38);// 0011 1000
	Delay1602(1000);
	Write1602(0x38);// 0011 1000
	Delay1602(1000);
	Write1602(0x38);// 0011 1000 �趨8bits�����ţ���ʾ���У�ʹ��5*7������
	Write1602(0x0E);// 0000 1110 �趨��ʾ��������꿪�������˸
	Write1602(0x06);// 0000 0110 �趨�ַ������������
	Write1602(0x01);// 0000 0001 ����
}
#endif //end of _HAVE_INITSCREEN_1602

#ifdef _HAVE_CLEARSCREEN_1602
void ClearScreen1602()//����
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
void CursorBack1602()//����λ
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
void SetMode1602(uchar mode)//���ģʽ�趨
{
	RS=0;
	RW=0;
	if(mode>3)
	{
		DB0_DB7=2;//Ĭ��ģʽ��AC�Լӣ��������
	}
	else
	{
		DB0_DB7=4+mode;//�趨ģʽ
		//0:�������AC�Լ�
		//1:��ʾ���ַ����ƣ���겻��
		//2:�������AC�Լ�
		//3:��ʾ���ַ����ƣ���겻��
	}
	E=0;
	nop;
	E=1;
	nop;
	CheckBusy1602();
}
#endif //end of _HAVE_SETMODE_1602

#ifdef _HAVE_SETSCREEN_1602
void SetScreen(uchar mode)//��ʾģʽ�趨
{
	RS=0;
	RW=0;
	if(mode>7)
	{
		DB0_DB7=0x0F;//Ĭ��ģʽ����ʾ���/�����˸/��ʾ��
	}
	else
	{
		DB0_DB7=8+mode;//�趨ģʽ
		//0:����ʾ���/��겻��˸/��ʾ��
		//1:����ʾ���/�����˸/��ʾ��
		//2:��ʾ���/��겻��˸/��ʾ��
		//3:��ʾ���/�����˸/��ʾ��
		//4:����ʾ���/��겻��˸/��ʾ��
		//5:����ʾ���/�����˸/��ʾ��
		//6:��ʾ���/��겻��˸/��ʾ��
		//7:��ʾ���/�����˸/��ʾ��
	}
	E=0;
	nop;
	E=1;
	nop;
	CheckBusy1602();
}
#endif //end of _HAVE_SETSCREEN_1602

#ifdef _HAVE_SETCURSOR_1602
void SetCursor1602(uchar action)//������
{
	RS=0;
	RW=0;
	if(action>3){
		DB0_DB7=1;//Ĭ�ϲ������������
	}
	else{
		DB0_DB7=0x10+action;//�趨ģʽ
		//0:�������AC�Լ�
		//4:�������AC�Լ�
		//8:��ʾ���ַ����ƣ���겻��
		//C:��ʾ���ַ����ƣ���겻��
	}
	E=0;
	nop;
	E=1;
	nop;
	CheckBusy1602();	
}
#endif //end of _HAVE_SETCURSOR_1602

#ifdef _HAVE_GETRAM_1602
uchar GetRam1602(uchar address)//��ȡDDRAM��CGRAM������
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
void SetCG_Next1602(uchar address)//�趨��һ��Ҫ����CGRAM�ĵ�ַ(��Χ0x00--0x3F)
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
void SetDD_Next1602(uchar address)//�趨��һ��Ҫ����DDRAM�ĵ�ַ(��Χ0x00--0x7F)
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
void PutChar1602(uchar tempdata)//����ַ�
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
uchar GetAC1602()//��ȡAC��ֵ
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
