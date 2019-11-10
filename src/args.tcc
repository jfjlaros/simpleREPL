#ifndef SIMPLE_REPL_ARGS_TCC_
#define SIMPLE_REPL_ARGS_TCC_

#include "io.tcc"
#include "tuple.tcc"

extern RWIO IO;


/*
 * Set default values and count the number of required parameters.
 */
inline int _setDefault(Tuple<>&, Tuple<>&, int count) {
  return count;
}

template <class T, class... Tail>
int _setDefault(T& argv, Tuple<PARG, Tail...>& defs, int count) {
  _convert(&argv.head, "0"); // Not strictly needed, but nice for debugging.

  return _setDefault(argv.tail, defs.tail, count + 1);
}

template <class T, class U>
int _setDefault(T& argv, U& defs, int count) {
  argv.head = defs.head.tail.head;

  return _setDefault(argv.tail, defs.tail, count);
}

template <class T, class U>
int setDefault(T& argv, U& defs) {
  return _setDefault(argv, defs, 0);
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
