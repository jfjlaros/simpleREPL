#ifndef SIMPLE_REPL_TUPLE_TCC_
#define SIMPLE_REPL_TUPLE_TCC_

/**
 * @file tuple.tcc
 *
 * @a Tuple and @a Object definitions and manipulation functions.
 */

/**
 * Empty tuple.
 *
 * @private
 */
template <class... Args>
struct Tuple {};

/**
 * Nested tuple.
 */
template <class T, class... Args>
struct Tuple<T, Args...> {
  T head;              ///< First element.
  Tuple<Args...> tail; ///< Remaining elements.
};


/**
 * Make a nested tuple from a list of parameters.
 *
 * @param args Values to store in a nested tuple.
 *
 * @return Nested tuple containing @a args.
 */
template <class... Args>
Tuple<Args...> pack(Args... args) {
  Tuple<Args...> t = {args...};

  return t;
}

#endif
