#ifndef BOARD_H
#define BOARD_H

#include"lcd.h"
#include"game.h"

void drawBoard(Board *board);

int przelicz(int x, int y);

void drawX(int xy);

#endif
