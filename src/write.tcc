#ifndef SIMPLE_REPL_WRITE_TCC_
#define SIMPLE_REPL_WRITE_TCC_


/**
 * Write a value of basic type to stdout.
 *
 * @param data Data.
 */
template<class T>
void _write(T *data) {
  cout << *data << endl;
}


/**
 * Recursion terminator for @a _write(Tuple*).
 *
 * @private
 */
inline void _write(Tuple<>*) {
  cout << endl;
}

/**
 * Write a value of type @a Tuple to stdout.
 *
 * @param data Tuple.
 */
template <class T, class... Args>
void _write(Tuple<T, Args...>* data) {
  _write(&(*data).head);
  _write(&(*data).tail);
}

#endif
