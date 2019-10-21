#include <avr/io.h>

void init_adc();
uint16_t read_adc(uint8_t channel);
double convert_adc(uint8_t adc_value);
