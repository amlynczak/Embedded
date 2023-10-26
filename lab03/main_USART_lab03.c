#include "Driver_USART.h"
#include "string.h"
#include "LPC17xx.h"

/* USART Driver */
extern ARM_DRIVER_USART Driver_USART0;
volatile uint32_t msTicks = 0;

void SysTick_Handler(void){
	msTicks++;
}

void delay(int t){
	msTicks = 0;
	while(msTicks < t);
}//delay taki sam jak lab01

int main(){
	uint32_t returnCode;
	returnCode = SysTick_Config(SystemCoreClock/100);
	
	char *text0 = "USART0 tekst dluzszy";
	
	PIN_Configure(0, 2, 1, 2, 0);
	PIN_Configure(0, 3, 1, 2, 0); //konfiguracja (port, pin(tx/rx?), )
		
	LPC_UART0->LCR = 3 | (1<<7); //pierwsze dwa bity - ilu bitowy lenght character (5-8), stop bit select, parity enable, parity select, break ctrl, DLAB
	LPC_UART0->DLL = 27; //Divisor Latch LSB register - najmlodsze bity
	LPC_UART0->DLM = 0; //najstarsze bity - ustala sie DL (tam przy wyznaczaniu B = f/16DL(1+A/B))
	LPC_UART0->LCR = 3;
		
	while(1){
		int len = strlen(text0);
		for(int i=0; i<len; i++){
			char tmp = text0[i];
			LPC_UART0->THR = tmp;//NIE TESTOWANE NA PLYTCE ale jest szansa ze to akurat bedzie dzialalo
		}
		delay(10);
	}
}
