#include "string.h"
#include "LPC17xx.h"
#include "PIN_LPC17xx.h"
#include "lcd_lib/Open1768_LCD.h"
#include "lcd_lib/LCD_ILI9325.h"
#include "lcd_lib/asciiLib.h"
#include "tp_lib/TP_Open1768.h"
#include <stdio.h>

void drawRectangle(int x1, int y1, int x2, int y2){
	for(int i = x1;i < x2;i++){
		for(int j = y1;j < y2;j++){
			lcdWriteReg(ADRY_RAM,j);
			lcdWriteReg(ADRX_RAM,i);	
			lcdWriteReg(DATA_RAM,LCDBlack);
		}	
	}
}

void writeSign(int x_0, int y_0, unsigned char sign, uint16_t color){
	unsigned char tab[16]; //tablica 'pikseli' - w jedym char jest 8 pikesli w szesnastkowym
		
	GetASCIICode(0, tab, sign); //funkcja z biblkoteki
		
	for(int i=0; i<16; i++){
		for(int j=0; j<8; j++){
			lcdWriteReg(ADRY_RAM, y_0 + (8-j));
			lcdWriteReg(ADRX_RAM, x_0 + (16-i));
			unsigned char tmp = tab[i];
			if(tmp>>j & 1){ //sprawdzenie czy j-ty bit jest 1 
				lcdWriteReg(DATA_RAM, color);
			}else{
				lcdWriteReg(DATA_RAM, LCDWhite); //mozna wylaczyc ale wtedy sie moga litery nakladac
			}
		}
	}
}

void writeString(int x_0, int y_0, char* napis, uint16_t color){
	int x = x_0;
	int y = y_0;
	for(int i=0; i<strlen(napis); i++){
		writeSign(x, y, napis[i], color);
		y = y+10; //przesuniece gdzie zaczac nastepna litere, 9 by tez siadlo
	}
}

int calcX(int x){
	return (int)(0.0667 * (double)x - 17.16);
}

int calcY(int y){
	return (int)(0.0885 * (double)y - 12.71);
}

int main(){
    lcdConfiguration(); //konfiguracja leda, trzeba wrzucic tak o
	
	touchpanelInit(); //inicjalizacja  touchpada
	
	// ILI9328 jest ukladem sterujacym

	init_ILI9325(); //do tego ukladu cos takiego

	for(int i = 0;i < 120;i++){
		for(int j = 0;j < 320;j++){
			lcdWriteReg(ADRY_RAM,j);
			lcdWriteReg(ADRX_RAM,i);	
			lcdWriteReg(DATA_RAM,LCDRed);
		}
    }
	for(int i = 120;i < 240;i++){
		for(int j = 0;j < 320;j++){
			lcdWriteReg(ADRY_RAM,j);
			lcdWriteReg(ADRX_RAM,i);	
			lcdWriteReg(DATA_RAM,LCDWhite);
		}
    }//polska gurom

	/*rysowanie krzyzykow do kalibracji/wyliczenia przelicznika miedzy tp a lcd*/
	
	//lewy dolny
	drawRectangle(20, 11, 21, 30);
	drawRectangle(11, 20, 30, 21);

	//lewy gorny
	drawRectangle(219, 10, 220, 30);
	drawRectangle(210, 20, 229, 21);

		
	//prawy dolny
	drawRectangle(20, 290, 21, 309);
	drawRectangle(11, 300, 30, 301);
		
	int px = 10; //trzeba bylo cos takiego bo tam krzyczal pozniej
	int py = 10;
	int *x = &px;
	int *y = &py;
	char coor[16];
	writeString(100, 100, coor, LCDBlack); //wyswietlanie koordynat

    while(1){
		touchpanelGetXY(x, y); //z liba, przekazujemy te wskazniki
		
		sprintf(coor, "%d , %d", *x, *y);
		writeString(100, 100, coor, LCDBlack); //wspolzedne
			
		writeString(calcX(*y), calcY(*x), "POLSKA", LCDBlack); //x i y sa na odwrot dla tp i lcd, dlatego do X jest y i Y x (chyba)
    }
}
