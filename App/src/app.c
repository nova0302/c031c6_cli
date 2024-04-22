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

void infoCli(uint8_t argc, const char **argv);
/*
 void infoCli(uint8_t argc, const char **argv) {
 // uartPrintf(_DEF_CH1,  "infoCli run %d\n", argc);
 cliPrintf("infoCli run %d\n", argc);
 }
 */
void ledIsr(void *arg) {
	ledToggle(_DEF_CH1);
	//HAL_GPIO_TogglePin(yLed_GPIO_Port, yLed_Pin);
}
void testIsr(void *arg){
	static uint32_t count = 0;
	uartPrintf(_DEF_CH1, "%d : testIsr\r\n", count++);
}

void appInit(void) {
	swtimerInit();
	uartInit();
	cliInit();
	ledInit();
	rtcInit();
	adcInit();
	buttonInit();
	cliAdd("info", infoCli);

	uint8_t timer_ch;
	if (swtimerGetCh(&timer_ch)) {
		swtimerSet(timer_ch,
				ledIsr,
				NULL,
				SWTIMER_LOOP,
				500);
		swtimerStart(timer_ch);
	}

	/*
	if (swtimerGetCh(&timer_ch)) {
		swtimerSet(timer_ch,
				testIsr,
				NULL,
				SWTIMER_LOOP,
				500);
		swtimerStart(timer_ch);
	}
	*/

}
void appMain(void) {
	uint32_t last = millis();
	while (true) {
		uint32_t now = millis();
		if (now - last > 1000) {
			last = now;
//			ledToggle(_DEF_CH1);
		}
		cliMain();
		adc_voltage = adcReadVol(0);
		for (int i = 0; i < BUTTON_MAX; ++i) {
			button_data[i] = buttonGetPressed(i);
		}
	}
}

void infoCli(uint8_t argc, const char **argv) {
	bool ret = false;

	//if (argc == 1 && strcmp(argv[0], "test") == 0) {
	if (argc == 1 && cliIsStr(argv[0], "test")) {
		cliPrintf("infoCli run test\n");
		ret = true;
	}
	if (argc == 2 && cliIsStr(argv[0], "print")) {
		uint8_t count;
		count = (uint8_t) cliGetData(argv[1]);
		for (int i = 0; i < count; ++i) {
			cliPrintf("print %d/%d\n", i + 1, count);
		}
		ret = true;
	}
	if (argc == 1 && cliIsStr(argv[0], "button")) {
		while (cliKeepLoop()) {
			for (int i = 0; i < BUTTON_MAX; ++i) {
				cliPrintf("%d", buttonGetPressed(i));
			}
			cliPrintf("\n");
			delay(100);
		}
		ret = true;
	}
	if (argc == 1 && cliIsStr(argv[0], "led")) {
		while (cliKeepLoop()) {
			for (int i = 0; i < BUTTON_MAX; ++i) {
				cliPrintf("%d", buttonGetPressed(i));
			}
			cliPrintf("\n");
			delay(100);
		}
		ret = true;
	}
	if (ret == false) {
		cliPrintf("info test\n");
		cliPrintf("info print 0~10\n");
		cliPrintf("info button\n");
		cliPrintf("info led\n");
	}
}
