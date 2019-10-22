/*
 * Main project file -> this file contains the main algorithm that provides the
 * main functionality of the project.
 *
 * Author: Aniket Rai & Adam Wilson
 */

// Libraries Needed
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h> 
#include "adc.h"
#include "uart.h"

// Macros
#define NUMBER_OF_SAMPLES 50
#define VOLTAGE_FACTOR 19
#define CURRENT_FACTOR 950
#define OFFSET 1.82

// Global Variables
volatile uint8_t startOfIndex = 0;
volatile uint8_t voltageValues[NUMBER_OF_SAMPLES];
volatile uint8_t voltageIndex = 0;
volatile uint8_t currentValues[NUMBER_OF_SAMPLES];
volatile uint8_t currentIndex = 0;
volatile uint8_t adcChannel = 0;

// ADC Interrupt Service routine that when triggered saves either the current
// or voltage value into the respective array.
ISR(ADC_vect)
{	
	// Voltage sampling
	if (adcChannel == 0) {
		if(voltageIndex == 50) {
			voltageIndex = 0;
		}
		voltageValues[voltageIndex] = ADCH;
		voltageIndex++;
		adcChannel = 4;
		change_adc_channel(adcChannel);
	}
	// Current sampling
	else if (adcChannel == 4) {
		if(currentIndex == 50) {
			currentIndex = 0;
		}
		currentValues[currentIndex] = ADCH;
		currentIndex++;
		adcChannel = 0;
		change_adc_channel(adcChannel);
	}
}


int main(void)
{
	// Local variables here
	uint8_t voltagePeak = 0;
	double voltageRMS = 0;
	double currentRMS = 0;
	double realPower = 0;
	double voltageSample;
	double currentSample;
	double powerFactor = 0;
	uint8_t samplesToCalculate;

	// Call Initialization Functions
	init_uart();
	init_adc();
	sei();

	// Working Loop for Main Functionality
	while (1)
	{
		// Ensure we won't access anythng out of the array
		if ((startOfIndex + NUMBER_OF_SAMPLES) >= 50) {
			samplesToCalculate = 50 - startOfIndex;
		}
		else {
			samplesToCalculate = NUMBER_OF_SAMPLES;
		}

		// Clear interrupts and ready data for calculations
		cli();
		voltagePeak = 0;

		// Linear Approximation
		for (int x = 0; x < sizeof(currentValues)/sizeof(double); x++) {
			currentValues[x] = 0.5*(currentValues[x]+currentValues[x+1]);
		}

		// Calculation loop
		for (int i = 0; i < startOfIndex+samplesToCalculate; i++) {
			// find max of values sampled as treat that as v-peak
			if(voltageValues[i] > voltagePeak) {
				voltagePeak = voltageValues[i];
			}

			// Calculate Vrms, Irms, Real Power and Power Factor
			voltageSample = VOLTAGE_FACTOR * (convert_adc_value(voltageValues[i]) - OFFSET);
			voltageRMS += pow(voltageSample,2);

			currentSample = CURRENT_FACTOR * (convert_adc_value(currentValues[i]) - OFFSET);
			currentRMS += pow(currentSample,2);

			realPower += voltageSample * currentSample / 1000;
		}

		voltageRMS = sqrt(voltageRMS/samplesToCalculate);
		currentRMS = sqrt(currentRMS/samplesToCalculate);
		realPower /= NUMBER_OF_SAMPLES;
		powerFactor = realPower / (voltageRMS * currentRMS / 1000);

		sei();

		volatile double floatvoltagepk = VOLTAGE_FACTOR * (convert_adc_value(voltagePeak) - OFFSET);

		// Transmit the respective values
		transmitVoltage(floatvoltagepk);
		transmitCurrent(currentRMS);
		transmitRealPower(realPower);
		transmitPowerFactor(powerFactor);
	}

}
