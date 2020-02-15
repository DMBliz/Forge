#pragma once
#include <iostream>

namespace Forge
{
#define LOG(x) std::cout << "\033[0;31mError: " << x << "\033[0m\n"
#define LOG_INFO(x) std::cout << "INFO: " << x << std::endl
#define LOG_ERROR(x) std::cout << "ERROR: " << x << std::endl
#define LOG_WARN(x) std::cout << "WARNING: " << x << std::endl
}