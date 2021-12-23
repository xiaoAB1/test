#include <STC12C5A60S2.H>
#include "intrins.h"
#define  uchar unsigned char

sbit key1 = P3^2;
sbit key2 = P3^3;
sbit key3 = P3^4;
sbit key4 = P3^5;

void Delay10ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 108;
	j = 145;
	do
	{
		while (--j);
	} while (--i);
}

void Delay500ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
 char flag=0;

void main()
{
	
	int i;
	P2M0=0XFF;
	EA=1;
	EX0=1;
	IT0=1;

	while(1)
	{	
		for(i=0;i<8;i++)
		{
			P1= ~(0X01<<i);
			Delay500ms();
			while(flag);
		}
	
	}

	

}







void Int0_Routine() interrupt 0
{
		if(key1 == 0) //判断按键是否按下
		{
			Delay10ms();  //延时消抖
			if(key1 == 0)  //再次判断
			{
				if(flag==0)
				{
					flag=1;
				}
				else
				{
					flag=0;
				}
			}
			while(!key1);  //判断按键是否抬起
			Delay10ms(); //消抖
			while(!key1); //再次判断
		}

}
