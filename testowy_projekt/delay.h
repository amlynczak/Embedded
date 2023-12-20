#ifndef DELAY_H
#define DELAY_H

#include<stdio.h>
#include"LPC17xx.h"

static volatile uint32_t msTicks = 0;

static void SysTick_Handler(void){
    msTicks++;
}

static void delay(int t){
    msTicks = 0;
    while(msTicks<t);
}

/*
w main umiescic:

uint32_t returnCode;
return Code = SysTick_Config(SystemCoreClock/100); //mianownik zmienic w zaleznosci od potrzeby
if(returnCode!=0){obsuga error} */

#endif
