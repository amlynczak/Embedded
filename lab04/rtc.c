#include "Driver_USART.h"
#include "string.h"
#include "LPC17xx.h"
#include "PIN_LPC17xx.h"

/* USART Driver */
extern ARM_DRIVER_USART Driver_USART0;

void RTC_IRQHandler(void){
	const char* napis1 = "TIK";
	const char* napis2 = "TAK";
	const char* napis;
	static bool flag = true;

	if(flag){
        napis = napis1;
    }else{
        napis = napis2;
    }
	
	for(int i=0; i< sizeof(napis); i++){
		if(LPC_UART0->LSR >> 6 == 1){ //sprawdzenie czy FIFO jest puste (dla 1 jest pusty i mozna przeslac kolejna litere)
			LPC_UART0->THR = napis[i];
		}else{
			i--; //cofamy wskaznik na wczesniejszy i staramy sie wyslac w nastepnym wykonaniu petli for
		}
	}

	LPC_RTC->ILR = 1;
	flag = !flag;
}

int main(){
    /*KONFIGURACJA USART*/
    PIN_Configure(0, 2, 1, 2, 0);
	PIN_Configure(0, 3, 1, 2, 0);

	LPC_UART0->LCR = 3 | (1<<7);
	LPC_UART0->DLL = 27;
	LPC_UART0->DLM = 0;
	LPC_UART0->LCR = 3;
	/*USART koniec - to samo*/

    LPC_RTC->CCR = 1; //wlaczenie zegara RTC - Control Register
	LPC_RTC->ILR = 1; //Interrupt Location Register - kontrola flagi przerwan RTC
	LPC_RTC->CIIR = 1; //Counter Increment Interrupt Register - kontrola zdarzen RTC(co powoduje przerwanie itd.)

    NVIC_EnableIRQ(RTC_IRQn); //wlaczenie przerwan dal RTC

while(1){
	
}
}
