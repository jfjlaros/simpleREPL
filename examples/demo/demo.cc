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
    greet, "greet",
    increase, "inc",
    multiply, "mul"));

  return 0;
}
