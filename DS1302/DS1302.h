/******************************************************************************
ʹ��ע������:
1.��DS1302.c���趨��ʹ�õ�������
2.�ڳ���ʼӦ���ȵ��ó�ʼ������DS1302_init()
3.����ȥ����12Сʱģʽ�ĺ�������Ϊ��ȡ����ͳһ����ֻ����ʮλ�͸�λ������
4.���û�ȡ����ʱӦʹ��һ��2�ֽڵ�bufָ����Ϊ��������������ȡ�Ľ��Ϊʮλ�͸�λ��
******************************************************************************/
#ifndef _DS1302_H_
#define _DS1302_H_

#include "at89x52.h"
#include "intrins.h"
#define uchar unsigned char
#define uint unsigned int
#define nop _nop_()

void DS1302_write(uchar type,uchar addr,uchar bytedata);//ָ����ַд����(typeָ��CLOCK��RAM)
uchar DS1302_read(uchar type,uchar addr);//ָ����ַ������(typeָ��CLOCK��RAM)

void DS1302_init();//init DS1302 signal

void DS1302_GetSEC(uchar RtnData[]);//Get SEC=RtnData[0]*10+RtnData[1]
void DS1302_GetMIN(uchar RtnData[]);//Get MIN=RtnData[0]*10+RtnData[1]
void DS1302_GetHR(uchar RtnData[]);////Get HR=RtnData[0]*10+RtnData[1]
void DS1302_GetDATE(uchar RtnData[]);//Get DATE=RtnData[0]*10+RtnData[1]
void DS1302_GetMONTH(uchar RtnData[]);//Get MONTH=RtnData[0]*10+RtnData[1]
void DS1302_GetDAY(uchar RtnData[]);//Get DAY= (RtnData[0]*10 +) RtnData[1]
void DS1302_GetYEAR(uchar RtnData[]);//Get YEAR= 2000 + RtnData[0]*10 + RtnData[1]

void DS1302_SetSEC(uchar SetData);//SetData should in range 0--59
void DS1302_SetMIN(uchar SetData);//SetData should in range 0--59
void DS1302_SetHR24(uchar SetData);//SetData should in range 0--24
//void DS1302_SetHR12(uchar SetData,uchar AMPM);//SetData should in range 1--12
void DS1302_SetDATE(uchar SetData);//SetData should in range 1--31(but should be right date!!!)
void DS1302_SetMONTH(uchar SetData);//SetData should in range 1--12(but should be right date!!!)
void DS1302_SetDAY(uchar SetData);//SetData should in range 1--7
void DS1302_SetYEAR(uchar SetData);//SetData should in range 0--99

void DS1302_SetWP();//Set Write Protect
void DS1302_ClrWP();//Clear Write Protect

#endif //end of _DS1302_H_
