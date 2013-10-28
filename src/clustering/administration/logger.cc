#include "clustering/administration/logger.hpp"

#include <stdarg.h>

#include "logger.hpp"

void log_internal(const char *src_file, int src_line, log_level_t level, const char *format, ...) {
	va_list args;
	va_start(args, format);
	vlog_internal(src_file, src_line, level, format, args);
	va_end(args);
}

void vlog_internal(const char *src_file, int src_line, log_level_t level, 
		const char *format, va_list args) {
//	thread_pool_log_writer_t *writer;
//	if ((writer = TLS_get_global_log_writer()) && TLS_get_log_writer_block() == 0) {
//		auto_drainer_t::lock_t lock(TLS_get_global_log_drainer());
//		
//		std::string message = vstrprintf(format, args);
//		coro_t::spawn_sometime(boost::bind(&log_coro, writer, level, message, lock));
//	}
//	else {
//		std::string message = vstrprintf(format, args);
//		fallback_log_writer.initiate_write(level, message);
//	}
	char *msg = new char[100];
	vsnprintf(msg, 100, format, args);	
	if (level == log_level_error) {
		printf("In %s:%d: error: %s\n", src_file, src_line, msg);
	}
	else {
		printf("Unknown log level.\n");
	}
	delete[] msg;
}