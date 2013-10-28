#include "errors.hpp"

#include <stdarg.h>

#include "logger.hpp"
#include "clustering/administration/logger.hpp"
#include "utils.hpp"

static __thread bool crashed = false;	// to prevent crashing within crashes

void report_fatal_error(const char *file, int line, const char *msg, ...) {
//	fprintf(stderr, "Version: %s\n", RETHINKDB_VERSION_STR);
	if (crashed) {
		va_list args;
		va_start(args, msg);
		fprintf(stderr, msg, args);
		vfprintf(stderr, msg, args);
		va_end(args);
		return;
	}
	
	crashed = true;
	
//	thread_log_writer_disabler_t disabler;
	
	va_list args;
	va_start(args, msg);
	logERR("Error in %s at line %d:", file, line);
	vlogERR(msg, args);
	va_end(args);
	
	logERR("Exiting.");
}