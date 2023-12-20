#ifndef CALIBRATION_H
#define CALIBRATION_H

#include"lcd.h"
#include"tp_lib/TP_Open1768.h"
#include"delay.h"

void calibrate(double *arr);

int calc(int xy, double a, double b);

/*tego nie chcemy docelowo*/

int calX(int x);
int calcY(int y);

#endif
