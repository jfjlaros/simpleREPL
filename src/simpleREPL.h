#ifndef SIMPLE_REPL_H_
#define SIMPLE_REPL_H_

/**
 * @file simpleREPL.h
 *
 * REPL interface.
 */
#include "interface.tcc"


/*
/// @private
byte _ping(byte data) {
  return data;
}
*/


/**
 * REPL interface.
 *
 * This function expects parameter pairs (function pointer, documentation).
 *
 * @param args Parameter pairs (function pointer, documentation).
 */
template <class... Args>
bool interface(Args... args) {
  return replInterface(args...);
}

#endif
