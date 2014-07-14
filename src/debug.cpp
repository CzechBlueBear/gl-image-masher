#include <iostream>
#include "debug.hpp"

void doComplain(const char *sourceFile, int sourceLine, const char *fn, const std::string &message)
{
	std::cerr << "error (reported by " << sourceFile << ":" << sourceLine
		<< ": " << fn << "): " << message << std::endl;
}
