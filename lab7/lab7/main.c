/*
 * lab7.c
 *
 * Created: 2019-10-02 11:02:50 AM
 * Author : USER
 */ 
#define F_CPU 16000000UL
#include <stdint.h>
#include <avr/io.h>
#include "timer0.h"
#include "led.h"

int compare_count = 0;

ISR(TIMER0_COMPA_vect) {
	if(compare_count == 100) {
		led_toggle();
		compare_count = 0;
	} else {
		compare_count++;
	}
}

int main(void)
{	
	DDRB |= (1 << PORTB5);
	timer0_init();
	sei(); //Q3.1
	while (1) {
/* Q 2.1	if(timer0_checkAndClearOverflow()) {
			led_toggle();
		}*/
	}
}
