#include "io.tcc"

/*
 *
 */
RWIO::RWIO(int argc, char** argv) {
  _ioREPL = false;
  _argc = argc;
  _argv = argv;
}

/*
 *
 */
string RWIO::read(void) {
  string data = "";
  bool quoted = false;
  char c = ' ';

  if (_ioREPL) {
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

  _number++;

  return _argv[_number];
}


/*
 *
 */
bool RWIO::eol(void) {
  if (_ioREPL) {
    return _endOfLine;
  }

  return _number >= _argc - 1;
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
