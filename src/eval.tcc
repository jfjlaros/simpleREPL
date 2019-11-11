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
template <class C, class P, class... Tail, class... Args>
void _call(
    void (*)(void), Tuple<C*, void (P::*)(Tail...)> t, Tuple<>&,
    Args&... args) {
  (*t.head.*t.tail.head)(args...);
}

template <class... Tail, class... Args>
void _call(void (*)(void), void (*f)(Tail...), Tuple<>&, Args&... args) {
  f(args...);
}

template <class C, class P, class T, class... Tail, class... Args>
void _call(
    void (*)(void), Tuple<C*, T (P::*)(Tail...)> t, Tuple<>&, Args&... args) {
  IO.write((*t.head.*t.tail.head)(args...), "\n");
}

template <class F, class... Args>
void _call(void (*)(void), F f, Tuple<>&, Args&... args) {
  IO.write(f(args...), "\n");
}

template <class T, class... Tail, class F, class U, class... Args>
void _call(void (*f_)(T, Tail...), F f, U& argv, Args&... args) {
  _call((void (*)(Tail...))f_, f, argv.tail, args..., argv.head);
}

template <class C, class T, class P, class... Tail, class U>
void call(Tuple<C*, T (P::*)(Tail...)> t, U& argv) {
  _call((void (*)(Tail...))t.head, t, argv);
}

template <class T, class... Tail, class U>
void call(T (*f)(Tail...), U& argv) {
  _call((void (*)(Tail...))f, f, argv);
}


/*
 * Parse command line parameters.
 */
template <class T, class U, class V>
void _parse(T f, const char* name, string descr, U& defs, V& argv) {
  string token = "";
  int req,
      opt,
      number = 0;

  setDefault(argv, defs);

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

  countArgs(defs, req, opt);

  if (number == req) {
    call(f, argv);
  }
  else if (number > req) {
    IO.write("Too many parameters provided.\n");
  }
  else {
    IO.write("Required parameter missing.\n");
  }
}

template <class C, class P, class T, class... Tail, class U>
void parse(
    Tuple<C*, T (P::*)(Tail...)> t, const char* name, string descr, U defs) {
  Tuple<Tail...> argv;

  _parse(t, name, descr, defs, argv);
}

template <class T, class... Tail, class U>
void parse(T (*f)(Tail...), const char* name, string descr, U defs) {
  Tuple<Tail...> argv;

  _parse(f, name, descr, defs, argv);
}


/*
 * Select a function to be executed.
 */
void select(string) {}

template <class T, class... Args>
void select(string name, T t, Args... args) {
  if (t.tail.head == name) {
    parse(t.head, t.tail.head, t.tail.tail.head, t.tail.tail.tail);
    return;
  }

  select(name, args...);
}

#endif
