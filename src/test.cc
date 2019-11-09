#include "help.tcc"
#include "io.tcc"
#include "args.tcc"

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
