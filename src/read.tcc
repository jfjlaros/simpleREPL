#ifndef SIMPLE_REPL_READ_TCC_
#define SIMPLE_REPL_READ_TCC_

#include <boost/io/detail/quoted_manip.hpp>

#include "types.tcc"


void _read(string *data) {
  cin >> boost::io::quoted(*data);
}

template<class T>
void _read(T *data) {
  if (!(cin >> *data)) {
    cout << "Error: expected parameter of type " << _typeof(*data) << endl;
    cin.clear();
    cin.ignore();
  }
}

#endif
