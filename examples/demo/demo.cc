#include "../../src/simpleREPL.h"


string greet(string name) {
  return "Hi " + name + ".";
}

int increase(int a) {
  return a + 1;
}

float multiply(float a, int b) {
  return a * b;
}


int main(void) {
  while (interface(
    func(greet, "greet", "Say hi to someone.",
      param("name", "a name")),
    func(increase, "inc", "Increase an integer value.",
      param("value", "a value")),
    func(multiply, "mul", "Multiply a float with an integer.",
      param("-a", 1.1F, "float value"),
      param("b", "multiplier"))));

  return 0;
}
