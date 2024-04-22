/*
 * swtimer.c
 *
 *  Created on: Apr 22, 2024
 *      Author: SanglaeKim
 */
#include "swtimer.h"


#define NUM_SWTIMER (8U)

typedef struct{
	bool enable;
	//bool is_set;
	SwtimerMode_t mode;
	uint32_t counter;
	uint32_t reload;
	void (*func)(void *arg);
	void *func_arg;
}swtimer_t;

uint8_t swtimer_count = 0;
swtimer_t swtimer_tbl[NUM_SWTIMER];
extern TIM_HandleTypeDef htim14;

bool swtimerInit(void){
	bool ret = true;
	for (int i = 0; i < NUM_SWTIMER; ++i) {
		swtimer_tbl[i].enable   = false;
		//swtimer_tbl[i].is_set   = false;
		swtimer_tbl[i].counter  = 0U;
		swtimer_tbl[i].func     = NULL;
		swtimer_tbl[i].func_arg = NULL;
		swtimer_tbl[i].mode     = SWTIMER_ONETIME;
		swtimer_tbl[i].reload   = 0;
	}
	HAL_TIM_Base_Start_IT(&htim14);
	return ret;
}

bool swtimerGetCh(uint8_t *p_ch){
	bool ret = false;
	if (swtimer_count < NUM_SWTIMER) {
		//if (!swtimer_tbl[swtimer_count].is_set) {
			*p_ch = swtimer_count++;
			ret = true;
		//}
	}
	return ret;
}

bool swtimerSet(uint8_t ch
		, void (*func)(void *arg)
		, void *func_arg
		, SwtimerMode_t mode
		, uint32_t time_ms)
{
	bool ret = false;

	if (ch < NUM_SWTIMER) {
		swtimer_tbl[ch].func     = func;
		swtimer_tbl[ch].func_arg = func_arg;
		swtimer_tbl[ch].mode     = mode;
		swtimer_tbl[ch].counter  = 0U;
		swtimer_tbl[ch].enable   = false;
		swtimer_tbl[ch].reload   = time_ms;
		swtimer_count++;
		ret = true;
	}
	return ret;
}

bool swtimerStart(uint8_t ch){
	bool ret = false;
	if (ch < NUM_SWTIMER) {
		swtimer_tbl[ch].counter = 0;
		swtimer_tbl[ch].enable = true;
		ret = true;
	}
	return ret;
}

bool swtimerStop(uint8_t ch){
	bool ret = false;
	if (ch < NUM_SWTIMER) {
		swtimer_tbl[ch].enable = false;
		ret = true;
	}
	return ret;
}

void swtimerIsr(void){
	for (int i = 0; i < NUM_SWTIMER; ++i) {
		if (swtimer_tbl[i].enable) {
			swtimer_tbl[i].counter++;
			if (swtimer_tbl[i].counter >= swtimer_tbl[i].reload) {
				if (swtimer_tbl[i].func != NULL) {
					swtimer_tbl[i].func(swtimer_tbl[i].func_arg);
				}
				swtimer_tbl[i].counter = 0;
				if (swtimer_tbl[i].mode == SWTIMER_ONETIME) {
					swtimer_tbl[i].enable = false;
				}
			}
		}
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	//static uint32_t count;
	if (htim == &htim14) {
		swtimerIsr();
		/*
		if (count++ > 500) {
			count = 0;
			HAL_GPIO_TogglePin(yLed_GPIO_Port, yLed_Pin);
		}
		*/
	}
}
