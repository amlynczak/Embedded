#include"lcd.h"

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