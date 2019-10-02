/*
 * timer0.h
 *
 * Created: 2019-10-02 12:02:57 PM
 *  Author: USER
 */ 
#ifndef TIMER0_H_
#define TIMER0_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
//initialize timer0
//sets it up to count to ......
void timer0_init();
//(when polling) check if timer0 has overflowed
//if so, it will clear the overflow flag and return 1
//otherwise, it returns 0
uint8_t timer0_checkAndClearOverflow();
#endif