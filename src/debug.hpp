#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <string>

#define complain(message) { doComplain(__FILE__, __LINE__, __func__, message); }

void doComplain(const char *sourceFile, int sourceLine, const char *fn, const std::string &message);

#endif
