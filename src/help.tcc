#ifndef SIMPLE_REPL_HELP_TCC_
#define SIMPLE_REPL_HELP_TCC_

#include "io.tcc"
#include "types.tcc"
#include "tuple.tcc"


/*
 * Help on required parameters.
 */
inline void _helpRequired(void (*)(void), Tuple<>&) {}

template <class H, class... Tail, PARG_T>
void _helpRequired(void (*f)(H, Tail...), PARG& argv) {
  H data;

  IO.write(
    "  ", argv.head.head, "\t\t", argv.head.tail.head, " (type ",
    _typeof(data), ")\n");
  _helpRequired((void (*)(Tail...))f, argv.tail);
}

template <class H, class... Tail, class U>
void _helpRequired(void (*f)(H, Tail...), U& argv) {
  _helpRequired((void (*)(Tail...))f, argv.tail);
}


/*
 * Help on optional parameters.
 */
inline void _helpOptional(void (*)(void), Tuple<>&) {}

template <class H, class... Tail, PARG_T>
void _helpOptional(void (*f)(H, Tail...), PARG& argv) {
  _helpOptional((void (*)(Tail...))f, argv.tail);
}

template <class... Tail, class A>
void _helpOptional(void (*f)(bool, Tail...), A& argv) {
  IO.write(
    "  ", argv.head.head, "\t\t", argv.head.tail.tail.head, " (type flag)\n");
  _helpOptional((void (*)(Tail...))f, argv.tail);
}

template <class H, class... Tail, class A>
void _helpOptional(void (*f)(H, Tail...), A& argv) {
  H data;

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

template <class R, class... Tail>
void returnType(R (*)(Tail...)) {
  R data;

  IO.write("\nreturns:\n  ", _typeof(data), "\n");
}


/*
 * Help.
 */
template <class R, class... Tail, class A>
void help(R (*f)(Tail...), string name, string descr, A& argv) {
  int req,
      opt;

  IO.write(name, ": ", descr, "\n");

  countArgs(argv, req, opt);

  if (req) {
    IO.write("\npositional arguments:\n");
    _helpRequired((void (*)(Tail...))f, argv);
  }

  if (opt) {
    IO.write("\noptional arguments:\n");
    _helpOptional((void (*)(Tail...))f, argv);
  }

  returnType(f);
}

template <TMEMB_T, class A>
void help(TMEMB t, string name, string descr, A& argv) {
  help((R (*)(Tail...))t.tail.head, name, descr, argv);
}


/*
 * Help selector.
 */
inline void selectHelp(string s) {
  IO.err("Unknown command: ", s, "\n");
}

template <class H, class... Tail>
void selectHelp(string name, H t, Tail... args) {
  if (t.tail.head == name) {
    help(t.head, t.tail.head, t.tail.tail.head, t.tail.tail.tail);
    return;
  }

  selectHelp(name, args...);
}


/*
 * Short description of all available functions.
 */
inline void describe(void) {
  IO.flush();
}

template <class H, class... Tail>
void describe(H t, Tail... args) {
  IO.write(t.tail.head, "\t\t", t.tail.tail.head, "\n");
  describe(args...);
}

#endif
