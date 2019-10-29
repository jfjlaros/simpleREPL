#ifndef SIMPLE_REPL_READ_TCC_
#define SIMPLE_REPL_READ_TCC_


void _read(string *data) {
  bool quoted = false;
  char c = ' ';

  while (c == ' ' || c == '\t') {
    c = getc(stdin);
  }
  while (c != '\n') {
    if (!quoted && (c == ' ' || c == '\t')) {
      break;
    }
    else if (c == '\\') {
      *data += getc(stdin);
    }
    else if (c == '"') {
      quoted = !quoted;
    }
    else {
      *data += c;
    }

    c = getc(stdin);
  }
}

template<class T>
void _read(T *data) {
  cin >> *data;
}

#endif
