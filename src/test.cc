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
 * Count the number of required parameters.
 */
inline int requiredParameters(Tuple<>&, int count) {
  return count;
}

template <class T, class... Tail>
int requiredParameters(Tuple<T, Required, Tail...>& t, int count) {
  return requiredParameters(t.tail.tail, count + 1);
}

template <class T>
int requiredParameters(T& t, int count) {
  return requiredParameters(t.tail.tail, count);
}


/*
 * Check whether a parameter is a boolean.
 */
inline bool isFlag(Tuple<>&, Tuple<>&, string) {
  return false;
}

template <class... Tail, class U>
bool isFlag(Tuple<bool, Tail...>& t, U& u, string name) {
  if (u.head == name) {
    return true;
  }

  return isFlag(t.tail, u.tail.tail, name);
}

template <class T, class U>
bool isFlag(T& t, U& u, string name) {
  return isFlag(t.tail, u.tail.tail, name);
}


/*
 * Set default parameter values.
 */
inline void setDefault(Tuple<>&, Tuple<>&) {}

template <class T, class U, class... Tail>
void setDefault(T& t, Tuple<U, Required, Tail...>& u) {
  _convert(&t.head, "0"); // Not strictly needed, but nice for debugging.
  setDefault(t.tail, u.tail.tail);
}

template <class T, class U>
void setDefault(T& t, U& u) {
  t.head = u.tail.head;
  setDefault(t.tail, u.tail.tail);
}


/*
 * Update an optional parameter value.
 */
inline void updateOptional(Tuple<>&, Tuple<>&, string, string) {}

template <class T, class... Tail, class U>
void updateOptional(Tuple<T, Tail...>& t, U& u, string name, string value) {
  if (u.head == name) {
    _convert(&t.head, value);
    return;
  }

  updateOptional(t.tail, u.tail.tail, name, value);
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
 * Update a flag.
 */
inline void updateFlag(Tuple<>&, Tuple<>&, string) {}

template <class... Tail, class U>
void updateFlag(Tuple<bool, Tail...>& t, U& u, string name) {
  if (u.head == name) {
    t.head = !t.head;
    return;
  }

  updateFlag(t.tail, u.tail.tail, name);
}

template <class T, class U>
void updateFlag(T& t, U& u, string name) {
  updateFlag(t.tail, u.tail.tail, name);
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


template <class T, class... Tail, class U>
void interface(T (*f)(Tail...), U u) {
  int required = requiredParameters(u, 0),
      number = 0;
  string line,
         parameter,
         value;
  istringstream iss;
  Tuple<Tail...> t;

  setDefault(t, u);

  getline(cin, line);
  iss.str(line);

  while (iss >> parameter) {
    if (parameter[0] == '-') {
      parameter.erase(0, 1);

      if (isFlag(t, u, parameter)) {
        updateFlag(t, u, parameter);
      }
      else {
        iss >> value;
        updateOptional(t, u, parameter, value);
      }
    }
    else {
      updateRequired(t, u, number, 0, parameter);
      number++;
    }
  }

  if (number >= required) {
    call((void (*)(Tail...))f, f, t);
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
  while (cin) {
    interface(f, pack("a", 2, "b", _req, "c", true, "d", 3.14F, "e", _req));
  }

  return 0;
}
