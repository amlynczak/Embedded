#include "string.h"
#include "LPC17xx.h"
#include "PIN_LPC17xx.h"
#include "lcd_lib/Open1768_LCD.h"
#include "lcd_lib/LCD_ILI9325.h"
#include "lcd_lib/asciiLib.h"
#include "tp_lib/TP_Open1768.h"
#include <stdio.h>
#include <math.h>

volatile uint32_t msTicks = 0;

void SysTick_Handler(void){
	msTicks++;
}

void delay(int t){
	msTicks = 0;
	while(msTicks < t);
}

void drawRectangle(int x1, int y1, int x2, int y2, uint16_t color){
	for(int i = x1;i < x2;i++){
		for(int j = y1;j < y2;j++){
			lcdWriteReg(ADRY_RAM,j);
			lcdWriteReg(ADRX_RAM,i);	
			lcdWriteReg(DATA_RAM,color);
		}	
	}
}

void drawBoard(){
		lcdConfiguration();
		drawRectangle(0, 0, 240, 320, LCDWhite);
	
	/* obrys*/
		drawRectangle(5, 5, 155, 155, LCDBlack);
		drawRectangle(6, 6, 154, 154, LCDWhite);
	
		drawRectangle(5, 165, 155, 315, LCDBlack);
		drawRectangle(6, 166, 154, 314, LCDWhite);
	
	/* linie pionowe*/
		drawRectangle(5, 34, 155, 35, LCDBlack);
		drawRectangle(5, 64, 155, 65, LCDBlack);
		drawRectangle(5, 94, 155, 95, LCDBlack);
		drawRectangle(5, 124, 155, 125, LCDBlack);
	
		drawRectangle(5, 194, 155, 195, LCDBlack);
		drawRectangle(5, 224, 155, 225, LCDBlack);
		drawRectangle(5, 254, 155, 255, LCDBlack);
		drawRectangle(5, 284, 155, 285, LCDBlack);
	
	/*linie poziome*/
		drawRectangle(34, 5, 35, 155, LCDBlack);
		drawRectangle(64, 5, 65, 155, LCDBlack);
		drawRectangle(94, 5, 95, 155, LCDBlack);
		drawRectangle(124, 5, 125, 155, LCDBlack);
		
		drawRectangle(34, 165, 35, 315, LCDBlack);
		drawRectangle(64, 165, 65, 315, LCDBlack);
		drawRectangle(94, 165, 95, 315, LCDBlack);
		drawRectangle(124, 165, 125, 315, LCDBlack);
		
		
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

void calibrate(double *arr){
	int px1 = 4095;
	int py1 = 0;
	int px2 = 4095;
	int py2 = 0;
	int px3 = 4095;
	int py3 = 0;
	int *x1 = &px1, *y1 = &py1;
	int *x2 = &px2, *y2 = &py2;
	int *x3 = &px3, *y3 = &py3;


	
	
	char coor[16];
	/*rysowanie krzyzykow do kalibracji/wyliczenia przelicznika miedzy tp a lcd*/
	drawRectangle(0, 0, 240, 320, LCDWhite);
	//lewy dolny
	drawRectangle(20, 11, 21, 30, LCDBlack);
	drawRectangle(11, 20, 30, 21, LCDBlack);
	
			
	
	while(1){
		touchpanelGetXY(x1, y1);
		sprintf(coor, "%d , %d", *x1, *y1);
		writeString(100, 100, coor, LCDBlack);
		if(*x1<4000 && *y1 > 200){
			break;
		}
	}
	delay(100);

	//lewy gorny
	drawRectangle(0, 0, 240, 320, LCDWhite);
	drawRectangle(219, 10, 220, 30, LCDBlack);
	drawRectangle(210, 20, 229, 21, LCDBlack);
	
	while(1){
		touchpanelGetXY(x2, y2);
		sprintf(coor, "%d , %d", *x2, *y2);
		writeString(100, 100, coor, LCDBlack);
		if(*x2<4095 && *y2 > 200){
			break;
		}
	}
	delay(100);
		
	//prawy dolny
	drawRectangle(0, 0, 240, 320, LCDWhite);
	drawRectangle(20, 290, 21, 309, LCDBlack);
	drawRectangle(11, 300, 30, 301, LCDBlack);
	
	while(1){
		touchpanelGetXY(x3, y3);
		sprintf(coor, "%d , %d", *x3, *y3);
		writeString(100, 100, coor, LCDBlack);
		if(*x3<4000 && *y3 > 200){
			break;
		}
	}
	delay(100);
	
	double a1 = 200.0/ (*y2 -*y1);
	double b1 = 20.0 - a1*(*y1);
	int a2mian = *x3 - *x1;
	double a2 = 280.0/(a2mian);
	double b2 = 20.0 - a2*(*x1);
	
	arr[0] = a1;
	arr[1] = b1;
	arr[2] = a2;
	arr[3] = b2;
	
	sprintf(coor, "%d , %d", (int)((a1)*1000), (int)((b1)*1000));
	writeString(100, 100, coor, LCDBlack);
	
	sprintf(coor, "%d , %d", (int)((a2)*1000), (int)((b2)*1000));
	writeString(200, 200, coor, LCDBlack);
	
	delay(100);
}





int calcX(int x){
	return (int)(0.0667 * (double)x - 17.16);
}

int calcY(int y){
	return (int)(0.0885 * (double)y - 12.71);
}

int calc(int xy, double a, double b){
	return (int)(a*(double)xy - b);
}

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
