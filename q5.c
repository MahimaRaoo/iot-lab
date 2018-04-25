#include<stdio.h>
#include"NUC1xx.h"
#include"Driver/DrvSYS.h"
#include"Driver/DrvGPIO.h"
#include"Driver/DrvUART.h"
#include"LCD_Driver.h"
#include"Seven_Segment.h"

void seven_seg(int val)
{
	int dig;
	dig=val/1000;
	close_seven_segment();
	show_seven_segment(3,dig);
	DrvSYS_Delay(2000);
	
	val=val-dig*1000;
	dig=val/100;
	close_seven_segment();
	show_seven_segment(2,dig);
	DrvSYS_Delay(2000);
	
	val=val-dig*100;
	dig=val/10;
	close_seven_segment();
	show_seven_segment(1,dig);
	DrvSYS_Delay(2000);
	
	val=val-dig*10;
	dig=val;
	close_seven_segment();
	show_seven_segment(0,dig);
	DrvSYS_Delay(2000);
	
	}
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
	
	DrvADC_Open(ADC_SINGLE_END,ADC_SINGLE_OP , 0x01,INTERNAL_HCLK , 1);
	while(1)
	{
		DrvADC_StartConvert(); // start A/D conversion
while(DrvADC_IsConversionDone()==FALSE);
value = ADC->ADDR[0].RSLT & 0xFFF;
		
		sprintf(text,"Value :%d",value);
		print_lcd(0,text);
		seven_seg(value);
		}
	
	}