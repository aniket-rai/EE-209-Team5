/*
 * CFile1.c
 *
 * Created: 25/09/2019 2:13:14 pm
 *  Author: Aniket
 */

#include <avr/io.h>
#include <avr/interrupt.h> 
#include "adc.h"

void init_adc() {
	// Reference Selection - AVCC
	ADMUX |= (1 << REFS0);
	ADMUX &= ~(1 << REFS1);

	// Left Adjust Results
	ADMUX |= (1 << ADLAR);

	// Enable Conversion
	ADCSRA |= (1 << ADEN);
	
	ADCSRA |= (1 << ADIE);

	// Set prescaler - 64
	ADCSRA |= (1 << ADPS1);
	ADCSRA |= (1 << ADPS2);

	// Ensure Control + Status Register B is in Free Running Mode
	ADCSRB = 0b00000000;

	// Start Conversion
	ADMUX = 0b01100101;
	ADCSRA |= (1 << ADSC);
	
}

void change_adc_channel(uint8_t channel) {

	// Set the channel to argument passed in
	ADMUX = 0b01100000;
	ADMUX |= channel;

	// Start converting
	ADCSRA |= (1 << ADSC);
}

double convert_adc(uint8_t adc_value) {
	return ((double)adc_value * ((double)5/(double)256));
}
