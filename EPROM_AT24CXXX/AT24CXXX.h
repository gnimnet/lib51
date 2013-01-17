/******************************************************************************
Write by Ming	2008-12-2
*******************************************************************************
使用注意事项:
1.在AT24CXXX.c内设定芯片的连接引脚
2.向芯片写时应注意"Roll Over"
	24C128为256个页，每页64字节
	24C256为512个页，每页64字节
  在读操作时会在读最后一页的最后一个字节后"Roll Over"到第一个页的第一个字节
  在写操作时会在当前页最后一个字节后"Roll Over"到当前页的第一个字节(注意!)
3.DeviceAddress为8位的设备地址，包括了读/写的指令
	Bit				7	6	5	4	3	2	1	0
	24C128/24C256	1	0	1	0	0	A1	A0	R/W
  DeviceAddress应为0xA?
  应保证A位对应与外部引脚
  读操作R/W位置高，写操作R/W位置低
4.WordAddress分为两个8位
  对于24C128，WordAddress1前两位无效
  对于24C256，WordAddress1前一位无效
******************************************************************************/
#ifndef	_AT24CXXX_H_
#define	_AT24CXXX_H_

#include "at89x52.h"
#include "intrins.h"
#define uchar unsigned char
#define uint unsigned int
#define nop _nop_()

//**************注释不需要的函数**************//
#define _HAVE_WRITE_24CXXX
#define _HAVE_READ_24CXXX
#define _HAVE_WRITEBYTE_24CXXX
#define _HAVE_READBYTE_24CXXX
//********************************************//

#ifdef _HAVE_WRITE_24CXXX
	bit IICWrite(uchar DeviceAddress,uchar WordAddress1,uchar WordAddress2,uchar *DataPointer,uchar num);//向24CXXX的指定地址写入若干个数据函数
#endif //end of _HAVE_WRITE_24CXXX

#ifdef _HAVE_READ_24CXXX
	bit IICRead(uchar DeviceAddress,uchar WordAddress1,uchar WordAddress2,uchar *DataPointer,uchar num);//从24CXXX的指定地址读入若干个数据函数
#endif //end of _HAVE_READ_24CXXX

#ifdef _HAVE_WRITEBYTE_24CXXX
	bit IICWriteByte(uchar DeviceAddress,uchar WordAddress1,uchar WordAddress2,uchar Data);//从24CXXX的指定地址写入一字节数据
#endif //end of _HAVE_WRITEBYTE_24CXXX

#ifdef _HAVE_READBYTE_24CXXX
	bit IICReadByte(uchar DeviceAddress,uchar WordAddress1,uchar WordAddress2,uchar *Data);//从24CXXX的指定地址读出一字节数据
#endif //end of _HAVE_READBYTE_24CXXX

#endif //end of _AT24CXXX_H_
