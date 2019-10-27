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
    greet, "greet", "Say hi to someone.",
    increase, "inc", "Increase an integer value.",
    multiply, "mul", "Multiply a float with an integer."));

  return 0;
}
