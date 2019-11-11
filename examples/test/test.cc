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

void g(int i, bool b) {
  IO.write("g: ", i, " ", b, "\n");
}

class C {
  public:
    int h(void) {
      return 1;
    }
    void i(int) {
    }
};


int main(int argc, char** argv) {
  C c;

  IO.enableCLI(argc, argv);

  interface(
    f, (const char*)argv[0], "funk the func", 
      param("-a", 2, "set the int"),
      param("name", "name the name"),
      param("-c", true, "flip the flop"),
      param("-d", 3.14F, "pimp the pi"),
      param("value", "set the value"));
/*
  interface(
    func(pack(&c, &C::i), "i", "class void test",
      param("a", "a")),
    func(f, "f", "funk the func", 
      param("-a", 2, "set the int"),
      param("name", "name the name"),
      param("-c", true, "flip the flop"),
      param("-d", 3.14F, "pimp the pi"),
      param("value", "set the value")),
    func(g, "g", "goop the gobb",
      param("value", "some value"),
      param("-b", true, "bleep the blop")),
    func(pack(&c, &C::h), "h", "class test")
  );
  */

  return 0;
}
