/*
 * uart.c
 *
 * Created: 25/09/2019 2:51:41 pm
 *  Author: Aniket
 */

#include <avr/io.h>

void init_uart(uint16_t ubrr) {
	// Mode Selection - Asynchronous USART
	UCSR0C &= ~(1 << UMSEL10);
	UCSR0C &= ~(1 << UMSEL11);

	// Character Size - 8 Bit
	UCSR0B &= ~(1 << UCSZ02);
	UCSR0C |= (1 << UCSZ10);
	UCSR0C |= (1 << UCSZ11);

	// Baud Rate - 9600
	UBRR0 = 16000000/(16*ubrr) - 1;

	// Transmitter Enable - Yes
	UCSR0B |= (1 << TXEN0);

	// Parity Mode - Disabled
	UCSR0C &= ~(1 << UPM00);
	UCSR0C &= ~(1 << UPM10);

	// Stop Bit Selection - 1 bit
	UCSR0C &= ~(1 << USBS0);
}

void transmit_uart(uint8_t data) {
	while(!(UCSR0A & (1 << UDRE0))) {

	}
	UDR0 = data;
}
