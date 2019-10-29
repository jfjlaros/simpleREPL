#ifndef SIMPLE_REPL_READ_TCC_
#define SIMPLE_REPL_READ_TCC_

#include <boost/io/detail/quoted_manip.hpp>


void _read(string *data) {
  cin >> boost::io::quoted(*data);
}

template<class T>
void _read(T *data) {
  cin >> *data;
}

#endif
