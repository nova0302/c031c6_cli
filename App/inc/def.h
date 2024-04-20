/*
 * def.h
 *
 *  Created on: Apr 15, 2024
 *      Author: SanglaeKim
 */

#ifndef INC_DEF_H_
#define INC_DEF_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

#define _DEF_CH1 (0U)
#define _DEF_CH2 (1U)
#define _DEF_CH3 (2U)
#define _DEF_CH4 (3U)
#define _DEF_CH5 (4U)

#define _BUTTON_CH_SEL    _DEF_CH1
#define _BUTTON_CH_LEFT   _DEF_CH2
#define _BUTTON_CH_RIGHT  _DEF_CH3
#define _BUTTON_CH_DOWN   _DEF_CH4
#define _BUTTON_CH_UP     _DEF_CH5


void delay(uint32_t time_ms);
uint32_t millis(void);


#endif /* INC_DEF_H_ */
