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
	GPIOA->OFFD|=0x00400000; 	//Disable digital input path
	SYS->GPAMFP.ADC7_SS21_AD6=1; 		//Set ADC function 
				
	/* Step 2. Enable and Select ADC clock source, and then enable ADC module */          
	SYSCLK->CLKSEL1.ADC_S = 2;	//Select 22Mhz for ADC
	SYSCLK->CLKDIV.ADC_N = 1;	//ADC clock source = 22Mhz/2 =11Mhz;
	SYSCLK->APBCLK.ADC_EN = 1;	//Enable clock source
	ADC->ADCR.ADEN = 1;			//Enable ADC module

	/* Step 3. Select Operation mode */
	ADC->ADCR.DIFFEN = 0;     	//single end input
	ADC->ADCR.ADMD   = 0;     	//single mode
		
	/* Step 4. Select ADC channel */
	ADC->ADCHER.CHEN = 0x40;
	
	/* Step 5. Enable ADC interrupt */
	ADC->ADSR.ADF =1;     		//clear the A/D interrupt flags for safe 
	ADC->ADCR.ADIE = 1;
	//NVIC_EnableIRQ(ADC_IRQn);
	
	/* Step 6. Enable WDT module */
	ADC->ADCR.ADST=1;
}

void InitPWM1(void)
{
 	/* Step 1. GPIO initial */ 
	SYS->GPAMFP.PWM1_AD14=1;
				
	/* Step 2. Enable and Select PWM clock source*/		
	SYSCLK->APBCLK.PWM01_EN = 1;//Enable PWM clock
	SYSCLK->CLKSEL1.PWM01_S = 0;//Select 22.1184Mhz for PWM clock source

	PWMA->PPR.CP01=11;			//Prescaler 0~255, Setting 0 to stop output clock
	PWMA->CSR.CSR1=0;			// PWM clock = clock source/(Prescaler + 1)/divider
				         
	/* Step 3. Select PWM Operation mode */
	//PWM0
	PWMA->PCR.CH1MOD=1;			//0:One-shot mode, 1:Auto-load mode
	//CNR and CMR will be auto-cleared after setting CH0MOD form 0 to 1.

	PWMA->CNR1=0xFFFF;
	PWMA->CMR1=0x3FFF;

	PWMA->PCR.CH1INV=0;			//Inverter->0:off, 1:on
	PWMA->PCR.CH1EN=1;			//PWM function->0:Disable, 1:Enable
 	PWMA->POE.PWM1=1;			//Output to pin->0:Diasble, 1:Enable
}


int main()
{
	char text[20];
	
	UNLOCKREG();
SYSCLK->PWRCON.XTL12M_EN = 1; //Enable 12Mhz and set HCLK-&gt;12Mhz
SYSCLK->CLKSEL0.HCLK_S = 0;
LOCKREG();
	InitADC();
	InitPWM1();
	
			initial_panel();
	clr_all_panel();
	
	while(1)
	{
		while(ADC->ADSR.ADF==0);
ADC->ADSR.ADF=1;
PWMA->CMR1=ADC->ADDR[6].RSLT<<4;
		sprintf(text,"ADC_value:%d",ADC->ADDR[6].RSLT);
		print_lcd(1,text);
		
		DrvSYS_Delay(2000);
		ADC->ADCR.ADCT=1;
		
		
		}
	}