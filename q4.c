#include<stdio.h>
#include"NUC1xx.h"
#include"Driver/DrvSYS.h"
#include"Driver/DrvGPIO.h"
#include"Driver/DrvUART.h"
#include"LCD_Driver.h"

int main()
{
	int value;
	char text[16];
	UNLOCKREG();
SYSCLK->PWRCON.XTL12M_EN = 1; //Enable 12Mhz and set HCLK-&gt;12Mhz
SYSCLK->CLKSEL0.HCLK_S = 0;
LOCKREG();
			initial_panel();
	clr_all_panel();
	
	DrvADC_Open(ADC_SINGLE_END,ADC_SINGLE_OP , 0x40,INTERNAL_HCLK , 1);
	while(1)
	{
		DrvADC_StartConvert(); // start A/D conversion
while(DrvADC_IsConversionDone()==FALSE);
value = ADC->ADDR[6].RSLT & 0xFFF;
		
		sprintf(text,"Value :%d",value);
		print_lcd(0,text);
		
		}
	
	}