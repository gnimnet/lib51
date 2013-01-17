/*****************************************************************
Write by Ming	2008-11-31
******************************************************************
使用注意事项:
1.先在LCD1602.c中设置引脚
2.字符的显示方式是对DDRAM的设定
		DDRAM	括号内的字符不能显示出来
	Line1	00	01	02	...	0F	(	...	27	)
	Line2	40	41	42	...	4F	(	...	67	)
  内部由AC来记录当前光标的位置
  应当控制显示不要超出，否则会显示不出来
  要设定光标位置时通过SetDD_Next1602()来进行，地址参照上面的DDRAM映射
3.显示模式设定调用函数SetScreen()
  参数中的模式如下:
	0:不显示光标/光标不闪烁/显示关
	1:不显示光标/光标闪烁/显示关
	2:显示光标/光标不闪烁/显示关
	3:显示光标/光标闪烁/显示关
	4:不显示光标/光标不闪烁/显示开
	5:不显示光标/光标闪烁/显示开
	6:显示光标/光标不闪烁/显示开
	7:显示光标/光标闪烁/显示开
	其他值:显示光标/光标闪烁/显示开
4.光标模式设定调用函数SetMode1602()
  参数中的模式如下:
	0:光标左移AC自减
	1:显示器字符右移，光标不动
	2:光标右移AC自加
	3:显示器字符左移，光标不动
5.光标操作SetCursor1602()函数
  参数设置如下:
	0:光标左移AC自减
	1:光标右移AC自加
	2:显示器字符左移，光标不动
	3:显示器字符右移，光标不动
6.在程序开始应进行屏幕初始化工作
*****************************************************************/
#ifndef	_LCD1602_H_
#define	_LCD1602_H_

#include "at89x52.h"
#include "intrins.h"
#define uchar unsigned char
#define uint unsigned int
#define nop _nop_()

//**************注释不需要的函数**************//
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

/********************底层控制函数********************/
void CheckBusy1602();				//检查屏幕是否忙
void Write1602(uchar tempdata);		//在tmpdata设定指令

/********************高层功能函数********************/

#ifdef _HAVE_INITSCREEN_1602
	void InitScreen1602();				//初始化显示屏
#endif //end of _HAVE_INITSCREEN_1602

#ifdef _HAVE_CLEARSCREEN_1602
	void ClearScreen1602();				//清屏
#endif //end of _HAVE_CLEARSCREEN_1602

#ifdef _HAVE_CURSORBACK_1602
	void CursorBack1602();				//光标归位
#endif //end of _HAVE_CURSORBACK_1602

#ifdef _HAVE_SETMODE_1602
	void SetMode1602(uchar mode);		//光标模式设定
#endif //end of _HAVE_SETMODE_1602

#ifdef _HAVE_SETSCREEN_1602
	void SetScreen1602(uchar mode);		//显示模式设定
#endif //end of _HAVE_SETSCREEN_1602

#ifdef _HAVE_SETCURSOR_1602
	void SetCursor1602(uchar action);	//光标操作
#endif //end of _HAVE_SETCURSOR_1602

#ifdef _HAVE_GETRAM_1602
	uchar GetRam1602(uchar address);	//获取DDRAM或CGRAM的内容
#endif //end of _HAVE_GETRAM_1602

#ifdef _HAVE_SETCGNEXT_1602
	void SetCG_Next1602(uchar address);	//设定下一个要存入CGRAM的地址(范围0x00--0x3F)
#endif //end of _HAVE_SETCGNEXT_1602

#ifdef _HAVE_SETDDNEXT_1602
	void SetDD_Next1602(uchar address);	//设定下一个要存入DDRAM的地址(范围0x00--0x7F)
#endif //end of _HAVE_SETDDNEXT_1602

#ifdef _HAVE_PUTCHAR_1602
	void PutChar1602(uchar tempdata);	//输出字符
#endif //end of _HAVE_PUTCHAR_1602

#ifdef _HAVE_PRINTSTR_1602
	void PrintStr1602(char * Str);		//输出字符串
#endif //end of _HAVE_PRINTSTR_1602

#ifdef _HAVE_GETAC_1602
	uchar GetAC1602();					//获取AC的值
#endif //end of _HAVE_GETAC_1602

#endif //end of _LCD1602_H_
