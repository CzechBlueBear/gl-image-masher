#include <cstdlib>
#include <iostream>
#include "panic.hpp"

void doPanic(const char *sourceFile, int line, const char *functionName, const std::string &message)
{
	std::cerr << "panic (unrecoverable error): " << sourceFile << ":" << line
		<< ": " << functionName << ": " << message << std::endl;
	::exit(2);
}
