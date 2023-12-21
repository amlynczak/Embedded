#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include "usart.h"
#include "game.h"
#include"delay.h"

#include<stdlib.h>

bool isLegal(int x, int y, Board *b){
	if(b->sqares[x][y] == 1){
			return false;
	}
	
	for(int i=x-1; i<=x+1; i++){
		for(int j=y-1; j<=y+1; j++){
			if(i>=0 && i<=5 && j>=0 && j<=5){
				if(i != x || j!= y){
					if(b->sqares[i][j] == 1){
						return false;
					}
				}
			}
		}
	}
	return true;
}

int przelicz(int x, int y){
    int coordinates = 0; //skonstruowane tak, ze liczba dziesiatek to kolumny, liczba jednosci to wiersze
		for(int i=0; i<5; i++){
			if(x>= 5 + 30 * i && x< 5 + 30 * (i+1)){
				coordinates += (5-i);
			}
		}
		
		for(int i=0; i<5; i++){
			if(y>= 165 + 30 * i && y< 165 + 30 * (i+1)){
				coordinates += 10 * (i+1);
			}
		}

    return coordinates;
}

void ustawStatkiRand(Player *p){
	
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			p->boardPlayer.sqares[i][j] = 0; 
		}
	}

	int randX = rand()%3;
	int randY = rand()%5;
	
	p->boardPlayer.sqares[randX][randY] = 1;
	p->boardPlayer.sqares[randX+1][randY] = 1;
	p->boardPlayer.sqares[randX+2][randY] = 1;
	
	do{
		randX = rand()%4;
		randY = rand()%5;
	}while(!isLegal(randX, randY, &p->boardPlayer) && !isLegal(randX+1, randY, &p->boardPlayer));
	
	p->boardPlayer.sqares[randX][randY] = 1;
	p->boardPlayer.sqares[randX+1][randY] = 1;
	
	do{
		randX = rand()%5;
		randY = rand()%5;
	}while(!isLegal(randX, randY, &p->boardPlayer));
	
	p->boardPlayer.sqares[randX][randY] = 1;
	
}

void start(double *tab, ARM_DRIVER_USART * USARTdrv){

	drawRectangle(190,95, 220, 225, LCDBlack);
	drawRectangle(191,96,219,224,LCDWhite);
	writeString(196, 135, "READY", LCDBlack);
	
	int px = 10; //trzeba bylo cos takiego bo tam krzyczal pozniej
	int py = 10;
	int *x = &px;
	int *y = &py;
	char text[2];
	
	while(1){
		touchpanelGetXY(x, y);
		if(calc(*y , tab[0], tab[1]) < 220 && calc(*y , tab[0], tab[1]) > 190 && calc(*x , tab[2], tab[3]) > 95 && calc(*x , tab[2], tab[3]) < 225){
			startFlag = true;
			USARTdrv->Send("R", 1);
			break;
		}
			USARTdrv->Receive(text, 1);
			if(!strcmp(text, "R")){
				startFlag = false;
				break;
		}
	}
	drawRectangle(190,95, 220, 225, LCDWhite);
}

void shoot(double *tab, Player *player, ARM_DRIVER_USART * USARTdrv){
	int px = 0; //trzeba bylo cos takiego bo tam krzyczal pozniej
	int py = 0;
	int *x = &px;
	int *y = &py;
	int result = 0;
	char coor[2];
	char *info;
	
	if(startFlag){
		while(1){
			touchpanelGetXY(x, y); //z liba, przekazujemy te wskazniki
			
			if(calc(*y , tab[0], tab[1]) <= 155 && calc(*y , tab[0], tab[1]) >= 5 && calc(*x , tab[2], tab[3]) <= 315 && calc(*x , tab[2], tab[3]) >= 165){
					delay(10);
					result = przelicz(calc(*y , tab[0], tab[1]), calc(*x , tab[2], tab[3]));
					sprintf(coor, "%d", result);
					USARTdrv->Send(coor, 2);
					break;
			}	
    }
	}else{
		while(1){
			USARTdrv->Receive(coor, 2);
			result = atoi(coor);
			if(result > 0) break;
	}
		
	if(!startFlag){
		int x = result/10;
		int y = result - x*10;
		
		if(player->boardPlayer.sqares[x][y] == 1){
			USARTdrv->Send("h", 1);
		}else{
			USARTdrv->Send("m", 1);
			startFlag = !startFlag;
		}
	}else{
		while(1){
			USARTdrv->Receive(info, 1);
			if(*info == 'h' && *info == 'm') break;
		}
		writeSign(100, 100, *info, LCDBlack);
		
		
	}
		
		writeString(100, 100, coor, LCDBlack);
	}
}

