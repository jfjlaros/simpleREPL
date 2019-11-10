#ifndef SIMPLE_REPL_HELP_TCC_
#define SIMPLE_REPL_HELP_TCC_

#include "io.tcc"
#include "types.tcc"
#include "tuple.tcc"


/*
 * Help on required parameters.
 */
void _helpRequired(void (*)(void), Tuple<>&) {}

template <class T, class... Tail, class... Args>
void _helpRequired(void (*f)(T, Tail...), Tuple<PARG, Args...>& argv) {
  T data;

  IO.write(
    "  ", argv.head.head, "\t\t", argv.head.tail.head, " (type ",
    _typeof(data), ")\n");
  _helpRequired((void (*)(Tail...))f, argv.tail);
}

template <class T, class... Tail, class U>
void _helpRequired(void (*f)(T, Tail...), U& argv) {
  _helpRequired((void (*)(Tail...))f, argv.tail);
}


/*
 * Help on optional parameters.
 */
void _helpOptional(void (*)(void), Tuple<>&) {}

template <class T, class... Tail, class... Args>
void _helpOptional(void (*f)(T, Tail...), Tuple<PARG, Args...>& argv) {
  _helpOptional((void (*)(Tail...))f, argv.tail);
}

template <class... Tail, class U>
void _helpOptional(void (*f)(bool, Tail...), U& argv) {
  IO.write(
    "  ", argv.head.head, "\t\t", argv.head.tail.tail.head, " (type flag)\n");
  _helpOptional((void (*)(Tail...))f, argv.tail);
}

template <class T, class... Tail, class U>
void _helpOptional(void (*f)(T, Tail...), U& argv) {
  T data;

  IO.write(
    "  ", argv.head.head, "\t\t", argv.head.tail.tail.head, " (type ",
    _typeof(data), ", default: ", argv.head.tail.head, ")\n");
  _helpOptional((void (*)(Tail...))f, argv.tail);
}


/*
 * Help on return type.
 */
template <class... Tail>
void returnType(void (*)(Tail...)) {}

template <class T, class... Tail>
void returnType(T (*)(Tail...)) {
  T data;

  IO.write("\nreturns:\n  ", _typeof(data), "\n");
}


/*
 * Help.
 */
template <class T, class... Tail, class U>
void _help(T (*f)(Tail...), string name, string descr, U& argv) {
  IO.write(name, ": ", descr, "\n\n");

  IO.write("positional arguments:\n");
  _helpRequired((void (*)(Tail...))f, argv);

  IO.write("\noptional arguments:\n");
  _helpOptional((void (*)(Tail...))f, argv);

  returnType(f);
}


/*
 * Help selector.
 */
void help(string) {}

template <class C, class R, class P, class... Z, class... Tail, class... Args>
void help(
    string name, Tuple<Tuple<C*, R (P::*)(Z...)>, Tail...> t, Args... args) {
  if (t.tail.head == name) {
    _help(
      (R (*)(Z...))t.head.tail.head, t.tail.head, t.tail.tail.head,
      t.tail.tail.tail);
    return;
  }

  help(name, args...);
}

template <class T, class... Args>
void help(string name, T t, Args... args) {
  if (t.tail.head == name) {
    _help(t.head, t.tail.head, t.tail.tail.head, t.tail.tail.tail);
    return;
  }

  help(name, args...);
}


/*
 * Short description of all available functions.
 */
void describe(void) {}

template <class T, class... Args>
void describe(T t, Args... args) {
  IO.write(t.tail.head, "\t\t", t.tail.tail.head, "\n");
  describe(args...);
}

#endif
