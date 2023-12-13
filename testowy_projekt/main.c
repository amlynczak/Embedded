#include"headers.h"

int main(){
	uint32_t returnCode;
	returnCode = SysTick_Config(SystemCoreClock/100);//zmiana mianownika->zmiana czasu delay
	if(returnCode!=0){/*obsluga errorow*/}
	
    lcdConfiguration(); //konfiguracja leda, trzeba wrzucic tak o
	
	touchpanelInit(); //inicjalizacja  touchpada
	
	// ILI9328 jest ukladem sterujacym

	init_ILI9325(); //do tego ukladu cos takiego
	
	
	double tab[4];
	
	calibrate(tab);
	drawBoard();

	/*rysowanie krzyzykow do kalibracji/wyliczenia przelicznika miedzy tp a lcd*/
	

		
	int px = 10; //trzeba bylo cos takiego bo tam krzyczal pozniej
	int py = 10;
	int *x = &px;
	int *y = &py;
	char coor[16];
	//writeString(100, 100, coor, LCDBlack); //wyswietlanie koordynat

    while(1){
		touchpanelGetXY(x, y); //z liba, przekazujemy te wskazniki
		
		sprintf(coor, "%d , %d", *x, *y);
		writeString(100, 100, coor, LCDBlack); //wspolzedne
			
		writeString(calc(*y, tab[0], tab[1]), calc(*x, tab[2], tab[3]), "POLSKA", LCDBlack); //x i y sa na odwrot dla tp i lcd, dlatego do X jest y i Y x (chyba)
			//writeString(calcX(*y), calcY(*x), "POLSKA", LCDBlack); //x i y sa na odwrot dla tp i lcd, dlatego do X jest y i Y x (chyba)
    }
}
