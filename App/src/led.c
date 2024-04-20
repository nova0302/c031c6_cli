/*
 * led.c
 *
 *  Created on: Apr 15, 2024
 *      Author: SanglaeKim
 */
#include "led.h"

bool ledInit(void){
	return true;
}

void ledOn(uint8_t ch){
	switch (ch) {
		case _DEF_CH1:
			HAL_GPIO_WritePin(yLed_GPIO_Port, yLed_Pin, GPIO_PIN_SET);
			break;
		default:
			break;
	}

}

void ledOff(uint8_t ch){
	switch (ch) {
		case _DEF_CH1:
			HAL_GPIO_WritePin(yLed_GPIO_Port, yLed_Pin, GPIO_PIN_RESET);
			break;
		default:
			break;
	}
}

void ledToggle(uint8_t ch){
	switch (ch) {
		case _DEF_CH1:
			HAL_GPIO_TogglePin(yLed_GPIO_Port, yLed_Pin);
			break;
		default:
			break;
	}

}



