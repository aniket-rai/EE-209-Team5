/*
 * uart.h
 *
 * Created: 25/09/2019 2:51:58 pm
 *  Author: Aniket
 */ 

#include <avr/io.h>

void init_uart();
void transmit_uart();
void transmitVoltage();
void transmitCurrent();
void transmitPowerFactor();
void transmitRealPower();