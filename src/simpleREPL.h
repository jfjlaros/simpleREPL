#ifndef SIMPLE_REPL_H_
#define SIMPLE_REPL_H_

/**
 * @file simpleREPL.h
 *
 * REPL interface.
 */

#include "interface.tcc"


/// @private
int _ping(int data) {
  return data;
}


/**
 * REPL interface.
 *
 * This function expects parameter pairs (function pointer, documentation).
 *
 * @param args Parameter pairs (function pointer, documentation).
 *
 * @return @a true to continue @a false to quit.
 */
template <class... Args>
bool interface(Args... args) {
  return replInterface(
    //_ping, "ping", "Ping.",
    args...);
}

#endif
