#ifndef SIMPLE_REPL_TYPES_TCC_
#define SIMPLE_REPL_TYPES_TCC_

/**
 * Type analysis and encoding.
 */


/*
 * Type naming functions.
 */
inline String _typeof(bool) {
  return "bool";
}

inline String _typeof(char) {
  return "char";
}

inline String _typeof(signed char) {
  return "signed char";
}

inline String _typeof(unsigned char) {
  return "unsigned char";
}

inline String _typeof(short int) {
  return "short int";
}

inline String _typeof(unsigned short int) {
  return "unsigned short int";
}

inline String _typeof(int) {
  return "int";
}

inline String _typeof(unsigned int) {
  return "unsigned int";
}

inline String _typeof(long int) {
  return "long int";
}

inline String _typeof(unsigned long int) {
  return "unsigned long int";
}

inline String _typeof(long long int) {
  return "long long int";
}

inline String _typeof(unsigned long long int) {
  return "unsigned long long int";
}

inline String _typeof(float) {
  return "float";
}

inline String _typeof(double) {
  return "double";
}

inline String _typeof(String) {
  return "string";
}

#endif
