/*
 * UART-Test.c
 *
 * Created: 18/10/2019 10:14:10 AM
 * Author : arai759
 */ 

#include <avr/io.h>
#include "uart.h"


int main(void) {
	init_uart(9600);
    /* Replace with your application code */
    while (1) 
    {
		transmitCurrent(1);
		transmitCurrent(11);
		transmitCurrent(99.944);
		transmitCurrent(999.4265);
    }
}

