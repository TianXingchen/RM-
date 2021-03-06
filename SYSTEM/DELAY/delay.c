#include "delay.h"

/**********************************************************************
*功能：使系统保持目前状态延迟一段时间
*输入：延迟时间，单位ms
***********************************************************************/
void delay_ms(unsigned int t)
{
	int i;
	for( i=0;i<t;i++)
	{
		int a=42000; //at 168MHz 42000 is ok
		while(a--);
	}
}

/**********************************************************************
*功能：使系统保持目前状态延迟一段时间
*输入：延迟时间，单位us
***********************************************************************/
void delay_us(unsigned int t)
{
	int i;
	for( i=0;i<t;i++)
	{
		int a=40;  //at 168MHz 40 is ok,the higher the number the more timing precise
		while(a--);
	}
}
