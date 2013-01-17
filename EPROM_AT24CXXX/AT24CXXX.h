/******************************************************************************
Write by Ming	2008-12-2
*******************************************************************************
ʹ��ע������:
1.��AT24CXXX.c���趨оƬ����������
2.��оƬдʱӦע��"Roll Over"
	24C128Ϊ256��ҳ��ÿҳ64�ֽ�
	24C256Ϊ512��ҳ��ÿҳ64�ֽ�
  �ڶ�����ʱ���ڶ����һҳ�����һ���ֽں�"Roll Over"����һ��ҳ�ĵ�һ���ֽ�
  ��д����ʱ���ڵ�ǰҳ���һ���ֽں�"Roll Over"����ǰҳ�ĵ�һ���ֽ�(ע��!)
3.DeviceAddressΪ8λ���豸��ַ�������˶�/д��ָ��
	Bit				7	6	5	4	3	2	1	0
	24C128/24C256	1	0	1	0	0	A1	A0	R/W
  DeviceAddressӦΪ0xA?
  Ӧ��֤Aλ��Ӧ���ⲿ����
  ������R/Wλ�øߣ�д����R/Wλ�õ�
4.WordAddress��Ϊ����8λ
  ����24C128��WordAddress1ǰ��λ��Ч
  ����24C256��WordAddress1ǰһλ��Ч
******************************************************************************/
#ifndef	_AT24CXXX_H_
#define	_AT24CXXX_H_

#include "at89x52.h"
#include "intrins.h"
#define uchar unsigned char
#define uint unsigned int
#define nop _nop_()

//**************ע�Ͳ���Ҫ�ĺ���**************//
#define _HAVE_WRITE_24CXXX
#define _HAVE_READ_24CXXX
#define _HAVE_WRITEBYTE_24CXXX
#define _HAVE_READBYTE_24CXXX
//********************************************//

#ifdef _HAVE_WRITE_24CXXX
	bit IICWrite(uchar DeviceAddress,uchar WordAddress1,uchar WordAddress2,uchar *DataPointer,uchar num);//��24CXXX��ָ����ַд�����ɸ����ݺ���
#endif //end of _HAVE_WRITE_24CXXX

#ifdef _HAVE_READ_24CXXX
	bit IICRead(uchar DeviceAddress,uchar WordAddress1,uchar WordAddress2,uchar *DataPointer,uchar num);//��24CXXX��ָ����ַ�������ɸ����ݺ���
#endif //end of _HAVE_READ_24CXXX

#ifdef _HAVE_WRITEBYTE_24CXXX
	bit IICWriteByte(uchar DeviceAddress,uchar WordAddress1,uchar WordAddress2,uchar Data);//��24CXXX��ָ����ַд��һ�ֽ�����
#endif //end of _HAVE_WRITEBYTE_24CXXX

#ifdef _HAVE_READBYTE_24CXXX
	bit IICReadByte(uchar DeviceAddress,uchar WordAddress1,uchar WordAddress2,uchar *Data);//��24CXXX��ָ����ַ����һ�ֽ�����
#endif //end of _HAVE_READBYTE_24CXXX

#endif //end of _AT24CXXX_H_
