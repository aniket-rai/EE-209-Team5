#include <avr/io.h>
#include "timers.h"

void init_timer0()
{
	TCCR0A |= (1 << WGM01);
	TCCR0B |= (1 << CS02) | (1 << CS00);
	TIMSK0 |= (1 << OCIE0A);
	OCR0A = 155;
}
