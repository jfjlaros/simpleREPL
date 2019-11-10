#ifndef SIMPLE_REPL_INTERFACE_TCC_
#define SIMPLE_REPL_INTERFACE_TCC_

/**
 * @file interface.tcc
 *
 * Template library for exporting native C and C++ functions as remote
 * procedure calls.
 *
 * For more information about (variadic) templates:
 * @li http://www.drdobbs.com/cpp/extracting-function-parameter-and-return/240000586
 * @li https://eli.thegreenplace.net/2014/variadic-templates-in-c/
 * @li https://en.cppreference.com/w/cpp/language/parameter_pack
 */

#include "args.tcc"
#include "eval.tcc"
#include "help.tcc"
#include "io.tcc"

#define param(args...) pack(args)
#define func(args...) pack(args)

RWIO IO;


/*
 * Parse command line parameters.
 */
template <class T, class... Tail, class U>
void parse(T (*f)(Tail...), const char* name, string descr, U defs) {
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


/**
 * REPL interface.
 *
 * This function expects parameter pairs (function pointer, name).
 *
 * A command is read from stdin into @a command, if the value equals @a help,
 * we describe the list of functions. Otherwise, we call the function indexed
 * by @a command.
 *
 * @param args Parameter pairs (function pointer, name).
 *
 * @return @a true to continue @a false to quit.
 */
template <class... Args>
bool interface(Args... args) {
  string command;

  IO.write("> ");
  command = IO.read();

  if (command == "exit") {
    return false;
  }
  if (command == "list") {
    describe(args...);
    return true;
  }
  if (command == "help") {
    help(IO.read(), args...);
    return true;
  }

  select(command, args...);

  return true;
}

#endif
