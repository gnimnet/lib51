#include "DS1302.h"

//**********定义相关地址**********//
#define DS1302_RC_BASE 0X81		//读时钟基地址
#define DS1302_RA_BASE 0XC1		//读RAM基地址
#define DS1302_WC_BASE 0x80		//写时钟基地
#define DS1302_WA_BASE 0xC0		//写RAM基地址

#define DS1302_SEC     0x00        //秒地址
#define DS1302_MIN     0x02        //分地址
#define DS1302_HR      0x04        //小时地址
#define DS1302_DATE    0x06        //日地址
#define DS1302_MONTH   0x08        //月
#define DS1302_DAY     0x0A        //星期
#define DS1302_YEAR    0x0C        //年

#define DS1302_CON     0x0E        //控制寄存器地址(写保护WP)
#define DS1302_TC      0x10        //Trickle Charger Address
#define DS1302_CB      0x3E        //Clock Burst Address


//**********设定引脚**********//
sbit DS1302_RST	=P0^0;
sbit DS1302_IO	=P0^1;
sbit DS1302_SCLK=P0^2;

void DS1302_write_byte(uchar bytedata){//对DS1302写字节
	uchar i;
	for(i=0;i<8;i++){
		DS1302_SCLK=0;
		if(bytedata&0x01)
            DS1302_IO=1;
		else
			DS1302_IO=0;
		DS1302_SCLK=1;
        bytedata=bytedata>>1;
	}
	DS1302_SCLK=0;
}

uchar DS1302_read_byte(){//对DS1302读字节
	uchar i;
	uchar temp=0;
	for(i=0;i<8;i++){
		temp=temp>>1;
		DS1302_SCLK=0;
		if(DS1302_IO==1)
			temp|=0x80;
		DS1302_SCLK=1;
	}
	DS1302_SCLK=0;
    return temp;
}

void DS1302_write(uchar type,uchar addr,uchar bytedata){//指定地址写数据(type指定CLOCK和RAM)
	uchar address;
	DS1302_RST=1;
	if(type)
    	address=addr+DS1302_WA_BASE;//write to RAM
	else
    	address=addr+DS1302_WC_BASE;//write to CLOCK
    DS1302_write_byte(address);
    DS1302_write_byte(bytedata);
	DS1302_RST=0;
}

uchar DS1302_read(uchar type,uchar addr){//指定地址读数据(type指定CLOCK和RAM)
	uchar address;
	uchar temp;
    DS1302_RST=1;
	if(type)
    	address=addr+DS1302_RA_BASE;//read from RAM
	else
    	address=addr+DS1302_RC_BASE;//read from CLOCK
	DS1302_write_byte(address);
	temp=DS1302_read_byte();
	DS1302_RST=0;
	return temp;
}

void DS1302_init(){//init DS1302 signal
	uchar temp;
	DS1302_RST=0;
	DS1302_IO =0; 
	DS1302_SCLK=0;
	DS1302_ClrWP();//clear write protect
	temp=DS1302_read(0,DS1302_SEC);
	if(temp&0x80)//clock halt!
		DS1302_write(0,DS1302_SEC,(temp&0x7F));//open clock halt flag
}

void DS1302_GetSEC(uchar RtnData[]){//Get SEC=RtnData[0]*10+RtnData[1]
	uchar temp;
	temp=DS1302_read(0,DS1302_SEC);
	RtnData[0]=(temp>>4)&0x07;
	RtnData[1]=temp&0x0F;
}

void DS1302_GetMIN(uchar RtnData[]){//Get MIN=RtnData[0]*10+RtnData[1]
	uchar temp;
	temp=DS1302_read(0,DS1302_MIN);
	RtnData[0]=(temp>>4)&0x07;
	RtnData[1]=temp&0x0F;
}

