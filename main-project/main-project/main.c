/*
 * main-project.c
 *
 * Created: 2/09/2019 3:59:08 pm
 * Author : Aniket
 */

#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>
#include <math.h>
#include "adc.h"
#include "uart.h"

// Global Variables
#define NUMBER_OF_SAMPLES 50
volatile uint8_t adc_value;
//volatile uint8_t numberOfSamples = 50;
volatile uint8_t startOfIndex = 0;
volatile uint8_t voltageValues[NUMBER_OF_SAMPLES];
volatile uint8_t voltageIndex = 0;
volatile uint8_t currentValues[NUMBER_OF_SAMPLES];
volatile uint8_t currentIndex = 0;
volatile uint8_t channel = 0;

// interrupt service routines;
ISR(ADC_vect)
{
	if (channel == 0) {
		if(voltageIndex == 50) {
			voltageIndex = 0;
		}
		voltageValues[voltageIndex] = ADCH;
		voltageIndex++;
		channel = 1;
		change_adc_channel(channel);
	} else if (channel == 1) {
		if(currentIndex == 50) {
			currentIndex = 0;
		}
		currentValues[currentIndex] = ADCH;
		currentIndex++;
		channel = 0;
		change_adc_channel(channel);
	}
}

int main(void)
{
	// Local variables here
	uint8_t voltagePeak = 0;
	double currentRMS = 0;
	double realPower = 0;
	//double powerFactor = 0;
//	uint8_t numberOfSamples = 20;
	uint8_t samplesToCalculate;

	// Call Initialization Functions
	//init_timer0();
	//init_interrupts();*/
	init_uart();
	init_adc();
	sei();

	// Working Loop for Main Functionality
	while (1)
	{
		if ((startOfIndex + NUMBER_OF_SAMPLES) >= 50) {
			samplesToCalculate = 50 - startOfIndex;
		}
		else {
			samplesToCalculate = NUMBER_OF_SAMPLES;
		}

		cli();
		voltagePeak = 0;
		for (int i = 0; i < startOfIndex+samplesToCalculate; i++) {
			if(voltageValues[i] > voltagePeak) {
				voltagePeak = voltageValues[i];
			}
			double currentSample = convert_adc(currentValues[i]);
			currentRMS += pow(currentSample,2);
			realPower += convert_adc(voltageValues[i]) * currentSample;
		}
		
		currentRMS = sqrt(currentRMS/samplesToCalculate);
		realPower /= NUMBER_OF_SAMPLES;
		sei();
//		realPower = voltageRMS * currentRMS * powerFactor;

		transmitVoltage(convert_adc(voltagePeak));
		transmitCurrent(currentRMS);
		transmitRealPower(realPower);
/*		transmitPowerFactor(0.9103);*/
	}

}
