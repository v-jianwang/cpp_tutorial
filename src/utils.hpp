#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <inttypes.h>
#include <string>


class startup_shutdown_t {
public:
	startup_shutdown_t();
	~startup_shutdown_t();
};


std::string strprintf(const char *format, ...) __attribute__((format (printf, 1, 2)));
//std::string vstrprintf(const char *format, va_list ap) __attribute__((format (printf, 1, 0)));



#endif /* UTILS_HPP_ */
