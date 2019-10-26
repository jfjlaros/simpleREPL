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
    int _state;
};


int main(void) {
  Calculator calculator;

  while (interface(
      pack(&calculator, &Calculator::add), "add",
      pack(&calculator, &Calculator::subtract), "sub",
      pack(&calculator, &Calculator::show), "show"));

  return 0;
}
