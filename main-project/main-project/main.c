/*
 * main-project.c
 *
 * Created: 2/09/2019 3:59:08 pm
 * Author : Aniket
 */ 

#include <avr/io.h>

void uart_init()
{
	// Mode Selection - Asynchronus UART
	UCSR0C &= ~(1 << UMSEL10);
	UCSR0C &= ~(1 << UMSEL11);
	
	// Character Size - 8 bit
	UCSR0B &= ~(1 << UCSZ02);
	UCSR0C |= (1 << UCSZ10);
	UCSR0C |= (1 << UCSZ11);
	
	// Baud Rate - 9600
	UBRR0 = 133;
	
	// Transmitter Enable
	UCSR0B |= (1 << TXEN0);
	
	// Parity Mode - Disabled
	UCSR0C &= ~(1 << UPM00);
	UCSR0C &= ~(1 << UPM10);
	
	// Stop Bit Selection - 1 bit
	UCSR0C &= ~(1 << USBS0);
}

void adc_init()
{
	// Reference Selection - AVCC
	ADMUX |= (1 << REFS0);
	ADMUX &= ~(1 << REFS1);
	
	// Left Adjust Results
	ADMUX |= (1 << ADLAR);
	
	// Enable and Start Conversion
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADSC);
	
	// Ensure Control + Status Register B is in Free Running Mode
	ADCSRB = 0b00000000;
}


int main(void)
{
	// Declare Local Vars Here
	
	
	// Call Initialisation Functions
	uart_init();
	adc_init;
	
    /* Replace with your application code */
    while (1) 
    {
    }
}
