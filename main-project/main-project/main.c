/*
 * main-project.c
 *
 * Created: 2/09/2019 3:59:08 pm
 * Author : Aniket
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
#include "adc.h"
#include "uart.h"
#include "interrupts.h"
#include "timers.h"

// Global Variables
volatile uint8_t adc_value;
volatile double valuesConverted[40];
volatile uint8_t arrayIndex = 0;

// interrupt service routines;
ISR(ADC_vect)
{
	adc_value = ADCH;

	cli();

	valuesConverted[arrayIndex] = convert_adc(adc_value);
	arrayIndex++;

	if (arrayIndex < 40) {
		sei();
	}

}

ISR()
{

}

int main(void)
{
	// Declare Local Vars Here
	int n = 0;
	int numberOfSamples = 15;
	int currentValues[numberOfSamples] = [];
	int voltageValues[numberOfSamples] = [];
	int adjustedCurrent[numberOfSamples] = [];

	// Call Initialisation Functions
	init_timer0();
	init_interrupts();
	init_uart();
	init_adc();

	// Working Loop for Main Functionality
	while (1)
	{
	// save 20 values from adc



	// copy current and voltage values from adc


	}
}
