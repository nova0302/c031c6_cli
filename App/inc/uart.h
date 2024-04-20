/*
 * uart.h
 *
 *  Created on: Apr 17, 2024
 *      Author: SanglaeKim
 */

#ifndef INC_UART_H_
#define INC_UART_H_


#include "def.h"

#define UART_MAX_CH (1U)

bool uartInit(void);
uint32_t uartWrite(uint8_t ch, uint8_t *pData, uint32_t len);
uint32_t uartAvailable(uint8_t ch);
uint8_t uartRead(uint8_t ch);
uint32_t uartPrintf(uint8_t ch, const char*fmt, ...);

#endif /* INC_UART_H_ */
