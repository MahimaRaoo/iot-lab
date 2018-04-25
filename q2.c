#include<stdio.h>
#include"NUC1xx.h"
#include"Driver/DrvSYS.h"
#include"Driver/DrvGPIO.h"
#include"Driver/DrvUART.h"
#include"LCD_Driver.h"

int main()
{
	char text[16];
	int a;
	UNLOCKREG();
SYSCLK-&gt;PWRCON.XTL12M_EN = 1; //Enable 12Mhz and set HCLK-&gt;12Mhz
SYSCLK-&gt;CLKSEL0.HCLK_S = 0;
LOCKREG();
	initial_panel();
	clr_all_panel();
	while(1)
	{
		DrvGPIO_SetPortBits(E_GPA,15);
		a=DrvGPIO_GetPortBits(E_GPA);
		sprintf(text,"port:%d",a);
		print_lcd(2,text);
		}
	}
	
	