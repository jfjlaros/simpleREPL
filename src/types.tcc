#ifndef SIMPLE_REPL_TYPES_TCC_
#define SIMPLE_REPL_TYPES_TCC_

/**
 * Type analysis and naming.
 */


/*
 * Type naming functions.
 */
inline string _typeof(bool) {
  return "bool";
}

inline string _typeof(char) {
  return "char";
}

inline string _typeof(signed char) {
  return "signed char";
}

inline string _typeof(unsigned char) {
  return "unsigned char";
}

inline string _typeof(short int) {
  return "short int";
}

inline string _typeof(unsigned short int) {
  return "unsigned short int";
}

inline string _typeof(int) {
  return "int";
}

inline string _typeof(unsigned int) {
  return "unsigned int";
}

inline string _typeof(long int) {
  return "long int";
}

inline string _typeof(unsigned long int) {
  return "unsigned long int";
}

inline string _typeof(long long int) {
  return "long long int";
}

inline string _typeof(unsigned long long int) {
  return "unsigned long long int";
}

inline string _typeof(float) {
  return "float";
}

inline string _typeof(double) {
  return "double";
}

inline string _typeof(string) {
  return "string";
}

#endif
