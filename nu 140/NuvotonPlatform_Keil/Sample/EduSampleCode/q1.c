#include<stdio.h>
#include"NUC1xx.h"
#include"Driver/DrvSYS.h"
#include"Driver/DrvGPIO.h"
#include"Driver/DrvUART.h"

void EINT1callback()
{
DrvGPIO_ClrBit(E_GPC,15);
DrvSYS_Delay(2000);
DrvGPIO_SetBit(E_GPC,15);
DrvSYS_Delay(2000);
DrvGPIO_ClrBit(E_GPB,11);
DrvSYS_Delay(2000);
DrvGPIO_SetBit(E_GPB,11);
DrvSYS_Delay(2000);
	}
	
int main(void)
	{
		UNLOCKREG();
SYSCLK-&gt;PWRCON.XTL12M_EN = 1; //Enable 12Mhz and set HCLK-&gt;12Mhz
SYSCLK-&gt;CLKSEL0.HCLK_S = 0;
LOCKREG();
		
		DrvGPIO_Open(E_GPC,15,E_IO_OUTPUT);
		DrvGPIO_SetBit(E_GPC,15);
		DrvGPIO_Open(E_GPB,11,E_IO_OUTPUT);
		DrvGPIO_Open(E_GPB,15,E_IO_INPUT);
		
		DrvGPIO_EnableEINT1(E_IO_BOTH_EDGE,E_MODE_EDGE,EINT1callback);
		while(1)
		{}
		}
		