#include "utils.hpp"

#include "containers/printf_buffer.hpp"

#include <stdarg.h>
#include <stdlib.h>

startup_shutdown_t::startup_shutdown_t() {
	
}

startup_shutdown_t::~startup_shutdown_t() {
	
}


struct nrand_xsubi_t {
	unsigned short xsubi[3];	// NOLINT(runtime/int)
};



int randint(int n) {
//	nrand_xsubi_t buffer;
//	if (!TLS_get_rng_initialized()) {
//		CT_ASSERT(sizeof(buffer.xsubi) == 6);
//		get_dev_urandom(&buffer.xsubi, sizeof(buffer.xsubi));
//		TLS_set_rng_initialized(true);
//	}
//	else {
//		buffer = TLS_get_rng_data();
//	}
//	long x = xrand48(buffer.xsubi);
//	TLS_get_rng_data(buffer);
//	return x % n;
	int rnd = rand() % n;
	return rnd;
}

int64_t round_up_to_power_of_two(int64_t x) {
//	rassert(x >= 0);
	--x;

	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x |= x >> 32;

//	rassert(x < INT64_MAX);

	return x + 1;
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
