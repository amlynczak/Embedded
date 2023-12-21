#include <stdio.h>
#include "lcd.h"
#include "usart.h"

extern ARM_DRIVER_USART Driver_USART0;
static bool startFlag;

typedef struct{
	int sqares[5][5]; //0 - nic nie ma na polu, 1 - postawiony statek, -1 - trafiony statek
}Board;

typedef struct{
	int size;
	int hits;
	bool zatopiony;
	int *coordinates[2];
}Ship;

typedef struct{
	Board boardPlayer;
	Board boardOpponent;
	
	Ship ships[3];
	bool win;
	
}Player;

#include<stdlib.h>

bool isLegal(int x, int y, Board *b);

int przelicz(int x, int y);

void ustawStatkiRand(Player *p);

void start(double *tab, ARM_DRIVER_USART * USARTdrv);

void shoot(double *tab, Player *player, ARM_DRIVER_USART * USARTdrv);

//z board

void drawBoard(Board *board);

void drawX(int xy);

//z calibrate

#include"lcd.h"
#include"tp_lib/TP_Open1768.h"

void calibrate(double *arr);

int calc(int xy, double a, double b);
