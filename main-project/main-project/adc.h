#ifndef _ADC_H
#define _ADC_H

void init_adc();
void change_adc_channel(uint8_t channel);
double convert_adc_value(uint8_t adc_value);

#endif