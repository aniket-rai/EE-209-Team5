/*
 * timer0.c
 *
 * Created: 2019-10-02 12:02:43 PM
 *  Author: USER
 */ 
#include "timer0.h"
#include "led.h"
void timer0_init()
{
	TCCR0A |= (1 << WGM01);
	TCCR0B |= (1 << CS02) | (1 << CS00);
	TIMSK0 |= (1 << OCIE0A);
	OCR0A = 155;
}
uint8_t timer0_checkAndClearOverflow()
{
	if(TIFR0 & (1 << TOV0)) { //TODO: check overflow flag
		TIFR0 &= ~(1 << TOV0);
		//TODO: clear overflow flag
		return 1;
	}
	return 0;
}