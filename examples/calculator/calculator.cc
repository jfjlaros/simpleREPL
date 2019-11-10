#include <simpleREPL.h>


class Calculator {
  public:
    Calculator(void) {}
    void add(int a) {
      _state += a;
    }
    void subtract(int a) {
      _state -= a;
    }
    int show(void) {
      return _state;
    }
  private:
    int _state = 0;
};


int main(void) {
  Calculator calc;

  while (interface(
    func(pack(&calc, &Calculator::add), "add", "Add something.",
      param("a", "a")),
    func(pack(&calc, &Calculator::subtract), "sub", "Subtract something.",
      param("a", "a")),
    func(pack(&calc, &Calculator::show), "show", "Show result.")));

  return 0;
}
