/*
 * button.h
 *
 *  Created on: Apr 15, 2024
 *      Author: SanglaeKim
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "def.h"

#define BUTTON_MAX (5U)

bool buttonInit(void);
bool buttonGetPressed(uint8_t ch);
uint32_t buttonGetData(uint8_t ch);


#endif /* INC_BUTTON_H_ */
