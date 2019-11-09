#include "help.tcc"
#include "io.tcc"

#include "read.tcc"
#include "tuple.tcc"
#include "types.tcc"


#define PARG Tuple<const char*, const char*>
#define param(args...) pack(args)
#define params(args...) pack(args)

RWIO IO;


/*
 * Debug function.
 */
template <class... Args>
void show(Args...) {
  IO.write(__PRETTY_FUNCTION__, "\n");
}


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
void interface(T (*f)(Tail...), const char* name, string descr, U defs) {
  Tuple<Tail...> argv;
  string token = "";
  int requiredParameters = setDefault(argv, defs),
      number = 0;

  while (!IO.eol()) {
    token = IO.read();

    if (token[0] == '-') {
      updateOptional(argv, defs, token);
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
    IO.write("Too many parameters provided.\n");
  }
  else {
    IO.write("Required parameter missing.");
  }
}


/*
 * Test.
 */
long f(int i, string s, bool b, float g, int j) {
  IO.write("f: ", i, " ", s, " ", b, " ", g, " ", j, "\n");

  return 0;
}


int main(int argc, char** argv) {
  //IO = RWIO(argc, argv);

  help(f, "f", "funk the func", params(
    param("-a", 2, "set the int"),
    param("name", "name the name"),
    param("-c", true, "flip the flop"),
    param("-d", 3.14F, "pimp the pi"),
    param("value", "set the value")));

  IO.write("\n");

  interface(f, "f", "funk the func", params(
    param("-a", 2, "set the a"),
    param("name", "name the name"),
    param("-c", true, "flip the flop"),
    param("-d", 3.14F, "pimp the pi"),
    param("value", "set the value")));

  return 0;
}
