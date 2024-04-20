/*
 * led.h
 *
 *  Created on: Apr 15, 2024
 *      Author: SanglaeKim
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "def.h"

bool ledInit(void);
void ledOn(uint8_t ch);
void ledOff(uint8_t ch);
void ledToggle(uint8_t ch);


#endif /* INC_LED_H_ */
