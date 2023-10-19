#include "Board_LED.h"
#include "Board_Buttons.h"
#include "Board_Joystick.h"
#include "LPC17xx.h" //do dobrego delaya

volatile uint32_t msTicks = 0;

void SysTick_Handler(void){
	msTicks++;
}//wywoluje sie samo

void delay(int t){
	msTicks = 0;
	while(msTicks < t);
}

void ledy(int n){
	int i = 0;
	int j = 0;
	while(i < n){
		LED_Off(1);
		LED_Off(2);
		LED_Off(3);
		LED_On(0);
		delay(j+=10);
		LED_On(1);
		LED_Off(0);
		delay(j+=10);
		LED_On(2);
		LED_Off(1);
		delay(j+=10);
		LED_On(3);
		LED_Off(2);
		delay(j+=10);
		i++;
	}
	LED_Off(3);
}//ta sekwencja ze sie po kolei zaswiecaja

void singleLedJoystick(int n){	
	if(n==1){
		LED_On(1);
	}
	if(n==2){
		LED_On(2);
	}
	if(n==8){
		LED_On(0);
	}
	if(n==16){
		LED_On(3);
	}
	if(n==4 || n==0){
		LED_Off(0);
		LED_Off(1);
		LED_Off(2);
		LED_Off(3);
	}
}//zapalanie ledow kontrolujac joystickiem


int main(){
	uint32_t returnCode;
	returnCode = SysTick_Config(SystemCoreClock/100);//zmiana mianownika->zmiana czasu delay
	if(returnCode!=0){/*obsluga errorow*/}
	LED_Initialize();
	LED_Off(0);
	LED_Off(1);
	LED_Off(2);
	LED_Off(3);
	Joystick_Initialize();
	
	while(1){
		if(Buttons_GetState() == 1){
			ledy(Buttons_GetState());
		}else if(Buttons_GetState() == 2){
			ledy(Buttons_GetState());
		}else if(Joystick_GetState()){
			singleLedJoystick(Joystick_GetState());
		}
	}
	
	LED_Uninitialize();
	Joystick_Uninitialize();
}
