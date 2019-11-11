#ifndef SIMPLE_REPL_ARGS_TCC_
#define SIMPLE_REPL_ARGS_TCC_

#include "io.tcc"
#include "tuple.tcc"

extern RWIO IO;


/*
 * Count parameters.
 */
inline void _countArgs(Tuple<>&, int& req, int& opt) {}

template <PARG_T>
void _countArgs(PARG& defs, int& req, int& opt) {
  _countArgs(defs.tail, ++req, opt);
}

template <class D>
void _countArgs(D& defs, int& req, int& opt) {
  _countArgs(defs.tail, req, ++opt);
}

template <class D>
void countArgs(D& defs, int& req, int& opt) {
  _countArgs(defs, req = 0, opt = 0);
}


/*
 * Set default values and count the number of required parameters.
 */
inline void setDefault(Tuple<>&, Tuple<>&) {}

template <class A, PARG_T>
void setDefault(A& argv, PARG& defs) {
  _convert(&argv.head, "0"); // Not strictly needed, but nice for debugging.
  setDefault(argv.tail, defs.tail);
}

template <class A, class D>
void setDefault(A& argv, D& defs) {
  argv.head = defs.head.tail.head;
  setDefault(argv.tail, defs.tail);
}


/*
 * Update a required parameter value.
 */
inline void _updateRequired(Tuple<>&, Tuple<>&, int, int, string&) {}

template <class A, PARG_T>
void _updateRequired(A& argv, PARG& defs, int num, int count, string& value) {
  if (num == count) {
    _convert(&argv.head, value);
    return;
  }

  _updateRequired(argv.tail, defs.tail, num, count + 1, value);
}

template <class A, class D>
void _updateRequired(A& argv, D& defs, int num, int count, string& value) {
  _updateRequired(argv.tail, defs.tail, num, count, value);
}

template <class A, class D>
void updateRequired(A& argv, D& defs, int num, string& value) {
  _updateRequired(argv, defs, num, 0, value);
}


/*
 * Update an optional parameter value.
 */
inline void updateOptional(Tuple<>&, Tuple<>&, string) {}

template <class... Tail, class D>
void updateOptional(Tuple<bool, Tail...>& argv, D& defs, string name) {
  if (defs.head.head == name) {
    argv.head = !argv.head;
    return;
  }

  updateOptional(argv.tail, defs.tail, name);
}

template <class H, class... Tail, class D>
void updateOptional(Tuple<H, Tail...>& argv, D& defs, string name) {
  if (defs.head.head == name) {
    _convert(&argv.head, IO.read());
    return;
  }

  updateOptional(argv.tail, defs.tail, name);
}

#endif
