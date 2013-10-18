#include "clustering/administration/main/options.hpp"

namespace options {

option_t::option_t(const names_t _names, const appearance_t appearance)
	: names(_names.names),
	  default_values() {
	
}

option_t::option_t(const names_t _names, const appearance_t appearance, std::string default_value)
	: names(_names.names),
	  default_values(1, default_value) {
	
}

}