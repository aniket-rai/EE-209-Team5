/*
 * lab-1.c
 *
 * Created: 2/08/2019 12:50:04 PM
 * Author : Aniket Rai
 */ 

#include <avr/io.h>
#define BAUD 9600

void usart_init(uint16_t ubrr){
	// Mode Selection - Asynchronous USART
	UCSR0C &= ~(1 << UMSEL10);
	UCSR0C &= ~(1 << UMSEL11);
	
	// Character Size - 8 Bit
	UCSR0B &= ~(1 << UCSZ02);
	UCSR0C |= (1 << UCSZ10);
	UCSR0C |= (1 << UCSZ11);
	
	// Baud Rate - 9600
	UBRR0H = 0b0000;
	UBRR0L = 0b01100111;
	
	// Transmitter Enable - Yes
	UCSR0B |= (1 << RXEN0);
	
	// Parity Mode - Disabled
	UCSR0C &= ~(1 << UPM00);
	UCSR0C &= ~(1 << UPM10);
	
	// Stop Bit Selection - 1 bit
	UCSR0C &= ~(1 << USBS0);
	
}

void usart_transmit(uint8_t data){
	while(!(UCSR0A & (1 << TXC0)));
	
	if (UCSR0A & (1 << UDRE0)){
		UDR0 = data;
	}
	else {
		usart_transmit(data);
	}
}

int main(void)
{
	// Initialise the registers in the uC
	usart_init(1);
	
    /* Replace with your application code */
    while (1) 
    {
		int data = 3;
		// Transmit the number 3
		usart_transmit(data);
    }
}



