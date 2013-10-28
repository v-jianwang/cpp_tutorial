#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <inttypes.h>
#include <string>

#include "containers/printf_buffer.hpp"


class startup_shutdown_t {
public:
	startup_shutdown_t();
	~startup_shutdown_t();
};


int64_t round_up_to_power_of_two(int64_t x);

int randint(int n);

std::string strprintf(const char *format, ...) __attribute__((format (printf, 1, 2)));
//std::string vstrprintf(const char *format, va_list ap) __attribute__((format (printf, 1, 0)));

#define MSTR(x) stringify(x) // Stringify a macro
#if defined __clang__
#define COMPILER "CLANG " __clang_version__
#elif defined __GNUC__
#define COMPILER "GCC " MSTR(__GNUC__) "." MSTR(__GNUC_MINOR__) "." MSTR(__GNUC_PATCHLEVEL__)
#else
#define COMPILER "UNKNOWN COMPILER"
#endif


#ifndef NDEBUG
#define RETHINKDB_VERSION_STR "rethinkdb " RETHINKDB_VERSION " (debug)" " (" COMPILER ")"
#else
#define RETHINKDB_VERSION_STR "rethinkdb " RETHINKDB_VERSION " (" COMPILER ")"
#endif


#endif /* UTILS_HPP_ */
