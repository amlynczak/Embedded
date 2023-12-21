#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include "calibration.h"
#include "usart.h"

typedef struct{
	int sqares[5][5]; //0 - nic nie ma na polu, 1 - postawiony statek, -1 - trafiony statek
}Board;

typedef struct{
	int size;
	int hits;
	bool zatopiony;
}Ship;

typedef struct{
	Board board;
	Ship ships[3];
	bool win;
}Player;

extern ARM_DRIVER_USART Driver_USART0;
static bool startFlag;

void ustawStatkiRand(Player *p);

void start(double *tab);

#endif
