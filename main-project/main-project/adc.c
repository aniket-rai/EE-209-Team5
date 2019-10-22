/*
 * ADC function file to initialise the hardware and contains two other
 * functions. change_adc_channel() and convert_adc().
 *
 * Author: Aniket Rai & Adam Wilson
 */

#include <avr/io.h>
#include "adc.h"

#define VCC 5
#define resolution 256

void init_adc() {
	// Reference Selection - AVCC
	ADMUX |= (1 << REFS0);
	ADMUX &= ~(1 << REFS1);

	// Left Adjust Results
	ADMUX |= (1 << ADLAR);

	// Enable Conversion
	ADCSRA |= (1 << ADEN);
	
	// Enable ADC Interrupts
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

	// Start conversion again
	ADCSRA |= (1 << ADSC);
}

double convert_adc_value(uint8_t adc_value) {
	return ((double)adc_value * ((double)VCC/(double)resolution));
}
