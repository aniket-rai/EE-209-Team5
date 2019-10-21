#include <avr/io.h>

void init_adc();
void change_adc_channel(uint8_t channel);
double convert_adc(uint8_t adc_value);
