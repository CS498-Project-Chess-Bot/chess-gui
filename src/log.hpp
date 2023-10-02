#ifndef LOG_HPP
#define LOG_HPP

#include "core.hpp"

#define CORE_ASSERT(x, ...) { if(!(x)) { std::cerr << "ERROR: ASSERTION FAILED - " << __VA_ARGS__ << std::endl; }}


#endif