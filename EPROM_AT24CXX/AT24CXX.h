/******************************************************************************
Write by Ming	2008-11-25
*******************************************************************************
使用注意事项:
1.在AT24CXX.c内设定芯片的连接引脚
2.向芯片写时应注意"Roll Over"
	24C02为32个页，每页8字节
	24C04为32个页，每页16字节
	24C08为64个页，每页16字节
	24C016为128个页，每页16字节
  在读操作时会在读最后一页的最后一个字节后"Roll Over"到第一个页的第一个字节
  在写操作时会在当前页最后一个字节后"Roll Over"到当前页的第一个字节(注意!)
3.DeviceAddress为8位的设备地址，包括了读/写的指令
	Bit		7	6	5	4	3	2	1	0
	24C02	1	0	1	0	A2	A1	A0	R/W
	24C04	1	0	1	0	A2	A1	P0	R/W
	24C08	1	0	1	0	A2	P1	P0	R/W
	24C016	1	0	1	0	P2	P1	P0	R/W
  DeviceAddress应为0xA?
  对于02/04/08应保证A位对应与外部引脚
  对于04/08/16则把P为作为高位地址
  读操作R/W位置高，写操作R/W位置低
******************************************************************************/
#ifndef	_AT24CXX_H_
#define	_AT24CXX_H_

#include "at89x52.h"
#include "intrins.h"
#define uchar unsigned char
#define uint unsigned int
#define nop _nop_()

bit IICWrite(uchar DeviceAddress,uchar WordAddress,uchar *DataPointer,uchar num);//向24CXX的指定地址写入若干个数据函数
bit IICRead(uchar DeviceAddress,uchar WordAddress,uchar *DataPointer,uchar num);//从24CXX的指定地址读入若干个数据函数
bit IICWriteByte(uchar DeviceAddress,uchar WordAddress,uchar Data);//从24CXX的指定地址写入一字节数据
bit IICReadByte(uchar DeviceAddress,uchar WordAddress,uchar *Data);//从24CXX的指定地址读出一字节数据

#endif //end of _AT24CXX_H_