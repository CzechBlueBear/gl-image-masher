#ifndef PANIC_HPP
#define PANIC_HPP

#include <string>

/**
 * Emergency exit macro. Prints a message together with information
 * of where in the source the problem occurred, and terminates
 * the application.
 */
#define panic(message) { doPanic(__FILE__, __LINE__, __func__, message); }

/**
 * Emergency exit routine (normally called via macro panic() that
 * automatically fills in the location in the source code).
 * Terminates the whole application immediately, printing the location
 * in the source code and a specified message.
 * This call does not return.
 */
void doPanic(const char *sourceFile, int line, const char *functionName, const std::string &message);

#endif
