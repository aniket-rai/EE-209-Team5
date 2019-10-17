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
volatile uint8_t numberOfSamples = 50;
volatile uint8_t startOfIndex = 0;
volatile double voltageValues[numberOfSamples];
volatile uint8_t voltageIndex = 0;
volatile double currentValues[numberOfSamples];
volatile uint8_t currentIndex = 0;
volatile uint8_t channel = 0;

// interrupt service routines;
ISR(ADC_vect)
{
	if (currentIndex == 40) {
		voltagevalues[startOfIndex] = convert_adc(ADCH);
		startOfIndex++;
		arrayIndex = startOfIndex;
		channel = 1;
	}

	if (channel == 0) {
		voltageValues[arrayIndex] = convert_adc(ADCH);
		voltageIndex++;
		channel = 1;
	}
	else if (channel == 1) {
		currentValues[arrayIndex] = convert_adc(ADCH);
		currentIndex++;
		channel = 0;
	}

	read_adc(channel);
}

int main(void)
{
	// Local variables here
	double voltageRMS = 0;
	double voltagePeak = 0;
	double currentRMS = 0;
	double realPower = 0;
	double powerFactor = 0;
	uint8_t numberOfSamples = 20;
	uint8_t samplesToCalculate;

	// Call Initialisation Functions
	//init_timer0();
	//init_interrupts();
	init_uart();
	//init_adc();

	// Working Loop for Main Functionality
	/*while (1)
	{
		if ((startOfIndex + numberOfSamples) >= 50) {
			samplesToCalculate = 50 - startOfIndex;
		}
		else {
			samplesToCalculate = numberOfSamples;
		}

		cli();
		for (int i = 0; i < startOfIndex+samplesToCalculate; i++) {
			voltageRMS += voltageValues[i]^2;
			currentRMS += currentRMS[i]^2;
		}
		sei();

		voltageRMS = sqrt(voltageRMS/samplesToCalculate);
		currentRMS = sqrt(currentRMS/samplesToCalculate);
		// POWER FACTOR ALGO HERE
		realPower = voltageRMS * currentRMS * powerFactor;

		transmitVoltage();
		transmitCurrent();
		transmitPowerFactor();
		transmitRealPower();
	}*/

}
