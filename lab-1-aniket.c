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
	UCSR0B |= (1 << TXEN0);
	
	// Parity Mode - Disabled
	UCSR0C &= ~(1 << UPM00);
	UCSR0C &= ~(1 << UPM10);

	// Stop Bit Selection - 1 bit
	UCSR0C &= ~(1 << USBS0);
}


void usart_transmit(uint8_t data){
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}


int main(void)
{
    // Initialize the registers in the uC
    usart_init(1);
    uint8_t data = 51;
    uint8_t primeNumbers[62] = {2, 3, 5, 7, 11, 13};
	

    /* Replace with your application code */
    while (1) 
    {
		for (int i = 0; i < 62; i++){
			uint8_t prime = primeNumbers[i];
			
			if (prime > 99 & prime < 1000) {
				usart_transmit(prime/100 + 48);
				prime -= (prime * (prime/100));
			}
			
			if (prime > 9) {
				usart_transmit(prime/10 + 48);
				prime -= (prime * (prime/10));
			}
			
			if (prime > 0) {
				usart_transmit(prime + 48);
			}	
			
			usart_transmit(44);
			usart_transmit(32);
			
		}
		usart_transmit(10);
		usart_transmit(13);
		usart_transmit(10);
		usart_transmit(13);
    }

}
