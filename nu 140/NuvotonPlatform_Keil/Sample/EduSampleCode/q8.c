#include<stdio.h>
#include"NUC1xx.h"
#include"Driver/DrvSYS.h"
#include"Driver/DrvGPIO.h"
#include"Driver/DrvUART.h"

void EINT1callback()
{
DrvGPIO_ClrBit(E_GPA,15);
DrvSYS_Delay(200);
	
	}
	
int main()
	{
		UNLOCKREG();
SYSCLK-&gt;PWRCON.XTL12M_EN = 1; //Enable 12Mhz and set HCLK-&gt;12Mhz
SYSCLK-&gt;CLKSEL0.HCLK_S = 0;
LOCKREG();
		DrvGPIO_Open(E_GPA,15,E_IO_OUTPUT);
		DrvGPIO_EnableEINT1(E_IO_BOTH_EDGE,E_MODE_EDGE,EINT1callback);
		while(1)
		{}
			
		}