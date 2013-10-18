#include "utils.hpp"

#include "containers/printf_buffer.hpp"

#include <stdarg.h>

startup_shutdown_t::startup_shutdown_t() {
	
}

startup_shutdown_t::~startup_shutdown_t() {
	
}

std::string strprintf(const char *format, ...) {
	std::string ret;

	va_list ap;
	va_start(ap, format);

	printf_buffer_t buf(ap, format);

	ret.assign(buf.data(), buf.data() + buf.size());

	va_end(ap);

	return ret;
}
