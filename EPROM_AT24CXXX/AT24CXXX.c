#include "AT24CXXX.h"

/********************24CXXX��51�������趨********************/
sbit SCL=P1^1;						//ʱ���ź�
sbit SDA=P1^0;						//�����ź�

/********************�ڲ�����********************/
void IICClockDelay(){//IIC����ʱ�ӵ�ƽ��ʱ
    nop;nop;nop;nop;nop;nop;
}

void StartIIC(){//����IIC��������ʱ��
	SCL=1;
	IICClockDelay();
	SDA=1;
	IICClockDelay();
	SDA=0;
	IICClockDelay();
	SCL=0;
	IICClockDelay();   
}

void StopIIC(){//����IIC����ֹͣʱ��
	SDA=0;
	IICClockDelay();
	SCL=1;
	IICClockDelay();
	SDA=1;
	IICClockDelay();
	SCL=1;
	IICClockDelay();
}

void IICAck(bit ackValue){//MCU��24CXX��Ӧ����
	if(ackValue)
		SDA=1;//ackValue=1��ʾӦ��
	else
		SDA=0;//ackValue=0��ʾ��Ӧ��
	IICClockDelay();
	SCL=1;
	IICClockDelay();
	SCL=0;
	IICClockDelay();
}

bit IICSendByte(uchar byteData){//��24CXX����һ���ֽ����ݻ��ַ����������ֵ0��ɹ�
	bit ackFlag;
	uchar i;
	for(i=0;i<8;i++){//Ҫ���͵����ݳ���Ϊ8λ
		if((byteData<<i)&0x80)//�����жϴ�����λ�ߵ�
			SDA=1;
		else
			SDA=0;
		IICClockDelay();
		SCL=1;//��ʱ����Ϊ�ߣ�֪ͨ24C02��ʼ��������λ
		IICClockDelay();
		SCL=0;
		IICClockDelay();
	}
	SDA=1;//8λ���ݷ�������ͷ������ߣ�׼������Ӧ��λ
	IICClockDelay();
	SCL=1;
	IICClockDelay();
	if(SDA==1)
		ackFlag=1;//24c02��Ӧ��
	else 
		ackFlag=0;//���ݳɹ�����
	SCL=0;
	IICClockDelay();
	return ackFlag;//����24C02Ӧ���־
}

uchar IICRcvByte(){//��24CXX��ȡһ���ֽ����ݺ���������ֵΪ����ĸ��ֽ�
    uchar retbyteData=0x00,i;//�÷���ֵ��ֵΪ0x00
    for(i=0;i<8;i++){
		SDA=1;
		IICClockDelay();
		SCL=1;//����ʱ���ߺ��ȡ�����ߵ�ƽ
		IICClockDelay();
		retbyteData=retbyteData<<1;//����ֵ��������һλ
		if(SDA==1)//��ȡ�����ߵ�ƽ���ڷ���ֵ�ճ���һλ
			retbyteData+=1;
		SCL=0;//�����ͷ�ʱ����
		IICClockDelay();
	}
	return(retbyteData);
}

/********************�ӿں���********************/
#ifdef _HAVE_WRITE_24CXXX
	bit IICWrite(uchar DeviceAddress,uchar WordAddress1,uchar WordAddress2,uchar *DataPointer,uchar num){
		//��24CXXX��ָ����ַд�����ɸ����ݺ���
		uchar i;
		StartIIC();//��������
		if(IICSendByte(DeviceAddress)==1)//����������ַ
			return 1;//EPROM����ʧ��
		if(IICSendByte(WordAddress1)==1)//���������ӵ�ַ1
			return 1;//EPROM����ʧ��
		if(IICSendByte(WordAddress2)==1)//���������ӵ�ַ2
			return 1;//EPROM����ʧ��
		for(i=0;i<num;i++){
			if(IICSendByte(*(DataPointer+i))==1)//��������
				return 1;//EPROM����ʧ��
		}
		StopIIC();//��������
		return 0;
	}
#endif //end of _HAVE_WRITE_24CXXX


#ifdef _HAVE_READ_24CXXX
	bit IICRead(uchar DeviceAddress,uchar WordAddress1,uchar WordAddress2,uchar *DataPointer,uchar num){
		//��24CXXX��ָ����ַ�������ɸ����ݺ���
		uchar i;
		StartIIC();//��������
		if(IICSendByte(DeviceAddress)==1)//����������ַ
			return 1;//EPROM����ʧ��
		if(IICSendByte(WordAddress1)==1)//���������ӵ�ַ1
			return 1;//EPROM����ʧ��
		if(IICSendByte(WordAddress2)==1)//���������ӵ�ַ2
			return 1;//EPROM����ʧ��
		StopIIC();//��������
		StartIIC();//������������
		if(IICSendByte(DeviceAddress+1)==1)//����������ַ
			return 1;//EPROM����ʧ��
		for(i=0;i<num-1;i++){
			*DataPointer=IICRcvByte();//��������
			IICAck(0);//����Ӧ��λ
			DataPointer++;
		}
		*DataPointer=IICRcvByte();//��������
		IICAck(1);
		StopIIC();//�������� 
		return 0;
	}
#endif //end of _HAVE_READ_24CXXX

#ifdef _HAVE_WRITEBYTE_24CXXX
	bit IICWriteByte(uchar DeviceAddress,uchar WordAddress1,uchar WordAddress2,uchar Data){
		//��24CXXX��ָ����ַд��һ�ֽ�����
		StartIIC();//��������
		if(IICSendByte(DeviceAddress)==1)//����������ַ
			return 1;//EPROM����ʧ��
		if(IICSendByte(WordAddress1)==1)//���������ӵ�ַ1
			return 1;//EPROM����ʧ��
		if(IICSendByte(WordAddress2)==1)//���������ӵ�ַ2
			return 1;//EPROM����ʧ��
		if(IICSendByte(Data)==1)//��������
			return 1;//EPROM����ʧ��
		StopIIC();//��������
		return 0;
	}
#endif //end of _HAVE_WRITEBYTE_24CXXX

#ifdef _HAVE_READBYTE_24CXXX
	bit IICReadByte(uchar DeviceAddress,uchar WordAddress1,uchar WordAddress2,uchar *Data){
		//��24CXXX��ָ����ַ����һ�ֽ�����
		StartIIC();//��������
		if(IICSendByte(DeviceAddress)==1)//����������ַ
			return 1;//EPROM����ʧ��
		if(IICSendByte(WordAddress1)==1)//���������ӵ�ַ1
			return 1;//EPROM����ʧ��
		if(IICSendByte(WordAddress2)==1)//���������ӵ�ַ2
			return 1;//EPROM����ʧ��
		StopIIC();//��������
		StartIIC();//������������
		if(IICSendByte(DeviceAddress+1)==1)//����������ַ
			return 1;//EPROM����ʧ��
		*Data=IICRcvByte();//��������
		IICAck(1);
		StopIIC();//�������� 
		return 0;
	}
#endif //end of _HAVE_READBYTE_24CXXX
