/*
 * rtc.h
 *
 *  Created on: Apr 22, 2024
 *      Author: SanglaeKim
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_

#include "def.h"

typedef struct{
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
}rtc_time_t;

typedef struct{
	uint8_t year;
	uint8_t month;
	uint8_t day;
}rtc_date_t;

typedef struct{
	rtc_time_t time;
	rtc_date_t date;
}rtc_info_t;


bool rtcInit(void);

bool rtcGetInfo(rtc_info_t *rtc_info);

bool rtcGetTime(rtc_time_t *rtc_time);
bool rtcGetDate(rtc_date_t *rtc_date);

bool rtcSetTime(rtc_time_t *rtc_time);
bool rtcSetDate(rtc_date_t *rtc_date);



#endif /* INC_RTC_H_ */
