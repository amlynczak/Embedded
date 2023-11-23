#include "Driver_USART.h"
#include "string.h"
#include "LPC17xx.h"
#include "PIN_LPC17xx.h"
#include "Board_LED.h"

/* USART Driver */
extern ARM_DRIVER_USART Driver_USART0;

volatile uint32_t msTicks = 0;

void SysTick_Handler(void){
	msTicks++;
}//do czasu martwego (tam zeby nie lapal dwa razy klikniecia)

void EINT0_IRQHandler(void){
	static bool cl = true; 
	if(msTicks > 25){ // jakas wartosc "oczekiwania"
		const char* napis = "Click";
		for(int i=0; i< strlen(napis); i++){
			if(LPC_UART0->LSR >> 6 == 1){
				LPC_UART0->THR = napis[i];
			}else{
				i--; 
			}
		}
		
		if(cl){
			LED_On(0);
		}else{
			LED_Off(0);
		}
		cl = !cl;
		
		msTicks = 0; //wyzerowanie aby msTicks bylo do nowa
	}
	LPC_SC->EXTINT = (1<<0); //System Control -> control external interrupts = 1 na zerowy bit - clear the interrupt flag
}

int main(){
    uint32_t returnCode;
	returnCode = SysTick_Config(SystemCoreClock/100);

    /*KONFIGURACJA USART*/
    PIN_Configure(0, 2, 1, 2, 0);
    PIN_Configure(0, 3, 1, 2, 0);

    LPC_UART0->LCR = 3 | (1<<7);
	LPC_UART0->DLL = 27;
	LPC_UART0->DLM = 0;
	LPC_UART0->LCR = 3;
	/*USART koniec - to samo*/

    LPC_SC->EXTMODE = (1<<0); //External interrupt sensing mode - ustawienie edge-sensitive
	LPC_SC->EXTPOLAR = 0; //polarity of the external interrupt - falling edge
	PIN_Configure(2,10,1,0,0); //do uzycia EINT0 - 2 port, 10 pin, function 1 - input, mode i drain?
	
	NVIC_EnableIRQ(EINT0_IRQn); // enable

    while(1){
        
    }
}