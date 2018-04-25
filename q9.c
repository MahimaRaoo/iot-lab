#include<stdio.h>
#include"NUC1xx.h"
#include"Driver/DrvSYS.h"
#include"Driver/DrvGPIO.h"
#include"Driver/DrvUART.h"
#include"LCD_Driver.h"
#include"DrvADC.h"

void InitADC(void)
{
/* Step 1. GPIO initial */
GPIOA-&gt;OFFD|=0x00400000; //Disable digital input path
SYS-&gt;GPAMFP.ADC7_SS21_AD6=1; //Set ADC function
/* Step 2. Enable and Select ADC clock source, and then enable ADC
module */
SYSCLK-&gt;CLKSEL1.ADC_S = 2; //Select 22Mhz for ADC
SYSCLK-&gt;CLKDIV.ADC_N = 1; //ADC clock source = 22Mhz/2 =11Mhz;
SYSCLK-&gt;APBCLK.ADC_EN = 1; //Enable clock source
ADC-&gt;ADCR.ADEN = 1; //Enable ADC module
/* Step 3. Select Operation mode */
ADC-&gt;ADCR.DIFFEN = 0; //single end input
ADC-&gt;ADCR.ADMD = 0; //single mode
/* Step 4. Select ADC channel */
ADC-&gt;ADCHER.CHEN = 0x40;
/* Step 5. Enable ADC interrupt */
ADC-&gt;ADSR.ADF =1; //clear the A/D interrupt flags for safe
ADC-&gt;ADCR.ADIE = 1;
//NVIC_EnableIRQ(ADC_IRQn);
/* Step 6. Enable WDT module */
ADC-&gt;ADCR.ADST=1;
}

int main()
{
	char text[20];
	
	UNLOCKREG();
SYSCLK->PWRCON.XTL12M_EN = 1; //Enable 12Mhz and set HCLK-&gt;12Mhz
SYSCLK->CLKSEL0.HCLK_S = 0;
LOCKREG();
	InitADC();

	
			initial_panel();
	clr_all_panel();
	
	while(1)
	{
		while(ADC-&gt;ADSR.ADF==0);
ADC-&gt;ADSR.ADF=1;
///PWMA-&gt;CMR0=ADC- &gt;ADDR[7].RSLT&lt;&lt;4;
		
		sprintf()
		print_lcd()
		DrvSYS_Delay()
		
		ADC-&gt;ADCR.ADST=1;
		}
	}