#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <stdio.h>

#include <string>

enum log_level_t { log_level_debug = 0, log_level_info = 1, log_level_warn, log_level_error };

void log_internal(const char *src_file, int src_line, log_level_t level, const char *format, ...)
	__attribute__((format (printf, 4, 5)));

void vlog_internal(const char *src_file, int src_line, log_level_t level, const char *format, va_list args);

#define logERR(fmt, args...) log_internal(__FILE__, __LINE__, log_level_error, (fmt), ##args)

#define vlogERR(fmt, args) vlog_internal(__FILE__, __LINE__, log_level_error, (fmt), (args))

#endif	// LOGGER_HPP_