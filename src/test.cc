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
inline int setDefault(Tuple<>&, Tuple<>&, int count) {
  return count;
}

template <class T, class U, class... Tail>
int setDefault(T& t, Tuple<U, Required, Tail...>& u, int count) {
  _convert(&t.head, "0"); // Not strictly needed, but nice for debugging.
  return setDefault(t.tail, u.tail.tail, count + 1);
}

template <class T, class U>
int setDefault(T& t, U& u, int count) {
  t.head = u.tail.head;
  return setDefault(t.tail, u.tail.tail, count);
}


/*
 * Update an optional parameter value.
 */
inline void updateOptional(Tuple<>&, Tuple<>&, string) {}

template <class... Tail, class U>
void updateOptional(Tuple<bool, Tail...>& t, U& u, string name) {
  if (u.head == name) {
    t.head = !t.head;
    return;
  }

  updateOptional(t.tail, u.tail.tail, name);
}

template <class T, class... Tail, class U>
void updateOptional(Tuple<T, Tail...>& t, U& u, string name) {
  if (u.head == name) {
    _convert(&t.head, _readToken());
    return;
  }

  updateOptional(t.tail, u.tail.tail, name);
}

/*
 * Update a required parameter value.
 */
inline void updateRequired(Tuple<>&, Tuple<>&, int, int, string) {}

template <class T, class U, class... Tail>
void updateRequired(
    T& t, Tuple<U, Required, Tail...>& u,
    int number, int count, string value) {
  if (number == count) {
    _convert(&t.head, value);
    return;
  }

  updateRequired(t.tail, u.tail.tail, number, count + 1, value);
}

template <class T, class U>
void updateRequired(T& t, U& u, int number, int count, string value) {
  updateRequired(t.tail, u.tail.tail, number, count, value);
}


/*
 * Call a function.
 */
template <class F, class... Args>
void call(void (*)(void), F f, Tuple<>&, Args&... args) {
  f(args...);
}

template <class T, class... Tail, class F, class U, class... Args>
void call(void (*f_)(T, Tail...), F f, U& t, Args&... args) {
  call((void (*)(Tail...))f_, f, t.tail, args..., t.head);
}


/*
 *
 */
template <class T, class... Tail, class U>
void interface(T (*f)(Tail...), U u) {
  Tuple<Tail...> t;
  string token;
  int requiredParameters = setDefault(t, u, 0),
      number = 0;

  while (!_endOfLine) {
    token = _readToken();

    if (token[0] == '-') {
      updateOptional(t, u, token.substr(1, string::npos));
    }
    else {
      updateRequired(t, u, number, 0, token);
      number++;
    }
  }

  if (number == requiredParameters) {
    call((void (*)(Tail...))f, f, t);
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
