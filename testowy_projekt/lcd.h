#include<stdio.h>
#include<string.h>
#include"lcd_lib/Open1768_LCD.h"
#include"lcd_lib/LCD_ILI9325.h"
#include"lcd_lib/asciiLib.h"

void drawRectangle(int x1, int y1, int x2, int y2, unit16_t color);

void writeSign(int x_0, int y_0, unsigned char sign, unit16_t color);

void writeString(int x_0, int y_0, char *napis, unit16_t color);