#include <STC12C5A60S2.H>
#include "intrins.h"

#define ui unsigned int   //宏定义 将unsigned int命名为ui
#define uc unsigned char  //宏定义 将unsigned char命名为uc
	
sbit key1 = P3^2;  //按键1
sbit key2 = P3^3;  //按键2

#define wei1 0x01;
#define wei2 0x02;
#define wei3 0x04;
#define wei4 0x08;

uc smg[]=
{
0xc0,0xf9,0xa4,0xb0,
0x99,0x92,0x82,0xf8,
0x80,0x90,0x88,0x83,
0xc6,0xa1,0x86,0x8e
}; //   数码管码表0,1,2,3,4,5,6,7,8,9,a,b,c,d,e,f


int num1=0, num2=0, num3=0, num4=0, led=0;//四位数码管与一位led
				
void delay(ui i) // 动态数码管延时
{
	while(i--);
}	
						
void Delay10ms()		//延时10ms @11.0592MHz
{
	uc i, j;

	i = 108;
	j = 145;
	do
	{
		while (--j);
	} while (--i);
}

int main(void)
{
	ui i;	
	EA=1;//总中断打开
	EX0=1;//外部中断0打开
	EX1=1;//外部中断1打开
	IT0=1;//低电平触发外部中断0
	IT1=1;//下降沿触发外部中断1
	
	P2M0=0XFF;  //强推挽，使数码管更亮
	
	while(1)
	{
		for(i=1;i<=4;i++)
		{
			switch (i)
			{
				case (1):
					P2 = wei1;//数码管位1
					P0 = smg[num4];//千位
					break;
				case (2):
					P2 = wei2;//数码管位2
					P0 = smg[num3];//百位
					break;
				case (3):
					P2 = wei3;//数码管位3
					P0 = smg[num2];//十位
					break;
				case (4):
					P2 = wei4;//数码管位4
					P0 = smg[num1];//个位
					break;
			}
			delay(100);//数码管延时
			P0=0;
		}
		P1 = ~(0x01 << led);//led流水，共8个，0~7位
		
	}
}
void Int0_Routine(void) interrupt 0 // 外部中断0  数码管加法，led后移
{
	if(key1 == 0)     //按键按下，低电平触发
	{
		Delay10ms();  //消抖
		if(key1 == 0) //再次判断按键按下
		{
			num4++;//个位++
			led=led+2;//led后移
			
			if(num4 >= 10)//个位>=10,十位进1
			{
				num4 = 0;
				num3++;	
			}		
			if(num3 >= 10)//十位>=10,百位进1
			{
				num3=0;
				num2++;
			}
			if(num2 >= 10)//百位>=10,千位进1
			{
				num2=0;
				num1++;
			}
			if(num1 >= 10)//千位>=10,四位回0
			{
				num1=0;
				num2=0;
				num3=0;
				num4=0;
			}
			if(led>7)//如果led>7,回到0位led
			{
				led=0;
			}
		}
		while(!key1);  //判断按键是否抬起
		Delay10ms();   //延时消抖
		while(!key1);  //再次判断是否抬起
	}
}

void Int1_Routine(void) interrupt 2//外部中断1  数码管减法，led前移
{
	if(key2 == 0)//判断按键按下，下降沿触发
	{
		Delay10ms();  //消抖
		if(key2 == 0)  //再次判断按键是否按下
		{
			num4--;//个位--
			led=led-2;//led前移
			
			if(num4<0)//个位<0,十位退1
			{
				num3--;
				num4=9;
			}
			if(num3<0)//十位<0,百位退1
			{
				num2--;
				num3=9;
			}
			if(num2<0)//百位<0,千位退1
			{
				num1--;
				num2=9;
			}
			if(num1<0)//千位<0,四位回9
			{
				num1=9;
				num2=9;
				num3=9;
				num4=9;
			}
			if(led<0)//led<0，回到7位led
			{
				led=7;
			}
		}
		while(!key2);  //判断按键是否抬起
		Delay10ms();   //消抖
		while(!key2);  //再次判断按键是否抬起
	}
}