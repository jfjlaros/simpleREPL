#include "../../src/simpleREPL.h"


string greet(string name) {
  return "Hi " + name + ".";
}

int inc(int a) {
  return a + 1;
}


int main(void) {
  while (interface(
      greet, "greet",
      inc, "inc"));

  return 0;
}
