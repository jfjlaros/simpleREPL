#include <iostream>

using namespace std;

#include "tuple.tcc"
#include "types.tcc"
#include "write.tcc"

struct Required {};

#define _req Required()


/*
 * Make a parameter list.
 */
template <class T, class... Args>
Tuple<Args...> f2t(T (*)(Args...)) {
  Tuple<Args...> t;

  return t;
}


/*
 * Update a parameter list with default values.
 */
inline void update(Tuple<>&, Tuple<>&) {}

template <class T, class U, class... Args>
void update(T& t, Tuple<U, Required, Args...>& u){
  update(t.tail, u.tail.tail);
}

template <class T, class U>
void update(T& t, U& u) {
  t.head = u.tail.head;
  update(t.tail, u.tail.tail);
}


/*
 * Modify a parameter list.
 */
template <class T>
inline void modify(Tuple<>&, Tuple<>&, string, T) {}

template <class U, class... Args, class V, class T>
void modify(Tuple<U, Args...>& t, V& u, string name, T value) {
  if (u.head == name) {
    t.head = *(U*)&value;
    return;
  }

  modify(t.tail, u.tail.tail, name, value);
}


/*
 * Debug function.
 */
template <class... Args>
void show(Args...) {
  cout << __PRETTY_FUNCTION__ << endl;
}


/*
 * Test.
 */
long f(int, string, bool, float, int) {
  return 0;
}

template <class T, class... Args, class U>
void test(T (*f)(Args...), U u) {
  Tuple<Args...> t;

  cout << "Uninitialised." << endl;
  _write(&t);

  update(t, u);
  cout << "Defaults added." << endl;
  _write(&t);

  modify(t, u, "b", (string)"hello");
  modify(t, u, "e", 18);
  cout << "Required parameters provided." << endl;
  _write(&t);

  modify(t, u, "c", false);
  modify(t, u, "d", (float)1.2);
  cout << "Optional parameters provided." << endl;
  _write(&t);
}


int main(void) {
  /* Example.

    void f(int a, string b, bool c, float d, int e) {}

  "a" optional, default value = 2.
  "b" mandatory.
  "c" a flag, default value = true.
  "d" optional, default value = 3.14.
  "e" mandatory.

    ("a", 2, "b", _req, "c", true, "d", 3.14, "e", _req)

  Make tuple:

    (int 2, string undef, bool true, float 3.14, int undef)

    f -d 1.2 "hello" -c 18

  var = 0
  update "d"
  update 1st _req ("b"); var++
  update "c" (negate)
  update 2nd _req ("e"); var++

  call f
  */

  test(f, pack("a", 2, "b", _req, "c", true, "d", 3.14, "e", _req));

  return 0;
}
