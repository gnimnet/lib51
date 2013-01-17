/******************************************************************************
Write by Ming	2008-11-25
*******************************************************************************
ʹ��ע������:
1.��AT24CXX.c���趨оƬ����������
2.��оƬдʱӦע��"Roll Over"
	24C02Ϊ32��ҳ��ÿҳ8�ֽ�
	24C04Ϊ32��ҳ��ÿҳ16�ֽ�
	24C08Ϊ64��ҳ��ÿҳ16�ֽ�
	24C016Ϊ128��ҳ��ÿҳ16�ֽ�
  �ڶ�����ʱ���ڶ����һҳ�����һ���ֽں�"Roll Over"����һ��ҳ�ĵ�һ���ֽ�
  ��д����ʱ���ڵ�ǰҳ���һ���ֽں�"Roll Over"����ǰҳ�ĵ�һ���ֽ�(ע��!)
3.DeviceAddressΪ8λ���豸��ַ�������˶�/д��ָ��
	Bit		7	6	5	4	3	2	1	0
	24C02	1	0	1	0	A2	A1	A0	R/W
	24C04	1	0	1	0	A2	A1	P0	R/W
	24C08	1	0	1	0	A2	P1	P0	R/W
	24C016	1	0	1	0	P2	P1	P0	R/W
  DeviceAddressӦΪ0xA?
  ����02/04/08Ӧ��֤Aλ��Ӧ���ⲿ����
  ����04/08/16���PΪ��Ϊ��λ��ַ
  ������R/Wλ�øߣ�д����R/Wλ�õ�
******************************************************************************/
#ifndef	_AT24CXX_H_
#define	_AT24CXX_H_

#include "at89x52.h"
#include "intrins.h"
#define uchar unsigned char
#define uint unsigned int
#define nop _nop_()

bit IICWrite(uchar DeviceAddress,uchar WordAddress,uchar *DataPointer,uchar num);//��24CXX��ָ����ַд�����ɸ����ݺ���
bit IICRead(uchar DeviceAddress,uchar WordAddress,uchar *DataPointer,uchar num);//��24CXX��ָ����ַ�������ɸ����ݺ���
bit IICWriteByte(uchar DeviceAddress,uchar WordAddress,uchar Data);//��24CXX��ָ����ַд��һ�ֽ�����
bit IICReadByte(uchar DeviceAddress,uchar WordAddress,uchar *Data);//��24CXX��ָ����ַ����һ�ֽ�����

#endif //end of _AT24CXX_H_