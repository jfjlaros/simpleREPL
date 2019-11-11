#include "io.tcc"


/*
 *
 */
string RWIO::read(void) {
  string data = "";
  bool quoted = false;
  char c = ' ';

  if (_interactive) {
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
  if (_interactive) {
    return _endOfLine;
  }

  return _number >= _argc - 1;
}

/*
 *
 */
bool RWIO::interactive(void) {
  return _interactive;
}

/*
 *
 */
void RWIO::enableCLI(int argc, char** argv) {
  _interactive = false;
  _argc = argc;
  _argv = argv;
}


/*
 *
 */
void _convert(bool* data, string s) {
  *data = (bool)stoi(s);
}

void _convert(char* data, string s) {
  *data = (char)stoi(s);
}

void _convert(signed char* data, string s) {
  *data = (signed char)stoi(s);
}

void _convert(unsigned char* data, string s) {
  *data = (unsigned char)stoi(s);
}

void _convert(short int* data, string s) {
  *data = (short int)stoi(s);
}

void _convert(unsigned short int* data, string s) {
  *data = (unsigned short int)stoi(s);
}

void _convert(int* data, string s) {
  *data = stoi(s);
}

void _convert(unsigned int* data, string s) {
  *data = (unsigned int)stoi(s);
}

void _convert(long int* data, string s) {
  *data = stol(s);
}

void _convert(unsigned long int* data, string s) {
  *data = stoul(s);
}

void _convert(long long int* data, string s) {
  *data = stoll(s);
}

void _convert(unsigned long long int* data, string s) {
  *data = stoull(s);
}

void _convert(float* data, string s) {
  *data = stof(s);
}

void _convert(double* data, string s) {
  *data = stod(s);
}

void _convert(long double* data, string s) {
  *data = stold(s);
}

void _convert(string* data, string s) {
  *data = s;
}
