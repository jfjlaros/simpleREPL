#ifndef SIMPLE_REPL_EVAL_TCC_
#define SIMPLE_REPL_EVAL_TCC_

/**
 * @file eval.tcc
 *
 * Read values from stdin, execute a function and write the result to stdout.
 */

#include "tuple.tcc"


/**
 * Execute a function.
 *
 * All parameters have been collected since function pointer @a *f_ has no
 * parameter types. All values are now present in the @a args parameter pack.
 *
 * @param - Dummy function pointer.
 * @param f Function pointer.
 * @param args Parameter pack for @a f.
 *
 * @private
 */
template <VMEMB_T, class... Args>
void _call(void (*)(void), VMEMB t, Tuple<>&, Args&... args) {
  (*t.head.*t.tail.head)(args...);
}

template <class... Tail, class... Args>
void _call(void (*)(void), void (*f)(Tail...), Tuple<>&, Args&... args) {
  f(args...);
}

template <TMEMB_T, class... Args>
void _call(void (*)(void), TMEMB t, Tuple<>&, Args&... args) {
  IO.write((*t.head.*t.tail.head)(args...), "\n");
}

template <class F, class... Args>
void _call(void (*)(void), F f, Tuple<>&, Args&... args) {
  IO.write(f(args...), "\n");
}

template <class H, class... Tail, class F, class U, class... Args>
void _call(void (*f_)(H, Tail...), F f, U& argv, Args&... args) {
  _call((void (*)(Tail...))f_, f, argv.tail, args..., argv.head);
}

template <TMEMB_T, class U>
void call(TMEMB t, U& argv) {
  _call((void (*)(Tail...))t.head, t, argv);
}

template <class R, class... Tail, class U>
void call(R (*f)(Tail...), U& argv) {
  _call((void (*)(Tail...))f, f, argv);
}


/*
 * Parse command line parameters.
 */
template <class F, class U, class V>
bool _parse(F f, U& defs, V& argv) {
  string token = "";
  int req,
      opt,
      number = 0;

  setDefault(argv, defs);

  while (!IO.eol()) {
    token = IO.read();

    if (token[0] == '-') {
      if (!updateOptional(argv, defs, token)) {
        return false;
      }
    }
    else {
      if (!updateRequired(argv, defs, number, token)) {
        return false;
      }
      number++;
    }
  }

  countArgs(defs, req, opt);

  if (number < req) {
    IO.write("Required parameter missing.\n");
    return false;
  }

  call(f, argv);

  return true;
}

template <TMEMB_T, class U>
bool parse(TMEMB t, U defs) {
  Tuple<Tail...> argv;

  return _parse(t, defs, argv);
}

template <class R, class... Tail, class U>
bool parse(R (*f)(Tail...), U defs) {
  Tuple<Tail...> argv;

  return _parse(f, defs, argv);
}


/*
 * Select a function to be executed.
 */
inline bool select(string s) {
  IO.write("Unknown command: ", s, "\n");
  IO.flush();
  return false;
}

template <class T, class... Args>
bool select(string name, T t, Args... args) {
  if (t.tail.head == name) {
    return parse(t.head, t.tail.tail.tail);
  }

  return select(name, args...);
}

#endif
