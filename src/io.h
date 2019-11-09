#ifndef SIMPLE_REPL_IO_H_
#define SIMPLE_REPL_IO_H_

#include <iostream>

using namespace std;

/*
 *
 */
class _IO {
  public:
    void write(void) {}
    template <class T, class... Args>
      void write(T, Args...);
};

/*
 *
 */
class REPLIO: public _IO{
  public:
    REPLIO(void) {}
    string read(void),
           read(size_t);
    bool eol(void);
  private:
    bool _endOfLine = false;
};

/*
 *
 */
class CLIIO: public _IO {
  public:
    CLIIO(void) {}
    CLIIO(int argc, char** argv);
    string read(void);
    bool eol(void);
  private:
    int _argc,
        _number = 0;
    char** _argv;
};


/*
 *
 */
template <class T, class... Args>
void _IO::write(T data, Args... args) {
  cout << data;
  write(args...);
}

#endif
