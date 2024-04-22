/*
 * rtc.c
 *
 *  Created on: Apr 22, 2024
 *      Author: SanglaeKim
 */

#include "cli.h"
#include "rtc.h"

extern RTC_HandleTypeDef hrtc;

static void rtcCli(uint8_t argc, const char **argv);

bool rtcInit(void) {
	bool ret = true;
	cliAdd("rtc", rtcCli);
	return ret;

}

bool rtcGetInfo(rtc_info_t *rtc_info) {
	bool ret = true;

	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };

	if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK) {
		ret = false;
	}
	if(ret){
		rtc_info->time.hours = sTime.Hours;
		rtc_info->time.minutes = sTime.Minutes;
		rtc_info->time.seconds = sTime.Seconds;
	}

	if (HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK) {
		ret = false;
	}
	if (ret) {
		rtc_info->date.year = sDate.Year;
		rtc_info->date.month = sDate.Month;
		rtc_info->date.day = sDate.Date;
	}

	return ret;

}

bool rtcGetTime(rtc_time_t *rtc_time) {
	bool ret = false;

	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };

	if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK) {
		ret = false;
	}
	if(ret){
		rtc_time->hours = sTime.Hours;
		rtc_time->minutes = sTime.Minutes;
		rtc_time->seconds = sTime.Seconds;
	}

	if (HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK) {
		ret = false;
	}
	return ret;
}

bool rtcGetDate(rtc_date_t *rtc_date) {
	bool ret = false;

	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };

	if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK) {
		ret = false;
	}
	if (HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK) {
		ret = false;
	}
	if (ret) {
		rtc_date->year  = sDate.Year;
		rtc_date->month = sDate.Month;
		rtc_date->day   = sDate.Date;
	}
	return ret;
}

bool rtcSetTime(rtc_time_t *rtc_time) {
	bool ret = false;
	return ret;

}

bool rtcSetDate(rtc_date_t *rtc_date) {
	bool ret = false;
	return ret;

}

static void rtcCli(uint8_t argc, const char **argv) {

	bool ret = false;
	if (argc == 2 && cliIsStr(argv[0], "get") && cliIsStr(argv[1], "info")) {
		rtc_info_t rtc_info;
		while(cliKeepLoop()){
			rtcGetInfo(&rtc_info);
			cliPrintf(
					"Y:%02d M:%02d D:%02d H:%02d M:%02d S:%02d \r\n"
					,rtc_info.date.year
					,rtc_info.date.month
					,rtc_info.date.day
					,rtc_info.time.hours
					,rtc_info.time.minutes
					,rtc_info.time.seconds
					);
			delay(100);
		}
		ret = true;
	}

	if (!ret) {
		cliPrintf("rtc get info\n");
		cliPrintf("rtc set time [h] [m] [s]\n");
		cliPrintf("rtc set date [y] [m] [d]\n");
	}

}
