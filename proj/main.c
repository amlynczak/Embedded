#include"headers.h"

#include "Driver_USART.h"
#include"usart.h"

extern ARM_DRIVER_USART Driver_USART0;

int main(){
	
	static ARM_DRIVER_USART * USARTdrv = &Driver_USART0;
  USART_Init(USARTdrv);
	
	uint32_t returnCode;
	returnCode = SysTick_Config(SystemCoreClock/100);//zmiana mianownika->zmiana czasu delay
	if(returnCode!=0){/*obsluga errorow*/}
	
   lcdConfiguration(); //konfiguracja leda, trzeba wrzucic tak o
	
	touchpanelInit(); //inicjalizacja  touchpada
	
	// ILI9328 jest ukladem sterujacym

	init_ILI9325(); //do tego ukladu cos takiego
	
	
	double tab[4];
	
	
	
	calibrate(tab);
	
	Player player1;
	ustawStatkiRand(&player1);
	drawBoard(&player1.boardPlayer);
	start(tab, USARTdrv);
	//shoot(tab, &player1, USARTdrv);

	/*rysowanie krzyzykow do kalibracji/wyliczenia przelicznika miedzy tp a lcd*/
	

		
	int px = 10; //trzeba bylo cos takiego bo tam krzyczal pozniej
	int py = 10;
	int *x = &px;
	int *y = &py;
	char coor[16];
	//writeString(100, 100, coor, LCDBlack); //wyswietlanie koordynat



    while(1){
		touchpanelGetXY(x, y); //z liba, przekazujemy te wskazniki
		
		//sprintf(coor, "%d , %d", *x, *y);
		//writeString(100, 100, coor, LCDBlack); //wspolzedne
			
		if(calc(*y , tab[0], tab[1]) <= 155 && calc(*y , tab[0], tab[1]) >= 5 && calc(*x , tab[2], tab[3]) <= 315 && calc(*x , tab[2], tab[3]) >= 165){
				//delay(10);
				int result = przelicz(calc(*y , tab[0], tab[1]), calc(*x , tab[2], tab[3]));
				sprintf(coor, "%d", result);
				writeString(100, 100, coor, LCDBlack);

				drawX(result);
			
		}
		USARTdrv->Receive(coor, 2);
		writeString(100, 100, coor, LCDBlack);
			
		//writeString(calc(*y, tab[0], tab[1]), calc(*x, tab[2], tab[3]), "POLSKA", LCDBlack); //x i y sa na odwrot dla tp i lcd, dlatego do X jest y i Y x (chyba)
			//writeString(calcX(*y), calcY(*x), "POLSKA", LCDBlack); //x i y sa na odwrot dla tp i lcd, dlatego do X jest y i Y x (chyba)
		drawRectangle(calc(*y, tab[0], tab[1]), calc(*x, tab[2], tab[3]), calc(*y, tab[0], tab[1]) +2 , calc(*x, tab[2], tab[3]) +2,  LCDBlue);
    }
}
