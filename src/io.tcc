#ifndef SIMPLE_REPL_IO_TCC_
#define SIMPLE_REPL_IO_TCC_

#include <iostream>

#define PARG Tuple<const char*, const char*>

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
         write(void) {}
    template <class T, class... Args>
      void write(T, Args...);
  private:
    int _argc,
        _number = 0;
    char** _argv;
    bool _endOfLine = false,
         _interactive = true;
};

void _convert(bool*, string);
void _convert(int*, string);
void _convert(float*, string);
void _convert(double*, string);
void _convert(string*, string);


/*
 *
 */
template <class T, class... Args>
void RWIO::write(T data, Args... args) {
  cout << data;
  write(args...);
}

#endif
