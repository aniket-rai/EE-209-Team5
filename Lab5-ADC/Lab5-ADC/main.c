/*
 * Lab5-ADC.c
 *
 * Created: 25/09/2019
 * Author : Aniket
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include "adc.h"
#include "uart.h"

#define DOT 46
#define NEWLINE 10
#define STARTLINE 13

void transmit_data(float data) {
	// transmit 1.00 column
	transmit_uart((uint8_t)data + 48);
	
	// transmit 0.10 column
	transmit_uart(DOT);
	uint8_t data_int = 10*(data - (int)data);
	transmit_uart(data_int + 48);
	
	// transmit 0.01 column
	uint8_t data_int2 = roundf(data * 100) / 100;
	transmit_uart(data_int2 + 48);
	transmit_uart(NEWLINE);
	transmit_uart(STARTLINE);
}

int main(void)
{
	// Initialisation
	init_adc();
	init_uart(9600);
	uint8_t channel = 0;
	
    /* Reading, Converting and Transmitting Code */
    while (1) 
    {
		//float data = 3.21;
		//transmit_data(data);
		
		// read, convert and transmit data
		transmit_data(convert_adc(read_adc(channel)));
			
		// change the channel
		if (channel == 0) {
			channel = 1;
		}
		else {
			channel = 0;
		}
    }
}

