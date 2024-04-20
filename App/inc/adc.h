/*
 * adc.h
 *
 *  Created on: Apr 15, 2024
 *      Author: SanglaeKim
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "def.h"


bool adcInit(void);
uint16_t adcRead(uint8_t ch);
double adcReadVol(uint8_t ch);



#endif /* INC_ADC_H_ */
