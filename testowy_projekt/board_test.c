#include"board_test.h"

void drawBoard(){
	lcdConfiguration();
	drawRectangle(0, 0, 240, 320, LCDWhite);
	
	/* obrys*/
	drawRectangle(5, 5, 155, 155, LCDBlack);
	drawRectangle(6, 6, 154, 154, LCDWhite);
	
	drawRectangle(5, 165, 155, 315, LCDBlack);
	drawRectangle(6, 166, 154, 314, LCDWhite);
	
	/* linie pionowe*/
    writeSign(157, 16, 'A'); //dodane opisy pol - od A do E na kolumnach
	drawRectangle(5, 34, 155, 35, LCDBlack);
    writeSign(157, 46, 'B');
	drawRectangle(5, 64, 155, 65, LCDBlack);
    writeSign(157, 76, 'C');
	drawRectangle(5, 94, 155, 95, LCDBlack);
    writeSign(157, 106, 'D');
	drawRectangle(5, 124, 155, 125, LCDBlack);
    writeSign(157, 136, 'E');

    writeSign(157, 176, 'A');
	drawRectangle(5, 194, 155, 195, LCDBlack);
    writeSign(157, 206, 'B');
	drawRectangle(5, 224, 155, 225, LCDBlack);
    writeSign(157, 236, 'C');
	drawRectangle(5, 254, 155, 255, LCDBlack);
    writeSign(157, 266, 'D');
	drawRectangle(5, 284, 155, 285, LCDBlack);
    writeSign(157, 296, 'E');
	
	/*linie poziome*/
	writeSign(12, 157, '5'); //i dodane od 1 do 5 na wierszach
	drawRectangle(34, 5, 35, 155, LCDBlack);
	writeSign(42, 157, '4');
	drawRectangle(64, 5, 65, 155, LCDBlack);
	writeSign(72, 157, '3');
	drawRectangle(94, 5, 95, 155, LCDBlack);
	writeSign(102, 157, '2');
	drawRectangle(124, 5, 125, 155, LCDBlack);
	writeSign(132, 157, '1');
		
	drawRectangle(34, 165, 35, 315, LCDBlack);
	drawRectangle(64, 165, 65, 315, LCDBlack);
	drawRectangle(94, 165, 95, 315, LCDBlack);
	drawRectangle(124, 165, 125, 315, LCDBlack);
}

int przelicz(int x, int y){
    int coordinates = 0; //skonstruowane tak, ze liczba dziesiatek to kolumny, liczba jednosci to wiersze
    if(x>=5 && x<35){
        coordinates += 5;
    }
    if(x>=35 && x<65){
        coordinates += 4;
    }
    if(x>=65 && x<95){
        coordinates += 3;
    }
    if(x>=95 && x<125){
        coordinates += 2;
    }
    if(x>=125 && x<=155){
        coordinates += 1;
    }

    if(y>=165 && y<195){
        coordinates += 10;
    }
    if(y>=195 && y<225){
        coordinates += 20;
    }
    if(y>=225 && y<255){
        coordinates += 30;
    }
    if(y>=255 && y<285){
        coordinates += 40;
    }
    if(y>=285 && y<=315){
        coordinates += 50;
    }

    return coordinates;
}