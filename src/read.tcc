#ifndef SIMPLE_REPL_READ_TCC_
#define SIMPLE_REPL_READ_TCC_

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
