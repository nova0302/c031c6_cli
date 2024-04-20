/*
 * uart.c
 *
 *  Created on: Apr 17, 2024
 *      Author: SanglaeKim
 */
#include "uart.h"

extern UART_HandleTypeDef huart1;

typedef struct {
	uint8_t head;
	uint8_t tail;
	char eBtnBuf[256];
} StFifo_t;

uint8_t g_rcvData;

StFifo_t g_StFifo;

void initQueue(StFifo_t *pFifo) {
	pFifo->head = pFifo->tail = 0;
}
void enqueue(StFifo_t *pFifo, char btn) {
	pFifo->eBtnBuf[pFifo->head++] = btn;
}
bool dequeue(StFifo_t *pFifo, char *pBtn) {
	bool ret = false;
	if (pFifo->head != pFifo->tail) {
		*pBtn = pFifo->eBtnBuf[pFifo->tail++];
		ret = true;
	} else {
	}
	return ret;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart == &huart1) {
		enqueue(&g_StFifo, g_rcvData);
		HAL_UART_Receive_IT(&huart1, &g_rcvData, 1U);
	}
}
bool uartInit(void) {
	bool ret = true;
	HAL_UART_Receive_IT(&huart1, &g_rcvData, 1U);
	return ret;
}

uint32_t uartWrite(uint8_t ch, uint8_t *pData, uint32_t len) {
	uint32_t ret = 0;
	const uint32_t waitMs = 100U;
	HAL_StatusTypeDef halRet;
	switch (ch) {
	case _DEF_CH1:
		//halRet = HAL_UART_Transmit(&huart1, pData, len, 100);
		halRet = HAL_UART_Transmit(&huart1, pData, len, waitMs);
		if (halRet == HAL_OK) {
			ret = len;
		}
		break;
	default:
		break;
	}

	return ret;
}

uint32_t uartAvailable(uint8_t ch) {
	uint32_t ret = 0;
	switch (ch) {
		case _DEF_CH1:
			ret = (g_StFifo.head + 256 - g_StFifo.tail) % 256;
			break;
		default:
			break;
	}

	return ret;
}

uint8_t uartRead(uint8_t ch) {
	uint8_t ret = 0;
	switch (ch) {
		case _DEF_CH1:
			if (uartAvailable(_DEF_CH1)>0) {
				dequeue(&g_StFifo, (char*)&ret);
			}
			break;
		default:
			break;
	}

	return ret;
}

uint32_t uartPrintf(uint8_t ch, const char *fmt, ...) {
	uint32_t ret = 0;
	va_list arg;
	char printBuf[256];

	va_start(arg, fmt);

	int len;
	len = vsnprintf(printBuf, 256, fmt, arg);
	va_end(arg);

	if (len > 0) {
		ret = uartWrite(ch, (uint8_t*) printBuf, len);
	}

	return ret;
}
