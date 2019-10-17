/*
 * uart.c
 *
 * Created: 25/09/2019 2:51:41 pm
 *  Author: Aniket
 */

#include <avr/io.h>

#define V 86
#define I 73
#define P 80
#define F 70
#define EQ 61
#define DOT 46

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

void transmitVoltage(double data) {
	transmit_uart(V);
	transmit_uart(EQ);

	if(data >= 10) {
		// transmit 10.00 column
		uint8_t tens = (uint8_t)data/10;
		transmit_uart(tens + 48);

		// transmit 1.00 column
		uint8_t ones = (uint8_t)data - tens*10;
		transmit_uart(ones + 48);

		// transmit 0.10 column
		transmit_uart(DOT);
		transmit_uart((10*(data - (int)data)) + 48);

		transmit_uart(NEWLINE);
		transmit_uart(STARTLINE);
	}
	else {
		// transmit 1.00 column
		transmit_uart((uint8_t)data + 48);

		// transmit 0.10 column
		transmit_uart(DOT);
		uint8_t tens = 10*(data - (int)data);
		transmit_uart(tens + 48);

		// transmit 0.01 column
		data *= 100;
		int ones = (int)data % 10;
		transmit_uart(ones + 48);

		// New line + Startline
		transmit_uart(NEWLINE);
		transmit_uart(STARTLINE);
	}
}

void transmitCurrent(double data) {
	transmit_uart(I);
	transmit_uart(EQ);

	// transmit 100.00 column
	uint8_t hundreds = (uint8_t)data/100;
	transmit_uart(hundreds + 48);

	// trasmit 10.00 column
	uint8_t tens = ((uint8_t)data - hundreds*100)/10;
	transmit_uart(tens + 48)

	// transmit 1.00 column
	uint8_t ones = (uint8_t)data - hundreds*100 - tens*10;
	transmit_uart(ones + 48);

	// transmit 0.10 column
	transmit_uart(DOT);
	uint8_t tens = 10*(data - (int)data);
	transmit_uart(tens + 48);

	// New line + Startline
	transmit_uart(NEWLINE);
	transmit_uart(STARTLINE);
}
