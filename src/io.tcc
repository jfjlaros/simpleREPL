#ifndef SIMPLE_REPL_IO_TCC_
#define SIMPLE_REPL_IO_TCC_

#include <iostream>

using namespace std;

/*
 *
 */
class RWIO {
  public:
    RWIO(void) {}
    RWIO(int, char**);
    bool eol(void);
    string read(void);
    void write(void) {}
    template <class T, class... Args>
      void write(T, Args...);
  private:
    int _argc,
        _number = 0;
    char** _argv;
    bool _endOfLine = false,
         _ioREPL = true;
};


/*
 *
 */
template <class T, class... Args>
void RWIO::write(T data, Args... args) {
  cout << data;
  write(args...);
}

#endif
