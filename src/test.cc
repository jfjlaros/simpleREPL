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

template <class T, class... Args>
int countRequired(Tuple<T, Required, Args...>& t, int count) {
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

template <class T, class U, class... Args>
void setDefault(T& t, Tuple<U, Required, Args...>& u) {
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
template <class T>
inline void updateOptional(Tuple<>&, Tuple<>&, string, T) {}

/*
 * The assignment of @t.head can only be done if the types of @t.head and @a
 * value are the same. It is possible to merge this function with the next one,
 * by using the following construct, but it would not be type safe anymore.
 *
 *     t.head = *(T*)&value;
 */
template <class T, class... Args, class U>
void updateOptional(Tuple<T, Args...>& t, U& u, string name, T value) {
  if (u.head == name) {
    t.head = value;
    return;
  }

  updateOptional(t.tail, u.tail.tail, name, value);
}

template <class T, class... Args, class U, class V>
void updateOptional(Tuple<T, Args...>& t, U& u, string name, V value) {
  updateOptional(t.tail, u.tail.tail, name, value);
}


/*
 * Update a required parameter value.
 */
template <class T>
inline void updateRequired(Tuple<>&, Tuple<>&, int, int, T) {}

/*
 * As mentioned in the documentation of @updateOptional(), this function can be
 * merged with the next one at the cost of type safely.
 */
template <class T, class... Args, class U, class... Tail>
void updateRequired(
    Tuple<T, Args...>& t, Tuple<U, Required, Tail...>& u,
    int number, int count, T value) {
  if (number == count) {
    t.head = value;
    return;
  }

  updateRequired(t.tail, u.tail.tail, number, count + 1, value);
}

template <class T, class U, class... Tail, class V>
void updateRequired(
    T& t, Tuple<U, Required, Tail...>& u, int number, int count, V value) {
  updateRequired(t.tail, u.tail.tail, number, count + 1, value);
}

template <class T, class U, class V>
void updateRequired(T& t, U& u, int number, int count, V value) {
  updateRequired(t.tail, u.tail.tail, number, count, value);
}


/*
 * Flip a flag.
 */
inline void flip(Tuple<>&, Tuple<>&, string) {}

template <class T>
void flip(T& t, T& u, string name) {
  if (u.head == name) {
    t.head = !t.head;
    return;
  }

  flip(t.tail, u.tail.tail, name);
}

template <class T, class U>
void flip(T& t, U& u, string name) {
  flip(t.tail, u.tail.tail, name);
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

template <class T, class... Args, class U>
void test(T (*f)(Args...), U u) {
  Tuple<Args...> t;

  cout << "Required: " << countRequired(u, 0) << endl;

  cout << "Uninitialised." << endl;
  _write(&t);

  setDefault(t, u);
  cout << "Defaults added." << endl;
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

  updateOptional(t, u, "b", string("hello"));
  updateOptional(t, u, "e", 18);
  cout << "Required parameters provided." << endl;
  _write(&t);

  flip(t, u, "c");
  updateOptional(t, u, "d", 1.2F);
  cout << "Optional parameters provided." << endl;
  _write(&t);

  updateRequired(t, u, 0, 0, string("world"));
  _write(&t);
  updateRequired(t, u, 1, 0, 19);
  _write(&t);


  call((void (*)(Args...))f, f, t);

  int i; double d;
  _convert(i, "123");
  _convert(d, "123.456");
  cout << i << " " << d << endl;
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
