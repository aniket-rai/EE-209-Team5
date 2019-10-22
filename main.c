/*
 * main-project.c
 *
 * Created: 2/09/2019 3:59:08 pm
 * Author : Aniket
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include "adc.h"
#include "uart.h"

#define NUMBER_OF_SAMPLES 50
#define VOLTAGE_FACTOR 16.85
#define CURRENT_FACTOR 1000
#define OFFSET 1.82

// Global Variables
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
		channel = 4;
		change_adc_channel(channel);
	} else if (channel == 4) {
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
	double voltageRMS = 0;
	double currentRMS = 0;
	double realPower = 0;
	double voltageSample;
	double currentSample;
	double powerFactor = 0;
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
					
		// Linear Approximation
		for (int x = 0; x < sizeof(currentValues)/sizeof(double); x++) {
			currentValues[x] = 0.5*(currentValues[x]+currentValues[x+1]);
		}
		
		for (int i = 0; i < startOfIndex+samplesToCalculate; i++) {
			if(voltageValues[i] > voltagePeak) {
				voltagePeak = voltageValues[i];
			}
			voltageSample = VOLTAGE_FACTOR * (convert_adc(voltageValues[i]) - OFFSET);
			voltageRMS += pow(voltageSample,2);
			
			currentSample = CURRENT_FACTOR * (convert_adc(currentValues[i]) - OFFSET);
			currentRMS += pow(currentSample,2);
			
			realPower += voltageSample * currentSample / 1000;
		}
		
		voltageRMS = sqrt(voltageRMS/samplesToCalculate);
		currentRMS = sqrt(currentRMS/samplesToCalculate);
		realPower /= NUMBER_OF_SAMPLES;
		powerFactor = realPower / (voltageRMS * currentRMS / 1000);
		sei();

		volatile double floatvoltagepk = VOLTAGE_FACTOR * (convert_adc(voltagePeak) - OFFSET);
		transmitVoltage(floatvoltagepk);
		transmitCurrent(currentRMS);
		transmitRealPower(realPower);
		transmitPowerFactor(powerFactor);
	}

}
