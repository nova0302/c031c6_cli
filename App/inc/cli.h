/*
 * cli.h
 *
 *  Created on: Apr 18, 2024
 *      Author: SanglaeKim
 */

#ifndef INC_CLI_H_
#define INC_CLI_H_

#include "def.h"

bool cliInit(void);
bool cliMain(void);
bool cliAdd(const char *cmd_str, void (*cmd_func)(uint8_t argc, const char **argv));
//uint32_t uartVPrintf(uint8_t ch, const char *fmt, va_list arg);
void cliPrintf(const char *fmt, ...);
int32_t cliGetData(const char *p_arg);
bool cliIsStr(const char *p_arg, const char *p_str);
bool cliKeepLoop(void);

#endif /* INC_CLI_H_ */
