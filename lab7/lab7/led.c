/*
 * led.c
 *
 * Created: 2019-10-02 12:03:51 PM
 *  Author: USER
 */ 
#include "led.h"
void led_toggle() {
	PORTB ^= (1 << PORTB5);
}