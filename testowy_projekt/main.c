#include "usart.h"
#include "lcd.h"
#include "game.h"

int main(){
	
	static ARM_DRIVER_USART * USARTdrv = &Driver_USART0;
  USART_Init(USARTdrv);
	
	uint32_t returnCode;
	returnCode = SysTick_Config(SystemCoreClock/100);
	if(returnCode!=0){}
	
  lcdConfiguration();
	
	touchpanelInit();
	init_ILI9325();
	
	float tab[4]; //coordinates
	
	calibrate(tab);
	
	Player player1;
	player1.win = false;
	for(int i=0; i<3; i++){
		player1.ships[i].hits = 0;
		player1.ships[i].zatopiony = false;
		player1.ships[i].size = 3-i;
	}
	ustawStatkiRand(&player1);
	drawBoard(&player1.boardPlayer);
	start(tab, USARTdrv);
	bool gameOn = false;
	
	while(1){
		gameOn = shoot(tab, &player1, USARTdrv);
		if(gameOn) break;
	}
	
	end(&player1, tab, USARTdrv);
}
