#ifndef _UART_H
#define _UART_H

void init_uart();
void transmit_uart(uint8_t data);
void transmitVoltage(double data);
void transmitCurrent(double data);
void transmitPowerFactor(double data);
void transmitRealPower(double data);

#endif