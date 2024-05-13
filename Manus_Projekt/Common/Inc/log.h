/*
 * log.h
 *
 *  Created on: Oct 6, 2023
 *      Author: Sander
 */

#ifndef INC_LOG_H_
#define INC_LOG_H_

#include <stdint.h>
#include "led.h"

#define n 1000
extern char buffer [n];

#define LOGLEVEL_OFF        (99)
#define LOGLEVEL_TRACE      (1)
#define LOGLEVEL_DEBUG      (2)
#define LOGLEVEL_WARN       (3)
#define LOGLEVEL_ERROR      (4)
#define USELOGLEVEL LOGLEVEL_TRACE

void _log_process_msg(char* msg, uint16_t len);

#define LOG_AT_LOG_LEVEL(LOGLEVEL, TYPE, FORMAT, ...) {\
	if (LOGLEVEL >= USELOGLEVEL){ \
		uint16_t len = snprintf(buffer, n,"%lu:%s:"TYPE":"FORMAT":\n", HAL_GetTick(),__func__,##__VA_ARGS__);\
		_log_process_msg(buffer, len);\
		}\
	if (LOGLEVEL == LOGLEVEL_ERROR){ \
		LED_Red_Write(1);\
	}\
}

#define LOG_PRINT(FORMAT, ...){\
		if (1 >= USELOGLEVEL){ \
			uint16_t len = snprintf(buffer, n, FORMAT"\n", ##__VA_ARGS__);\
			_log_process_msg(buffer, len);\
		}\
}

#define LOG_TRACE(FORMAT, ...)   LOG_AT_LOG_LEVEL(LOGLEVEL_TRACE, "TRACE", FORMAT, ##__VA_ARGS__)
#define LOG_DEBUG(FORMAT, ...)   LOG_AT_LOG_LEVEL(LOGLEVEL_DEBUG, "DEBUG", FORMAT, ##__VA_ARGS__)
#define LOG_WARNING(FORMAT, ...)   LOG_AT_LOG_LEVEL(LOGLEVEL_WARN, "WARNING", FORMAT, ##__VA_ARGS__)
#define LOG_ERROR(FORMAT, ...)   LOG_AT_LOG_LEVEL(LOGLEVEL_ERROR, "ERROR", FORMAT, ##__VA_ARGS__)




#endif /* INC_LOG_H_ */
