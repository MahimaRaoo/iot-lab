#include<stdio.h>
#include"NUC1xx.h"
#include"Driver/DrvSYS.h"
#include"Driver/DrvGPIO.h"
#include"Driver/DrvUART.h"
#include"LCD_Driver.h"
int counter=0;
void callback()
{
	int a;
	char text[16];
	
	print_lcd(0,"Interrupt received");
	counter++;
	a=DrvGPIO_GetPortBits(E_GPA);
sprintf(text,"port :%d",a);
	print_lcd(1,text);
	
	}
	
	int main()
	{
		char text1[16];
		UNLOCKREG();
SYSCLK-&gt;PWRCON.XTL12M_EN = 1; //Enable 12Mhz and set HCLK-&gt;12Mhz
SYSCLK-&gt;CLKSEL0.HCLK_S = 0;
LOCKREG();
			initial_panel();
	clr_all_panel();
		DrvGPIO_Open(E_GPA,15,E_IO_OUTPUT);
		DrvGPIO_EnableInt((E_GPA,15,E_IO_RISING,E_MODE_EDGE);
		DrvGPIO_SetDebounceTime(5,1);
		DrvGPIO_EnableDebounce(E_GPA,15);
		DrvGPIO_SetIntCallback(callback,NULL);
		
		
		while
		{
			sprintf(text1,"counter:%d",counter);
			print_lcd(3,text1);
			
			}
		}