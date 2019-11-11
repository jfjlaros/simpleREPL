#ifndef SIMPLE_REPL_ARGS_TCC_
#define SIMPLE_REPL_ARGS_TCC_

#include "io.tcc"
#include "tuple.tcc"

extern RWIO IO;


/*
 * Count parameters.
 */
inline void _countArgs(Tuple<>&, int& req, int& opt) {}

template <class... Tail>
void _countArgs(Tuple<PARG, Tail...>& defs, int& req, int& opt) {
  _countArgs(defs.tail, ++req, opt);
}

template <class U>
void _countArgs(U& defs, int& req, int& opt) {
  _countArgs(defs.tail, req, ++opt);
}

template <class U>
void countArgs(U& defs, int& req, int& opt) {
  _countArgs(defs, req = 0, opt = 0);
}


/*
 * Set default values and count the number of required parameters.
 */
inline void setDefault(Tuple<>&, Tuple<>&) {}

template <class T, class... Tail>
void setDefault(T& argv, Tuple<PARG, Tail...>& defs) {
  _convert(&argv.head, "0"); // Not strictly needed, but nice for debugging.

  setDefault(argv.tail, defs.tail);
}

template <class T, class U>
void setDefault(T& argv, U& defs) {
  argv.head = defs.head.tail.head;

  setDefault(argv.tail, defs.tail);
}


/*
 * Update a required parameter value.
 */
inline void _updateRequired(Tuple<>&, Tuple<>&, int, int, string) {}

template <class T, class... Tail>
void _updateRequired(
    T& argv, Tuple<PARG, Tail...>& defs, int number, int count, string value) {
  if (number == count) {
    _convert(&argv.head, value);

    return;
  }

  _updateRequired(argv.tail, defs.tail, number, count + 1, value);
}

template <class T, class U>
void _updateRequired(T& argv, U& defs, int number, int count, string value) {
  _updateRequired(argv.tail, defs.tail, number, count, value);
}

template <class T, class U>
void updateRequired(T& argv, U& defs, int number, string value) {
  _updateRequired(argv, defs, number, 0, value);
}


/*
 * Update an optional parameter value.
 */
inline void updateOptional(Tuple<>&, Tuple<>&, string) {}

template <class... Tail, class U>
void updateOptional(Tuple<bool, Tail...>& argv, U& defs, string name) {
  if (defs.head.head == name) {
    argv.head = !argv.head;

    return;
  }

  updateOptional(argv.tail, defs.tail, name);
}

template <class T, class... Tail, class U>
void updateOptional(Tuple<T, Tail...>& argv, U& defs, string name) {
  if (defs.head.head == name) {
    _convert(&argv.head, IO.read());

    return;
  }

  updateOptional(argv.tail, defs.tail, name);
}

#endif
