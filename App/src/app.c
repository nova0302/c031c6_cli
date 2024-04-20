/*
 * app.c
 *
 *  Created on: Apr 15, 2024
 *      Author: SanglaeKim
 */
#include "app.h"
#include "cli.h"

double adc_voltage = 0.0F;

bool button_data[BUTTON_MAX];

void infoCli(uint8_t argc, const char **argv){
	//uartPrintf(_DEF_CH1,  "infoCli run %d\n", argc);
	cliPrintf("infoCli run %d\n", argc);
}

void appInit(void) {
	uartInit();
	cliInit();
	ledInit();
	adcInit();
	buttonInit();
	cliAdd("info", infoCli);

}
void appMain(void) {
	uint32_t last = millis();
	while (true) {
		uint32_t now = millis();
		if (now - last > 1000) {
			last = now;
			ledToggle(_DEF_CH1);
		}

		cliMain();

		adc_voltage = adcReadVol(0);
		for (int i = 0; i < BUTTON_MAX; ++i) {
			button_data[i] = buttonGetPressed(i);
		}
	}
}