//z board

void drawBoard(Board *board){
	lcdConfiguration();
	drawRectangle(0, 0, 240, 320, LCDWhite);
	
	/* obrys*/
	drawRectangle(5, 5, 155, 155, LCDBlack);
	drawRectangle(6, 6, 154, 154, LCDWhite);
	
	drawRectangle(5, 165, 155, 315, LCDBlack);
	drawRectangle(6, 166, 154, 314, LCDWhite);
	
	/* linie pionowe*/
    writeSign(157, 16, 'A', LCDBlack); //dodane opisy pol - od A do E na kolumnach
	drawRectangle(5, 34, 155, 35, LCDBlack);
    writeSign(157, 46, 'B', LCDBlack);
	drawRectangle(5, 64, 155, 65, LCDBlack);
    writeSign(157, 76, 'C', LCDBlack);
	drawRectangle(5, 94, 155, 95, LCDBlack);
    writeSign(157, 106, 'D', LCDBlack);
	drawRectangle(5, 124, 155, 125, LCDBlack);
    writeSign(157, 136, 'E', LCDBlack);

    writeSign(157, 176, 'A', LCDBlack);
	drawRectangle(5, 194, 155, 195, LCDBlack);
    writeSign(157, 206, 'B', LCDBlack);
	drawRectangle(5, 224, 155, 225, LCDBlack);
    writeSign(157, 236, 'C', LCDBlack);
	drawRectangle(5, 254, 155, 255, LCDBlack);
    writeSign(157, 266, 'D', LCDBlack);
	drawRectangle(5, 284, 155, 285, LCDBlack);
    writeSign(157, 296, 'E', LCDBlack);
	
	/*linie poziome*/
	writeSign(12, 156, '5', LCDBlack); //i dodane od 1 do 5 na wierszach
	drawRectangle(34, 5, 35, 155, LCDBlack);
	writeSign(42, 156, '4', LCDBlack);
	drawRectangle(64, 5, 65, 155, LCDBlack);
	writeSign(72, 156, '3', LCDBlack);
	drawRectangle(94, 5, 95, 155, LCDBlack);
	writeSign(102, 156, '2', LCDBlack);
	drawRectangle(124, 5, 125, 155, LCDBlack);
	writeSign(132, 156, '1', LCDBlack);
		
	drawRectangle(34, 165, 35, 315, LCDBlack);
	drawRectangle(64, 165, 65, 315, LCDBlack);
	drawRectangle(94, 165, 95, 315, LCDBlack);
	drawRectangle(124, 165, 125, 315, LCDBlack);
	
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			if(board->sqares[i][j] == 1){
				drawRectangle(7+30*i, 7+30*j, 2+30*(i+1), 2+30*(j+1), LCDGrey);
			}
		}
	}
}



void drawX(int xy){
	int x = (xy)/10;
	int y = xy - y;
	
	int x_0, y_0, x_1, y_1;
	
	x_0 = 5 + 30 * (x-1);
	y_0 = 165 + 30 * (y-1);
	
	x_1 = 5 + 30 * x;
	y_1 = 165 + 30 * y;
	
	for(int i=x_0; i<x_1; i++){
		for(int j=y_0; j<y_1; j++){
			if(i==j){
				drawRectangle(j-1,j+1,j-1,j+1, LCDRed);
			}
		}
	}
	
}


//z calibrate

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

int calc(int xy, double a, double b){
    return (int)(a * (double)xy + b);
}
