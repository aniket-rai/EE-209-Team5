#include <avr/io.h>
#include <avr/interrupt.h>
#include "interrupts.h"

void init_interrupts() {
  // Any logical change in INT0 generates interrupt
	EICRA |= (1 << ISC00);
	EICRA &= ~(1 << ISC01);

	// Any logical change in INT1 generates interrupt
	EICRA |= (1 << ISC10);
	EICRA &= ~(1 << ISC11);

	// Enabling interrupts on INT0 and INT1
	EIMSK |= (1 << INT0);
	EIMSK |= (1 << INT1);

	// Enable global interrupts
	sei();
}
