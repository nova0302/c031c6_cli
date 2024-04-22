/*
 * app.h
 *
 *  Created on: Apr 15, 2024
 *      Author: SanglaeKim
 */

#ifndef INC_APP_H_
#define INC_APP_H_

#include "def.h"
#include "utils.h"
#include "led.h"
#include "adc.h"
#include "button.h"
#include "uart.h"
#include "swtimer.h"
#include "rtc.h"


void appInit(void);
void appMain(void);



#endif /* INC_APP_H_ */
