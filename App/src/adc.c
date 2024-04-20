/*
 * adc.c
 *
 *  Created on: Apr 15, 2024
 *      Author: SanglaeKim
 */

#include "adc.h"

extern ADC_HandleTypeDef hadc1;

bool adcInit(void) {
	return true;
}

uint16_t adcRead(uint8_t ch) {
	uint16_t ret = 0;
	switch (ch) {
	case _DEF_CH1:
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 100);
		ret = HAL_ADC_GetValue(&hadc1);
		break;
	default:
		break;
	}

	return ret;
}

double adcReadVol(uint8_t ch) {
	double ret = 0.0F;
	uint16_t adc_data = adcRead(0);

	ret = (3.3F * (double) adc_data / 4096.0F);

	return ret;
}

