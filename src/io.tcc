#ifndef SIMPLE_REPL_IO_TCC_
#define SIMPLE_REPL_IO_TCC_

#include <iostream>

#define PARG_T class... Args
#define PARG Tuple<Tuple<const char*, const char*>, Args...>

using namespace std;

/*
 *
 */
class RWIO {
  public:
    RWIO(void) {}
    bool eol(void),
         interactive(void);
    string read(void);
    void enableCLI(int, char**),
         flush(),
         write(void) {}
    template <class... Args>
      void err(Args...);
    template <class T, class... Args>
      void write(T, Args...);
  private:
    int _argc,
        _number = 0;
    char** _argv;
    bool _endOfLine = false,
         _interactive = true;
};

void _convert(bool*, string),
     _convert(char*, string),
     _convert(signed char*, string),
     _convert(unsigned char*, string),
     _convert(short int*, string),
     _convert(unsigned short int*, string),
     _convert(int*, string),
     _convert(unsigned int*, string),
     _convert(long int*, string),
     _convert(unsigned long int*, string),
     _convert(long long int*, string),
     _convert(unsigned long long int*, string),
     _convert(float*, string),
     _convert(double*, string),
     _convert(long double*, string),
     _convert(string*, string);


/*
 *
 */
template <class... Args>
void RWIO::err(Args... args) {
  write(args...);
  flush();
}

/*
 *
 */
template <class T, class... Args>
void RWIO::write(T data, Args... args) {
  cout << data;
  write(args...);
}


template <class T>
bool convert(T* data, string s) {
  try {
    _convert(data, s);
  }
  catch (std::invalid_argument) {
    return false;
  }
  return true;
}

#endif
