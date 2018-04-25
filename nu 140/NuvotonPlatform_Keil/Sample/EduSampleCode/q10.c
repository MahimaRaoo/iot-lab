#include<stdio.h>
#include"NUC1xx.h"
#include"Driver/DrvSYS.h"
#include"Driver/DrvGPIO.h"
#include"Driver/DrvUART.h"
#include"LCD_Driver.h"
unsigned char CW[8]={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};
unsigned char CCW[8]={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};

void CW_motor(int deg)
{
	for(int i=0;i<(deg);i++)
	{
		for(int j=0;j<8;j++)
		{
			GPIOA->DOUT=CW[j];
			DrvSYS_Delay(2000);
			}}
	}
	void CCW_motor(int deg)
{
	for(int i=0;i<(deg);i++)
	{
		for(int j=0;j<8;j++)
		{
			GPIOA->DOUT=CCW[j];
			DrvSYS_Delay(2000);
			}}
	}
int main()
{
	CW_motor(51/2);
	
	//CCW_motor(51/2);
	
	
	}