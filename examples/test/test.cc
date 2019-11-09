#include "interface.tcc"


/*
 * Debug function.
 */
template <class... Args>
void show(Args...) {
  IO.write(__PRETTY_FUNCTION__, "\n");
}


/*
 * Test.
 */
long f(int i, string s, bool b, float g, int j) {
  IO.write("f: ", i, " ", s, " ", b, " ", g, " ", j, "\n");

  return 0;
}


int main(int argc, char** argv) {
  //IO = RWIO(argc, argv);

  help(f, "f", "funk the func", params(
    param("-a", 2, "set the int"),
    param("name", "name the name"),
    param("-c", true, "flip the flop"),
    param("-d", 3.14F, "pimp the pi"),
    param("value", "set the value")));

  IO.write("\n");

  interface(f, "f", "funk the func", params(
    param("-a", 2, "set the a"),
    param("name", "name the name"),
    param("-c", true, "flip the flop"),
    param("-d", 3.14F, "pimp the pi"),
    param("value", "set the value")));

  return 0;
}
