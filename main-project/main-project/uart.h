/*
 * uart.h
 *
 * Created: 25/09/2019 2:51:58 pm
 *  Author: Aniket
 */ 

#ifndef _UART_H
#define _UART_H

void init_uart();
void transmit_uart(uint8_t data);
void transmitVoltage(double data);
void transmitCurrent(double data);
void transmitPowerFactor(double data);
void transmitRealPower(double data);

#endif