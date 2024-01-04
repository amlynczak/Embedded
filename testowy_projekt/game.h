#ifndef GAME_H
#define GAME_H

#include "usart.h"
#include "tp_lib/TP_Open1768.h"

extern ARM_DRIVER_USART Driver_USART0;
static bool startFlag;

typedef struct{
	int sqares[5][5]; //0 - nic nie ma na polu, 1 - postawiony statek, -1 - trafiony statek
}Board;

typedef struct{
	int size;
	int hits;
	int coordinatesStart[2];
	bool orientation; //true - pionowo, false - poziomo
	bool zatopiony;
}Ship;

typedef struct{
	Board boardPlayer;
	Board boardOpponent;
	Ship ships[3];
	bool win;
}Player;

bool isLegal(int x, int y, Board *b);

int przelicz(int x, int y);

void ustawStatkiRand(Player *p);

void start(float *tab, ARM_DRIVER_USART * USARTdrv);

bool shoot(float *tab, Player *player, ARM_DRIVER_USART * USARTdrv);

void end(Player *player, float *tab, ARM_DRIVER_USART * USARTdrv);

//z board

void drawBoard(Board *board);

void drawX(int xy);

void drawVoid(int xy);

//z calibrate

void calibrate(float *arr);

int calc(int xy, float a, float b);

#endif
