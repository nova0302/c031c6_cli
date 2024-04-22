/*
 * cli.c
 *
 *  Created on: Apr 18, 2024
 *      Author: SanglaeKim
 */

#include "cli.h"
#include "uart.h"

#define CLI_CMD_LIST_MAX (8U)

typedef struct {
	char cmd_str[8];
	void (*cmd_func)(uint8_t argc, const char **argv);
} cli_cmd_t;

static uint8_t cli_cmd_count = 0;
static cli_cmd_t cli_cmd_func[CLI_CMD_LIST_MAX];

static const uint8_t cli_ch = _DEF_CH1;

static char cli_buf[128];
static uint16_t cli_buf_index;

static uint16_t cli_argc = 0;
static char *cli_argv[8];

static void cliHelp(uint8_t argc, const char **argv);

bool cliInit(void) {
	bool ret = true;
	for (int i = 0; i < CLI_CMD_LIST_MAX; ++i) {
		cli_cmd_func[i].cmd_func = NULL;
	}
	cliAdd("help", cliHelp);

	return ret;
}

static void cliHelp(uint8_t argc, const char **argv){
	cliPrintf("------------------------\r\n");
	for (int i = 0; i < cli_cmd_count; ++i) {
		cliPrintf("%s\n", cli_cmd_func[i].cmd_str);
	}
	cliPrintf("------------------------\r\n");
}

uint32_t uartVPrintf(uint8_t ch, const char *fmt, va_list arg){
	uint32_t ret = 0;
	char print_buf[256];

	int len = vsnprintf(print_buf, 256, fmt, arg);
	if (len > 0) {
		ret = uartWrite(ch, (uint8_t*)print_buf, len);
	}
	return ret;
}

void cliPrintf(const char *fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);
	uartVPrintf(cli_ch, fmt, arg);
	va_end(arg);
}

bool cliAdd(const char *cmd_str, void (*cmd_func)(uint8_t argc, const char **argv)) {
	bool ret = false;
	if (cli_cmd_count < CLI_CMD_LIST_MAX) {
		strncpy(cli_cmd_func[cli_cmd_count].cmd_str, cmd_str, 8);
		cli_cmd_func[cli_cmd_count++].cmd_func = cmd_func;
		ret = true;
	} else {
	}
	return ret;
}

bool cliMain(void) {
	bool ret = false;

	if (uartAvailable(cli_ch) > 0) {

		uint8_t rxData = uartRead(cli_ch);
		if (rxData == '\r') {
			cli_buf[cli_buf_index] = 0;
			cli_buf_index = 0;
			uartPrintf(cli_ch, "\r\n");

			// run cmd
			char *tok;
			char *str_ptr = cli_buf;

			cli_argc = 0;
			while ((tok = strtok_r(str_ptr, " ", &str_ptr)) != NULL) {
				cli_argv[cli_argc++] = tok;
			}
			for (int i = 0; i < cli_cmd_count; ++i) {
				if (cli_cmd_func[i].cmd_func != NULL) {
					if (strcmp(cli_argv[0], cli_cmd_func[i].cmd_str) == 0) {
						cli_cmd_func[i].cmd_func(cli_argc - 1, (const char**) &cli_argv[1]);
						ret = true;
						break;
					}
				}
			}
			uartPrintf(cli_ch, "cli# ");

		} else if (rxData == 0x08) {
			if (cli_buf_index > 0) {
				cli_buf_index--;
				uartPrintf(cli_ch, "\b \b");
			}
		} else if (cli_buf_index < (128 - 1)) {
			cli_buf[cli_buf_index++] = rxData;
			uartWrite(cli_ch, &rxData, 1);
		}
	}
	return ret;
}
bool cliIsStr(const char *p_arg, const char *p_str){
	bool ret = false;
	if (strcmp(p_arg, p_str) == 0) {
		ret = true;
	}
	return ret;
}
int32_t cliGetData(const char *p_arg){
	int32_t ret;
	ret = (int32_t)strtoul(p_arg, (char**)NULL, 0);
}

bool cliKeepLoop(void){
	bool ret = false;
	if (uartAvailable(cli_ch) == 0) {
		ret = true;
	}
	return ret;
}


