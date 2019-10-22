/*
 * UART Transmission file. Initialises the uart and transmits either voltage,
 * current, real power and power factor.
 *
 * Author: Aniket Rai & Adam Wilson
 */

// Libraries
#include <avr/io.h>
#include <math.h>

// Macros
#define V 'V'
#define I 'I'
#define P 'P'
#define F 'F'
#define EQ '='
#define DOT '.'
#define SLASH 92
#define N 'n'
#define UBRR0_VALUE 103

// initialises the uart module
void init_uart(uint16_t ubrr) {
	// Mode Selection - Asynchronous USART
	UCSR0C &= ~(1 << UMSEL10);
	UCSR0C &= ~(1 << UMSEL11);

	// Character Size - 8 Bit
	UCSR0B &= ~(1 << UCSZ02);
	UCSR0C |= (1 << UCSZ10);
	UCSR0C |= (1 << UCSZ11);

	// Baud Rate - 9600
	UBRR0 = UBRR0_VALUE;

	// Transmitter Enable - Yes
	UCSR0B |= (1 << TXEN0);

	// Parity Mode - Disabled
	UCSR0C &= ~(1 << UPM00);
	UCSR0C &= ~(1 << UPM10);

	// Stop Bit Selection - 1 bit
	UCSR0C &= ~(1 << USBS0);
}

// transmits data passed in through a uart
void transmit_uart(uint8_t data) {
	while(!(UCSR0A & (1 << UDRE0))) {

	}
	UDR0 = data;
}

/* Voltage Transmission Function */
void transmitVoltage(double data) {
	// transmit placeholder and equals
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
		uint8_t oneth = (10*(data - (uint8_t)data));
		transmit_uart(oneth + 48);

		// transmit 0.01 column
		uint8_t tenth = (uint8_t)(data*100 - (uint8_t)(data)*100 - oneth*10);
		transmit_uart(tenth + 48);

		// New line + Startline
		transmit_uart(SLASH);
		transmit_uart(N);
	}
	else {
		// transmit 1.00 column
		transmit_uart((uint8_t)data + 48);

		// transmit 0.10 column
		transmit_uart(DOT);
		uint8_t ones = 10*(data - (uint8_t)data);
		transmit_uart(ones + 48);

		// transmit 0.01 column
		uint8_t tens = (uint8_t)(data*100 - (uint8_t)(data)*100- ones*10);
		transmit_uart(tens + 48);

		// transmit 0.001 column
		uint8_t hundreds = (uint8_t)(data*1000 - (uint8_t)(data)*1000 - tens*10 - ones*100);
		transmit_uart(hundreds + 48);

		// New line + Startline
		transmit_uart(SLASH);
		transmit_uart(N);
	}
}

/* Current Transmission Function */
void transmitCurrent(double data) {
	// transmit placeholder and equals
	transmit_uart(I);
	transmit_uart(EQ);

	// transmit 100.00 column
	uint8_t hundreds = (uint8_t)((data - fmod(data, 100))/100);
	transmit_uart(hundreds + 48);

	// trasmit 10.00 column
	uint8_t tens =  (uint8_t)((data - fmod(data, 10) - hundreds * 100)/10);
	transmit_uart(tens + 48);

	// transmit 1.00 column
	uint8_t ones = (uint8_t)(fmod(data, 10));
	transmit_uart(ones + 48);

	// transmit 0.10 column
	transmit_uart(DOT);
	volatile uint8_t tenths = (data - hundreds*100 - tens*10 - ones) * 10;
	transmit_uart(tenths + 48);

	// New line + Startline
	transmit_uart(SLASH);
	transmit_uart(N);
}

/* Power Factor Transmission Function */
void transmitPowerFactor(double data) {
	// transmit placeholder and equals
	transmit_uart(F);
	transmit_uart(EQ);

	//transmit 0 and Dot
	transmit_uart(48);
	transmit_uart(DOT);

	// transmit 0.1 column
	uint8_t ones = (uint8_t)(data * 10);
	transmit_uart(ones + 48);

	// transmit 0.01 column
	uint8_t tens = (uint8_t)(data*100 - ones*10);
	transmit_uart(tens + 48);

	// tranmit 0.001 column
	uint8_t hundreds = (uint8_t)(data*1000 - tens*10 - ones*100);
	transmit_uart(hundreds + 48);

	// New line + Startline
	transmit_uart(SLASH);
	transmit_uart(N);
}

/* Real Power Transmission Function */
void transmitRealPower(double data) {
	// transmit placeholder and equals
	transmit_uart(P);
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
		uint8_t tenth = (10*(data - (uint8_t)data));
		transmit_uart(tenth + 48);

		// transmit 0.01 column
		transmit_uart((data - tens*10 - ones - tenth/10)*100 + 48);

		// New line + Startline
		transmit_uart(SLASH);
		transmit_uart(N);
	}
	else {
		// transmit 1.00 column
		transmit_uart((uint8_t)data + 48);

		// transmit 0.10 column
		transmit_uart(DOT);
		uint8_t tens = 10*(data - (int)data);
		transmit_uart(tens + 48);

		// transmit 0.01 column
		uint8_t ones = (uint8_t)(fmod((data*100),10));
		transmit_uart(ones + 48);

		// transmit 0.001 column
		transmit_uart((uint8_t)(fmod(data*1000, 10)) + 48);

		// New line + Startline
		transmit_uart(SLASH);
		transmit_uart(N);
	}
}
