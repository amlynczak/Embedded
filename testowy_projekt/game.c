#include"game.h"
#include<stdlib.h>
#include<time.h>

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

void ustawStatkiRand(Player *p){
	srand(time(NULL));
	
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			p->board.sqares[i][j] = 0; 
		}
	}

	int randX = rand()%3;
	int randY = rand()%5;
	
	p->board.sqares[randX][randY] = 1;
	p->board.sqares[randX+1][randY] = 1;
	p->board.sqares[randX+2][randY] = 1;
	
	do{
		randX = rand()%4;
		randY = rand()%5;
	}while(!isLegal(randX, randY, &p->board) && !isLegal(randX+1, randY, &p->board));
	
	p->board.sqares[randX][randY] = 1;
	p->board.sqares[randX+1][randY] = 1;
	
	do{
		randX = rand()%5;
		randY = rand()%5;
	}while(!isLegal(randX, randY, &p->board));
	
	p->board.sqares[randX][randY] = 1;
	
}

void start(double *tab){
  static ARM_DRIVER_USART * USARTdrv = &Driver_USART0;
  USART_Init(USARTdrv);

  drawRectangle(190,95, 220, 225, LCDBlack);
	drawRectangle(191,96,219,224,LCDWhite);
	writeString(196, 135, "READY", LCDBlack); //przycisk gotowosci

  int px = 10;
	int py = 10;
	int *x = &px;
	int *y = &py;
	char text[5];
	
	while(1){
		touchpanelGetXY(x, y);

		if(calc(*y , tab[0], tab[1]) < 220 && calc(*y , tab[0], tab[1]) > 190 && calc(*x , tab[2], tab[3]) > 95 && calc(*x , tab[2], tab[3]) < 225){
			startFlag = true;
			USARTdrv->Send("READY", 5);
			break;
		}

		USARTdrv->Receive(text, 5);
		writeString(196, 135, text, LCDBlack);
		if(!strcmp(text, "READY")){
			startFlag = false;
			break;
		}
	}
	drawRectangle(190,95, 220, 225, LCDWhite);
}
