/*

 * lab-1.c

 *

 * Created: 2/08/2019 12:50:04 PM

 * Author : Aniket Rai, Adam Wilson

 */ 

#include <avr/io.h>
#define BAUD_RATE 9600
#define COMMA 44
#define SPACE 32
#define LINE_BREAK usart_transmit(10);\
		   usart_transmit(13)

void usart_init(uint16_t ubrr){

	// Mode Selection - Asynchronous USART
	UCSR0C &= ~(1 << UMSEL10);
	UCSR0C &= ~(1 << UMSEL11);

	// Character Size - 8 Bit
	UCSR0B &= ~(1 << UCSZ02);
	UCSR0C |= (1 << UCSZ10);
	UCSR0C |= (1 << UCSZ11);
	
	// Baud Rate - 9600
	UBRR0 = ubrr;

	// Transmitter Enable - Yes
	UCSR0B |= (1 << TXEN0);
	
	// Parity Mode - Disabled
	UCSR0C &= ~(1 << UPM00);
	UCSR0C &= ~(1 << UPM10);

	// Stop Bit Selection - 1 bit
	UCSR0C &= ~(1 << USBS0);
}

void usart_transmit(uint8_t data){
	while(!(UCSR0A & (1 << UDRE0))) {
		
	}
	UDR0 = data;
}

int main(void)
{
	// Initialize the UART registers in the uC
	uint16_t ubrr_val = 16000000 / 16 / BAUD_RATE - 1;
	usart_init(ubrr_val);

	// Prime calculator
	uint16_t prime_numbers[62];
	int is_prime, number, num_to_check, current_prime = 0;

	for(number = 2; number < 300; number++) {
		is_prime = 1;
		num_to_check = 2;
		do {
			if(number % num_to_check == 0 && num_to_check != number && num_to_check != 1) {
				is_prime = 0;
			}
			num_to_check++;
		} while(is_prime == 1 && num_to_check <= number);
    
		if(is_prime == 1) {
			prime_numbers[current_prime] = number;
			current_prime++;
		}
	}

	while (1) {
		for (int i = 0; i < 62; i++) {
			uint16_t prime = prime_numbers[i];
			
			if (prime / 100 != 0) {
				usart_transmit(prime / 100 + 48);
			}
			
			if (prime > 9){
				usart_transmit((prime / 10) % 10 + 48);
			}
			
			usart_transmit(prime % 10 + 48);
			
			usart_transmit(COMMA);
			usart_transmit(SPACE);
		}
		LINE_BREAK;
		LINE_BREAK;
	}
}
