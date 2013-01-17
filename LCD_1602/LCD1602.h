/*****************************************************************
Write by Ming	2008-11-31
******************************************************************
ʹ��ע������:
1.����LCD1602.c����������
2.�ַ�����ʾ��ʽ�Ƕ�DDRAM���趨
		DDRAM	�����ڵ��ַ�������ʾ����
	Line1	00	01	02	...	0F	(	...	27	)
	Line2	40	41	42	...	4F	(	...	67	)
  �ڲ���AC����¼��ǰ����λ��
  Ӧ��������ʾ��Ҫ�������������ʾ������
  Ҫ�趨���λ��ʱͨ��SetDD_Next1602()�����У���ַ���������DDRAMӳ��
3.��ʾģʽ�趨���ú���SetScreen()
  �����е�ģʽ����:
	0:����ʾ���/��겻��˸/��ʾ��
	1:����ʾ���/�����˸/��ʾ��
	2:��ʾ���/��겻��˸/��ʾ��
	3:��ʾ���/�����˸/��ʾ��
	4:����ʾ���/��겻��˸/��ʾ��
	5:����ʾ���/�����˸/��ʾ��
	6:��ʾ���/��겻��˸/��ʾ��
	7:��ʾ���/�����˸/��ʾ��
	����ֵ:��ʾ���/�����˸/��ʾ��
4.���ģʽ�趨���ú���SetMode1602()
  �����е�ģʽ����:
	0:�������AC�Լ�
	1:��ʾ���ַ����ƣ���겻��
	2:�������AC�Լ�
	3:��ʾ���ַ����ƣ���겻��
5.������SetCursor1602()����
  ������������:
	0:�������AC�Լ�
	1:�������AC�Լ�
	2:��ʾ���ַ����ƣ���겻��
	3:��ʾ���ַ����ƣ���겻��
6.�ڳ���ʼӦ������Ļ��ʼ������
*****************************************************************/
#ifndef	_LCD1602_H_
#define	_LCD1602_H_

#include "at89x52.h"
#include "intrins.h"
#define uchar unsigned char
#define uint unsigned int
#define nop _nop_()

//**************ע�Ͳ���Ҫ�ĺ���**************//
#define _HAVE_INITSCREEN_1602
#define _HAVE_CLEARSCREEN_1602
//#define _HAVE_CURSORBACK_1602
//#define _HAVE_SETMODE_1602
//#define _HAVE_SETSCREEN_1602
//#define _HAVE_SETCURSOR_1602
//#define _HAVE_GETRAM_1602
//#define _HAVE_SETCGNEXT_1602
#define _HAVE_SETDDNEXT_1602
#define _HAVE_PUTCHAR_1602
#define _HAVE_PRINTSTR_1602
//#define _HAVE_GETAC_1602
//********************************************//

/********************�ײ���ƺ���********************/
void CheckBusy1602();				//�����Ļ�Ƿ�æ
void Write1602(uchar tempdata);		//��tmpdata�趨ָ��

/********************�߲㹦�ܺ���********************/

#ifdef _HAVE_INITSCREEN_1602
	void InitScreen1602();				//��ʼ����ʾ��
#endif //end of _HAVE_INITSCREEN_1602

#ifdef _HAVE_CLEARSCREEN_1602
	void ClearScreen1602();				//����
#endif //end of _HAVE_CLEARSCREEN_1602

#ifdef _HAVE_CURSORBACK_1602
	void CursorBack1602();				//����λ
#endif //end of _HAVE_CURSORBACK_1602

#ifdef _HAVE_SETMODE_1602
	void SetMode1602(uchar mode);		//���ģʽ�趨
#endif //end of _HAVE_SETMODE_1602

#ifdef _HAVE_SETSCREEN_1602
	void SetScreen1602(uchar mode);		//��ʾģʽ�趨
#endif //end of _HAVE_SETSCREEN_1602

#ifdef _HAVE_SETCURSOR_1602
	void SetCursor1602(uchar action);	//������
#endif //end of _HAVE_SETCURSOR_1602

#ifdef _HAVE_GETRAM_1602
	uchar GetRam1602(uchar address);	//��ȡDDRAM��CGRAM������
#endif //end of _HAVE_GETRAM_1602

#ifdef _HAVE_SETCGNEXT_1602
	void SetCG_Next1602(uchar address);	//�趨��һ��Ҫ����CGRAM�ĵ�ַ(��Χ0x00--0x3F)
#endif //end of _HAVE_SETCGNEXT_1602

#ifdef _HAVE_SETDDNEXT_1602
	void SetDD_Next1602(uchar address);	//�趨��һ��Ҫ����DDRAM�ĵ�ַ(��Χ0x00--0x7F)
#endif //end of _HAVE_SETDDNEXT_1602

#ifdef _HAVE_PUTCHAR_1602
	void PutChar1602(uchar tempdata);	//����ַ�
#endif //end of _HAVE_PUTCHAR_1602

#ifdef _HAVE_PRINTSTR_1602
	void PrintStr1602(char * Str);		//����ַ���
#endif //end of _HAVE_PRINTSTR_1602

#ifdef _HAVE_GETAC_1602
	uchar GetAC1602();					//��ȡAC��ֵ
#endif //end of _HAVE_GETAC_1602

#endif //end of _LCD1602_H_
