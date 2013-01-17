#include "AT24CXX.h"

/********************24CXX对51的引脚设定********************/
sbit SCL=P1^0;						//时钟信号
sbit SDA=P1^1;						//数据信号

/********************内部函数********************/
void IICClockDelay(){//IIC总线时钟电平延时
    nop;nop;nop;nop;nop;nop;
}

void StartIIC(){//发送IIC总线启动时序
	SCL=1;
	IICClockDelay();
	SDA=1;
	IICClockDelay();
	SDA=0;
	IICClockDelay();
	SCL=0;
	IICClockDelay();   
}

void StopIIC(){//发送IIC总线停止时序
	SDA=0;
	IICClockDelay();
	SCL=1;
	IICClockDelay();
	SDA=1;
	IICClockDelay();
	SCL=1;
	IICClockDelay();
}

void IICAck(bit ackValue){//MCU对24CXX的应答函数
	if(ackValue)
		SDA=1;//ackValue=1表示应答
	else
		SDA=0;//ackValue=0表示不应答
	IICClockDelay();
	SCL=1;
	IICClockDelay();
	SCL=0;
	IICClockDelay();
}

bit IICSendByte(uchar byteData){//向24CXX发送一个字节数据或地址函数，返回值0则成功
	bit ackFlag;
	uchar i;
	for(i=0;i<8;i++){//要传送的数据长度为8位
		if((byteData<<i)&0x80)//依次判断待发送位高低
			SDA=1;
		else
			SDA=0;
		IICClockDelay();
		SCL=1;//置时钟线为高，通知24C02开始接收数据位
		IICClockDelay();
		SCL=0;
		IICClockDelay();
	}
	SDA=1;//8位数据发送完后释放数据线，准备接收应答位
	IICClockDelay();
	SCL=1;
	IICClockDelay();
	if(SDA==1)
		ackFlag=1;//24c02无应答
	else 
		ackFlag=0;//数据成功发送
	SCL=0;
	IICClockDelay();
	return ackFlag;//返回24C02应答标志
}

uchar IICRcvByte(){//从24CXX读取一个字节数据函数，返回值为读入的该字节
    uchar retbyteData=0x00,i;//置返回值初值为0x00
    for(i=0;i<8;i++){
		SDA=1;
		IICClockDelay();
		SCL=1;//拉高时钟线后读取数据线电平
		IICClockDelay();
		retbyteData=retbyteData<<1;//返回值依次左移一位
		if(SDA==1)//读取数据线电平至于返回值空出的一位
			retbyteData+=1;
		SCL=0;//拉低释放时钟线
		IICClockDelay();
	}
	return(retbyteData);
}

/********************接口函数********************/
bit IICWrite(uchar DeviceAddress,uchar WordAddress,uchar *DataPointer,uchar num){
	//向24CXX的指定地址写入若干个数据函数
	uchar i;
	StartIIC();//启动总线
	if(IICSendByte(DeviceAddress)==1)//发送器件地址
		return 1;//EPROM返回失败
	if(IICSendByte(WordAddress)==1)//发送器件子地址
		return 1;//EPROM返回失败
	for(i=0;i<num;i++){
		if(IICSendByte(*(DataPointer+i))==1)//发送数据
			return 1;//EPROM返回失败
	}
	StopIIC();//结束总线
	return 0;
}

bit IICRead(uchar DeviceAddress,uchar WordAddress,uchar *DataPointer,uchar num){
	//从24CXX的指定地址读入若干个数据函数
	uchar i;
	StartIIC();//启动总线
	if(IICSendByte(DeviceAddress)==1)//发送器件地址
		return 1;//EPROM返回失败
	if(IICSendByte(WordAddress)==1)//发送器件子地址
		return 1;//EPROM返回失败
	StopIIC();//结束总线
	StartIIC();//重新启动总线
	if(IICSendByte(DeviceAddress+1)==1)//发送器件地址
		return 1;//EPROM返回失败
	for(i=0;i<num-1;i++){
		*DataPointer=IICRcvByte();//接收数据
		IICAck(0);//发送应答位
		DataPointer++;
	}
	*DataPointer=IICRcvByte();//接收数据
	IICAck(1);
	StopIIC();//结束总线 
	return 0;
}

bit IICWriteByte(uchar DeviceAddress,uchar WordAddress,uchar Data){
	//从24CXX的指定地址写入一字节数据
	StartIIC();//启动总线
	if(IICSendByte(DeviceAddress)==1)//发送器件地址
		return 1;//EPROM返回失败
	if(IICSendByte(WordAddress)==1)//发送器件子地址
		return 1;//EPROM返回失败
	if(IICSendByte(Data)==1)//发送数据
		return 1;//EPROM返回失败
	StopIIC();//结束总线
	return 0;
}

bit IICReadByte(uchar DeviceAddress,uchar WordAddress,uchar *Data){
	//从24CXX的指定地址读出一字节数据
	StartIIC();//启动总线
	if(IICSendByte(DeviceAddress)==1)//发送器件地址
		return 1;//EPROM返回失败
	if(IICSendByte(WordAddress)==1)//发送器件子地址
		return 1;//EPROM返回失败
	StopIIC();//结束总线
	StartIIC();//重新启动总线
	if(IICSendByte(DeviceAddress+1)==1)//发送器件地址
		return 1;//EPROM返回失败
	*Data=IICRcvByte();//接收数据
	IICAck(1);
	StopIIC();//结束总线 
	return 0;
}
