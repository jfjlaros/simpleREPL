#include "io.h"

/*
 *
void _IO::write(string data) {
  cout << data;
}
 */


/*
 *
 */
string REPLIO::read(void) {
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

/*
 *
 */
string REPLIO::read(size_t size) {
  string data;

  cin >> data;

  return data;
}

/*
 *
 */
bool REPLIO::eol(void) {
  return _endOfLine;
}


/*
 *
 */
CLIIO::CLIIO(int argc, char** argv) {
  _argc = argc;
  _argv = argv;
}

/*
 *
 */
string CLIIO::read(void) {
  _number++;

  return _argv[_number];
}

/*
 *
 */
bool CLIIO::eol(void) {
  return _number >= _argc - 1;
}
