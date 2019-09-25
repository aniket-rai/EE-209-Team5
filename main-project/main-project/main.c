/*
 * main-project.c
 *
 * Created: 2/09/2019 3:59:08 pm
 * Author : Aniket
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// interrupt service routines
ISR(INT0_vect)
{
	
}

ISR(INT1_vect)
{
	
}
// other initializations
void init()
{
	// Any logical change in INT0 generates interrupt 
	EICRA |= (1 << ISC00);
	EICRA &= ~(1 << ISC01);
	
	// Any logical change in INT1 generates interrupt
	EICRA |= (1 << ISC10);
	EICRA &= ~(1 << ISC11);
	
	// Enabling interrupts on INT0 and INT1
	EIMSK |= (1 << INT0);
	EIMSK |= (1 << INT1);
	
	// Enable global interrupts
	sei();
}


// function that initialises the uart
void uart_init() 
{
	// Mode Selection - Asynchronous UART
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

// function that initialises the adc
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


float adc_read() {
	
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
	init();
	uart_init();
	adc_init;
	
    /* Replace with your application code */
    while (1) 
    {
		// save 20 values from adc
		
		
		
		// copy current and voltage values from adc
		
		
    }
}
