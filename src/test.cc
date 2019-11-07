#include <iostream>
#include <sstream>

using namespace std;

#include "read.tcc"
#include "tuple.tcc"
#include "types.tcc"
#include "write.tcc"

struct Required {};

#define _req Required()


/*
 * Debug function.
 */
template <class... Args>
void show(Args...) {
  cout << __PRETTY_FUNCTION__ << endl;
}


/*
 * Set default values and count the number of required parameters.
 */
inline int _setDefault(Tuple<>&, Tuple<>&, int count) {
  return count;
}

template <class T, class U, class... Tail>
int _setDefault(T& argv, Tuple<U, Required, Tail...>& defs, int count) {
  _convert(&argv.head, "0"); // Not strictly needed, but nice for debugging.

  return _setDefault(argv.tail, defs.tail.tail, count + 1);
}

template <class T, class U>
int _setDefault(T& argv, U& defs, int count) {
  argv.head = defs.tail.head;

  return _setDefault(argv.tail, defs.tail.tail, count);
}

template <class T, class U>
int setDefault(T& argv, U& defs) {
  return _setDefault(argv, defs, 0);
}


/*
 * Update a required parameter value.
 */
inline void _updateRequired(Tuple<>&, Tuple<>&, int, int, string) {}

template <class T, class U, class... Tail>
void _updateRequired(
    T& argv, Tuple<U, Required, Tail...>& defs,
    int number, int count, string value) {
  if (number == count) {
    _convert(&argv.head, value);

    return;
  }

  _updateRequired(argv.tail, defs.tail.tail, number, count + 1, value);
}

template <class T, class U>
void _updateRequired(T& argv, U& defs, int number, int count, string value) {
  _updateRequired(argv.tail, defs.tail.tail, number, count, value);
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
  if (defs.head == name) {
    argv.head = !argv.head;

    return;
  }

  updateOptional(argv.tail, defs.tail.tail, name);
}

template <class T, class... Tail, class U>
void updateOptional(Tuple<T, Tail...>& argv, U& defs, string name) {
  if (defs.head == name) {
    _convert(&argv.head, _readToken());

    return;
  }

  updateOptional(argv.tail, defs.tail.tail, name);
}


/*
 * Call a function.
 */
template <class F, class... Args>
void _call(void (*)(void), F f, Tuple<>&, Args&... args) {
  f(args...);
}

template <class T, class... Tail, class F, class U, class... Args>
void _call(void (*f_)(T, Tail...), F f, U& argv, Args&... args) {
  _call((void (*)(Tail...))f_, f, argv.tail, args..., argv.head);
}

template <class T, class... Tail, class U>
void call(T (*f)(Tail...), U& argv) {
  _call((void (*)(Tail...))f, f, argv);
}


/*
 * Parse command line parameters.
 */
template <class T, class... Tail, class U>
void interface(T (*f)(Tail...), U defs) {
  Tuple<Tail...> argv;
  string token;
  int requiredParameters = setDefault(argv, defs),
      number = 0;

  while (!_endOfLine) {
    token = _readToken();

    if (token[0] == '-') {
      updateOptional(argv, defs, token.substr(1, string::npos));
    }
    else {
      updateRequired(argv, defs, number, token);
      number++;
    }
  }

  if (number == requiredParameters) {
    call(f, argv);
  }
  else if (number > requiredParameters) {
    cout << "Too many parameters provided." << endl;
  }
  else {
    cout << "Required parameter missing." << endl;
  }
}


/*
 * Test.
 */
long f(int i, string s, bool b, float g, int j) {
  cout << "f: " << i << " " << s << " " << b << " " << g << " " << j << endl;

  return 0;
}


int main(void) {
  string s;

  while (!feof(stdin)) {
    s = _readToken(); // Command.
    interface(f, pack("a", 2, "b", _req, "c", true, "d", 3.14F, "e", _req));
  }

  return 0;
}
