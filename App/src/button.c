/*
 * button.c
 *
 *  Created on: Apr 15, 2024
 *      Author: SanglaeKim
 */

#include "button.h"
#include "adc.h"

static const uint8_t adc_ch = _DEF_CH1;

//static const double adcValuesTbl[]={ 0.335F ,0.995F ,1.665F ,2.33F ,2.975F };

typedef struct{
	double adc_min;
	double adc_max;
}button_adc_t;

static const button_adc_t button_adc[]={
		 {2.33F,  2.975F}
		,{1.66F,  2.330F}
		,{0.99F,  1.665F}
		,{0.33F,  0.995F}
		,{0.00F,  0.335F}
};


bool buttonInit(void) {
	return true;
}

bool buttonGetPressed(uint8_t ch) {
	bool ret = false;
	if (ch > BUTTON_MAX) {
		return ret;
	}


	double adcVoltage = adcReadVol(adc_ch);

	for (int i = 0; i < BUTTON_MAX; ++i) {
		if (adcVoltage > button_adc[ch].adc_min && adcVoltage < button_adc[ch].adc_max) {
			ret = true;
		}
	}
#if 0
	if (adcVoltage > (3.3 + 2.65) / 2) {
		// no btn event
	} else if (adcVoltage > (2.65 + 2.01) / 2) {
		if (ch == _DEF_CH1) {
			ret = true;
		}
	} else if (adcVoltage > (2.01 + 1.32) / 2) {
		if (ch == _DEF_CH2) {
			ret = true;
		}
	} else if (adcVoltage > (1.32 + 0.67) / 2) {
		if (ch == _DEF_CH3) {
			ret = true;
		}
	} else if (adcVoltage > 0.67 / 2) {
		if (ch == _DEF_CH4) {
			ret = true;
		}
	} else {
		if (ch == _DEF_CH5) {
			ret = true;
		}
	}
#endif

	return ret;
}

uint32_t buttonGetData(uint8_t ch) {
	uint32_t ret = 0;
	for (int i = 0; i < BUTTON_MAX; ++i) {
		ret |= (buttonGetPressed(i) << i);
	}
	return ret;
}

