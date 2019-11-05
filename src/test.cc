#include <iostream>

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
inline int countRequired(Tuple<>&, int count) {
  return count;
}

template <class T, class... Tail>
int countRequired(Tuple<T, Required, Tail...>& t, int count) {
  return countRequired(t.tail.tail, count + 1);
}

template <class T>
int countRequired(T& t, int count) {
  return countRequired(t.tail.tail, count);
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
    T& t, Tuple<U, Required, Tail...>& u, int number, int count, string value) {
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


/*
 * Test.
 */
long f(int i, string s, bool b, float g, int j) {
  cout << "f: " << i << " " << s << " " << b << " " << g << " " << j << endl;

  return 0;
}

template <class T, class... Tail, class U>
void test(T (*f)(Tail...), U u) {
  Tuple<Tail...> t;

  cout << "Required number of parameters: " << countRequired(u, 0) << endl <<
    endl; 

  setDefault(t, u);
  cout << "Default parameters." << endl;
  _write(&t);

  /*
  1. Set number of required parameters read to 0.
  2. Read one token from stdin, if EOL go to 7.
  3. Check whether token is a name (starts with a dash, has at lease one letter).
  4. If 3. is true, get the type of the parameter and read its value from stdin.
     - NOTE: booleans
  5. If 3. is false, get the type of the next required parameter and read its
    value from stdin.
  6. Go to 2.
  7. If all required parameters have been read, succeed, fail otherwise.
  */

  updateOptional(t, u, "a", "3");
  updateOptional(t, u, "d", "3.15");
  cout << "Optional parameters applied." << endl;
  _write(&t);

  updateFlag(t, u, "c");
  cout << "Flag parameters applied." << endl;
  _write(&t);

  updateRequired(t, u, 0, 0, "hello");
  updateRequired(t, u, 1, 0, "18");
  cout << "Required parameters applied." << endl;
  _write(&t);

  call((void (*)(Tail...))f, f, t);
}


int main(void) {
  /* Example.

    void f(int a, string b, bool c, float d, int e) {}

  "a" optional, default value = 2.
  "b" mandatory.
  "c" a flag, default value = true.
  "d" optional, default value = 3.14F.
  "e" mandatory.

    ("a", 2, "b", _req, "c", true, "d", 3.14F, "e", _req)

  Make tuple:

    (int 2, string undef, bool true, float 3.14F, int undef)

    f -d 1.2 "hello" -c 18

  var = 0
  update "d"
  update 1st _req ("b"); var++
  update "c" (negate)
  update 2nd _req ("e"); var++

  call f
  */

  test(f, pack("a", 2, "b", _req, "c", true, "d", 3.14F, "e", _req));

  return 0;
}
