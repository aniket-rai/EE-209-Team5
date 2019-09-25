/*
 * CFile1.c
 *
 * Created: 25/09/2019 2:13:14 pm
 *  Author: Aniket
 */ 

#include <avr/io.h>

void init_adc() {
	// Reference Selection - AVCC
	ADMUX |= (1 << REFS0);
	ADMUX &= ~(1 << REFS1);
		
	// Left Adjust Results
	ADMUX |= (1 << ADLAR);
		
	// Enable Conversion
	ADCSRA |= (1 << ADEN);
	
	// Set prescaler
	ADCSRA |= (1 << ADPS0);
	ADCSRA |= (1 << ADPS1);
	ADCSRA |= (1 << ADPS2);
		
	// Ensure Control + Status Register B is in Free Running Mode
	ADCSRB = 0b00000000;
}

uint16_t read_adc(uint8_t channel) {
	// Set the channel to argument passed in
	ADMUX = 0b01100000;
	ADMUX |= channel;
	
	// Start converting and wait for finish
	ADCSRA |= (1 << ADSC);
	while ((ADCSRA & (1 << ADIF)) == 0) {
		// Blocking
	}
	
	// Store adc value and convert to millivolts
	uint16_t adc_value = (ADCL << 0) | (ADCH << 8);
	
	return adc_value;
}
	
double convert_adc(uint16_t adc_value) {
	return (float)adc_value * (float)(5000/1024);
}