void DS1302_GetHR(uchar RtnData[]){////Get HR=RtnData[0]*10+RtnData[1]
	uchar temp;
	temp=DS1302_read(0,DS1302_HR);
	if(temp&0x80){//12 hour mode
		if(temp&0x20){//PM
			if(temp&0x10)
				temp=(temp&0x0F)+22;
			else
				temp=(temp&0x0F)+12;
		}
		else{//AM
			if(temp&0x10)
				temp=(temp&0x0F)+10;
			else
				temp=(temp&0x0F);
		}
		RtnData[0]=temp/12;
		RtnData[1]=temp%12;
	}
	else{//24 hour mode
		RtnData[0]=(temp>>4)&0x01;
		RtnData[1]=temp&0x0F;
		if(temp&0x20)
			RtnData[0]++;
	}
}

void DS1302_GetDATE(uchar RtnData[]){//Get DATE=RtnData[0]*10+RtnData[1]
	uchar temp;
	temp=DS1302_read(0,DS1302_DATE);
	RtnData[0]=(temp>>4)&0x03;
	RtnData[1]=temp&0x0F;
}

void DS1302_GetMONTH(uchar RtnData[]){//Get MONTH=RtnData[0]*10+RtnData[1]
	uchar temp;
	temp=DS1302_read(0,DS1302_MONTH);
	RtnData[0]=(temp>>4)&0x01;
	RtnData[1]=temp&0x0F;
}

void DS1302_GetDAY(uchar RtnData[]){//Get DAY= (RtnData[0]*10 +) RtnData[1]
	uchar temp;
	temp=DS1302_read(0,DS1302_DAY);
	RtnData[0]=0;
	RtnData[1]=temp&0x07;
}

void DS1302_GetYEAR(uchar RtnData[]){//Get YEAR= 2000 + RtnData[0]*10 + RtnData[1]
	uchar temp;
	temp=DS1302_read(0,DS1302_YEAR);
	RtnData[0]=(temp>>4)&0x0F;
	RtnData[1]=temp&0x0F;
}

void DS1302_SetSEC(uchar SetData){//SetData should in range 0--59
	uchar temp;
	temp=((SetData/10)<<4)+(SetData%10);
	DS1302_write(0,DS1302_SEC,temp);
}

void DS1302_SetMIN(uchar SetData){//SetData should in range 0--59
	uchar temp;
	temp=((SetData/10)<<4)+(SetData%10);
	DS1302_write(0,DS1302_MIN,temp);
}

void DS1302_SetHR24(uchar SetData){//SetData should in range 0--23
	uchar temp;
	temp=SetData%10;
	if(SetData/10==0)
		temp+=0x00;
	else if(SetData/10==1)
		temp+=0x10;
	else
		temp+=0x30;
	DS1302_write(0,DS1302_HR,temp);
}

/*
void DS1302_SetHR12(uchar SetData,uchar AMPM){//SetData should in range 1--12
	uchar temp;
	temp=SetData%10;
	if(SetData/10==1)
		temp+=0x10;
	if(AMPM){//is PM
		temp+=0x20;
	}
	temp+=0x80;
	DS1302_write(0,DS1302_HR,temp);
}
*/

void DS1302_SetDATE(uchar SetData){//SetData should in range 1--31(but should be right date!!!)
	uchar temp;
	temp=((SetData/10)<<4)+(SetData%10);
	DS1302_write(0,DS1302_DATE,temp);
}

void DS1302_SetMONTH(uchar SetData){//SetData should in range 1--12(but should be right date!!!)
	uchar temp;
	temp=((SetData/10)<<4)+(SetData%10);
	DS1302_write(0,DS1302_MONTH,temp);
}

void DS1302_SetDAY(uchar SetData){//SetData should in range 1--7
	DS1302_write(0,DS1302_DAY,SetData);
}

void DS1302_SetYEAR(uchar SetData){//SetData should in range 0--99
	uchar temp;
	temp=((SetData/10)<<4)+(SetData%10);
	DS1302_write(0,DS1302_YEAR,temp);
}

void DS1302_SetWP(){//Set Write Protect
	DS1302_write(0,DS1302_CON,0x80);
}

void DS1302_ClrWP(){//Clear Write Protect
	DS1302_write(0,DS1302_CON,0x00);
}
