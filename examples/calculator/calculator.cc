#include "../../src/simpleREPL.h"


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
  Calculator calculator;

  while (interface(
    pack(&calculator, &Calculator::add), "add", "Add something.",
    pack(&calculator, &Calculator::subtract), "sub", "Subtract something.",
    pack(&calculator, &Calculator::show), "show", "Show result."));

  return 0;
}
