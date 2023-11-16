#include "Driver_USART.h"
#include "string.h"
#include "LPC17xx.h"
#include "PIN_LPC17xx.h"

/* USART Driver */
extern ARM_DRIVER_USART Driver_USART0;

void TIMER0_IRQHandler(void){
	const char* napis = "ping\n";
    LPC_TIM0->IR |= 1 << 0;
	for(int i=0; i< sizeof(napis); i++){
	    if(LPC_UART0->LSR >> 6 == 1){ //sprawdzenie czy FIFO jest puste (dla 1 jest pusty i mozna przeslac kolejna litere)
			LPC_UART0->THR = napis[i];
		}else{
			i--; //cofamy wskaznik na wczesniejszy i staramy sie wyslac w nastepnym wykonaniu petli for
		}
	}
}

int main(){
	/*KONFIGURACJA USART*/
	PIN_Configure(0, 2, 1, 2, 0);
	PIN_Configure(0, 3, 1, 2, 0);

	LPC_UART0->LCR = 3 | (1<<7);
	LPC_UART0->DLL = 27;
	LPC_UART0->DLM = 0;
	LPC_UART0->LCR = 3;
	/*USART koniec - to samo co ostatnio*/
	
	LPC_TIM0->PR = 0; //ustawienie Prescaler Register - podzial czestotliwosci zegara wyjsciowego timera
	LPC_TIM0->MR0 = 12500000; //Match Register 0 - gorna granica licznika timera
	
	LPC_TIM0->MCR = 0 | (1<<0) | (1<<1); //Match Cotrol Register - co ma sie dziac po wykryciu warunku dopasowania (dokumentacja)
	
	LPC_TIM0->TCR = 1; //Timer Control Register - ustawienie 1 na 1. bit (uruchomienie)
	
	NVIC_EnableIRQ(TIMER0_IRQn); // wlaczenie przerwan dla TIMER0 - z uzyciem TIMER0_IRQn
}