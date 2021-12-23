#include <STC12C5A60S2.H>
#include "intrins.h"

#define ui unsigned int   //�궨�� ��unsigned int����Ϊui
#define uc unsigned char  //�궨�� ��unsigned char����Ϊuc
	
sbit key1 = P3^2;  //����1
sbit key2 = P3^3;  //����2

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
}; //   ��������0,1,2,3,4,5,6,7,8,9,a,b,c,d,e,f


int num1=0, num2=0, num3=0, num4=0, led=0;//��λ�������һλled
				
void delay(ui i) // ��̬�������ʱ
{
	while(i--);
}	
						
void Delay10ms()		//��ʱ10ms @11.0592MHz
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
	EA=1;//���жϴ�
	EX0=1;//�ⲿ�ж�0��
	EX1=1;//�ⲿ�ж�1��
	IT0=1;//�͵�ƽ�����ⲿ�ж�0
	IT1=1;//�½��ش����ⲿ�ж�1
	
	P2M0=0XFF;  //ǿ���죬ʹ����ܸ���
	
	while(1)
	{
		for(i=1;i<=4;i++)
		{
			switch (i)
			{
				case (1):
					P2 = wei1;//�����λ1
					P0 = smg[num4];//ǧλ
					break;
				case (2):
					P2 = wei2;//�����λ2
					P0 = smg[num3];//��λ
					break;
				case (3):
					P2 = wei3;//�����λ3
					P0 = smg[num2];//ʮλ
					break;
				case (4):
					P2 = wei4;//�����λ4
					P0 = smg[num1];//��λ
					break;
			}
			delay(100);//�������ʱ
			P0=0;
		}
		P1 = ~(0x01 << led);//led��ˮ����8����0~7λ
		
	}
}
void Int0_Routine(void) interrupt 0 // �ⲿ�ж�0  ����ܼӷ���led����
{
	if(key1 == 0)     //�������£��͵�ƽ����
	{
		Delay10ms();  //����
		if(key1 == 0) //�ٴ��жϰ�������
		{
			num4++;//��λ++
			led=led+2;//led����
			
			if(num4 >= 10)//��λ>=10,ʮλ��1
			{
				num4 = 0;
				num3++;	
			}		
			if(num3 >= 10)//ʮλ>=10,��λ��1
			{
				num3=0;
				num2++;
			}
			if(num2 >= 10)//��λ>=10,ǧλ��1
			{
				num2=0;
				num1++;
			}
			if(num1 >= 10)//ǧλ>=10,��λ��0
			{
				num1=0;
				num2=0;
				num3=0;
				num4=0;
			}
			if(led>7)//���led>7,�ص�0λled
			{
				led=0;
			}
		}
		while(!key1);  //�жϰ����Ƿ�̧��
		Delay10ms();   //��ʱ����
		while(!key1);  //�ٴ��ж��Ƿ�̧��
	}
}

void Int1_Routine(void) interrupt 2//�ⲿ�ж�1  ����ܼ�����ledǰ��
{
	if(key2 == 0)//�жϰ������£��½��ش���
	{
		Delay10ms();  //����
		if(key2 == 0)  //�ٴ��жϰ����Ƿ���
		{
			num4--;//��λ--
			led=led-2;//ledǰ��
			
			if(num4<0)//��λ<0,ʮλ��1
			{
				num3--;
				num4=9;
			}
			if(num3<0)//ʮλ<0,��λ��1
			{
				num2--;
				num3=9;
			}
			if(num2<0)//��λ<0,ǧλ��1
			{
				num1--;
				num2=9;
			}
			if(num1<0)//ǧλ<0,��λ��9
			{
				num1=9;
				num2=9;
				num3=9;
				num4=9;
			}
			if(led<0)//led<0���ص�7λled
			{
				led=7;
			}
		}
		while(!key2);  //�жϰ����Ƿ�̧��
		Delay10ms();   //����
		while(!key2);  //�ٴ��жϰ����Ƿ�̧��
	}
}