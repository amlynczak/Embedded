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
}

void print(const char *napis){
	for(int i=0; i< strlen(napis); i++){
		if(LPC_UART0->LSR >> 6 == 1){ //sprawdzenie czy FIFO jest puste (dla 1 jest pusty i mozna przeslac kolejna litere)
			LPC_UART0->THR = napis[i];
		}else{
			i--; //cofamy wskaznik na wczesniejszy i staramy sie wyslac w nastepnym wykonaniu petli for
		}
	}
}

void TIMER0_IRQHandler(void){
	const char* napis = "ping";
    LPC_TIM0->IR |= 1 << 0;
	for(int i=0; i< sizeof(napis); i++){
	    if(LPC_UART0->LSR >> 6 == 1){
			LPC_UART0->THR = napis[i];
		}else{
			i--;
		}
	}
}

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
		if(LPC_UART0->LSR >> 6 == 1){
			LPC_UART0->THR = napis[i];
		}else{
			i--;
		}
	}
	LPC_RTC->ILR = 1;
	flag = !flag;
}

void EINT0_IRQHandler(void){
	static bool cl = true;
	if(msTicks > 25){
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
		
		msTicks = 0;
	}
	LPC_SC->EXTINT = (1<<0);
}

void EINT3_IRQHandler(void){
const char* napis = "bang";
	if(msTicks > 25){
		for(int i=0; i< sizeof(napis); i++){
				if(LPC_UART0->LSR >> 6 == 1){
				LPC_UART0->THR = napis[i];
			}else{
				i--;
			}
		}
		msTicks = 0;
	}
	LPC_GPIOINT->IO0IntClr = 1<<19;
}

int main(){
	LED_Initialize();
	LED_SetOut(0);
	LED_Off(0);
	LED_Off(1);
	LED_Off(2);
	LED_Off(3);
	
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

	///////////TIMER0/////////////////////////////////////
	LPC_TIM0->PR = 0; //ustawienie Prescaler Register - podzial czestotliwosci zegara wyjsciowego timera
	LPC_TIM0->MR0 = 12500000; //Match Register 0 - gorna granica licznika timera
	
	LPC_TIM0->MCR = 0 | (1<<0) | (1<<1); //Match Cotrol Register - co ma sie dziac po wykryciu warunku dopasowania (dokumentacja)
	
	LPC_TIM0->TCR = 1; //Timer Control Register - ustawienie 1 na 1. bit (uruchomienie)
	
	NVIC_EnableIRQ(TIMER0_IRQn);

	///////////RTC//////////////////////////////////////
	LPC_RTC->CCR = 1; //wlaczenie zegara RTC - Control Register
	LPC_RTC->ILR = 1; //Interrupt Location Register - kontrola flagi przerwan RTC
	LPC_RTC->CIIR = 1; //Counter Increment Interrupt Register - kontrola zdarzen RTC(co powoduje przerwanie itd.)

  	NVIC_EnableIRQ(RTC_IRQn);
	
	///////////EINT0////////////////////////////////
	LPC_SC->EXTMODE = (1<<0);
	LPC_SC->EXTPOLAR = 0;
	PIN_Configure(2,10,1,0,0);
	
	NVIC_EnableIRQ(EINT0_IRQn);

	///////////EINT3///////////////////////////////////////
	LPC_GPIOINT->IO0IntEnF = 1<<19;
	PIN_Configure(0,19,1,0,0); 
	//EINT3 to GPIO
	NVIC_EnableIRQ(EINT3_IRQn);
    
	while(1){
		
	}
	LED_Uninitialize();
}