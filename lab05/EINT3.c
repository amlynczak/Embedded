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
	LPC_GPIOINT->IO0IntClr = 1<<19; //GPIO Interrupt register block->clear interrupt flag = usatwienie 1 na 19 bit
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

    LPC_GPIOINT->IO0IntEnF = 1<<19; //enable interrupts on falling edge - ustawienie 1 na 19 bit
	PIN_Configure(0,19,1,0,0); //port 0, 19 pin, 1 - input, mode, drain
	//EINT3 to GPIO
	NVIC_EnableIRQ(EINT3_IRQn); //enable

    while(1){
        
    }
}