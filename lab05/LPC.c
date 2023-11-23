#include "Driver_USART.h"
#include "string.h"
#include "LPC17xx.h"
#include "PIN_LPC17xx.h"
#include "Board_LED.h"
#include "lcd_lib/Open1768_LCD.h"
#include "lcd_lib/LCD_ILI9325.h"

void drawRectangle(int x1, int y1, int x2, int y2){
	for(int i = x1;i < x2;i++){
		for(int j = y1;j < y2;j++){
			lcdWriteReg(ADRY_RAM,j);
			lcdWriteReg(ADRX_RAM,i);	
			lcdWriteReg(DATA_RAM,LCDBlack);
		}	
	}
}

int main(){
    lcdConfiguration(); //konfiguracja leda, trzeba wrzucic tak o
	
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

    while(1){
        
    }
}