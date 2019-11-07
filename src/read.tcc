#ifndef SIMPLE_REPL_READ_TCC_
#define SIMPLE_REPL_READ_TCC_

#include <boost/io/detail/quoted_manip.hpp>

#include "types.tcc"

bool _endOfLine = false;


string _readToken(void) {
  string data = "";
  bool quoted = false;
  char c = ' ';

  _endOfLine = false;

  while (c == ' ' || c == '\t') {
    c = getc(stdin);
  }

  while (c != '\n') {
    if (!quoted && (c == ' ' || c == '\t')) {
      return data;
    }
    else if (c == '\\') {
      data += getc(stdin);
    }
    else if (c == '"') {
      quoted = !quoted;
    }
    else {
      data += c;
    }

    c = getc(stdin);
  }

  _endOfLine = true;

  return data;
}


void _convert(bool* data, string s) {
  *data = (bool)stoi(s);
}

void _convert(int* data, string s) {
  *data = stoi(s);
}

void _convert(float* data, string s) {
  *data = stof(s);
}

void _convert(double* data, string s) {
  *data = stod(s);
}

void _convert(string* data, string s) {
  *data = s;
}


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
