#include <math.h>

#include "../../src/simpleREPL.h"


int main(void) {
  while (interface(
    (double (*)(double))cos, "cos", "Compute cosine.",
    (double (*)(double))sin, "sin", "Compute sine.",
    (double (*)(double))tan, "tan", "Compute tangent.",
    (double (*)(double))fabs, "fabs", "Compute absolute value.",
    (double (*)(double, double))fmod, "fmod", "Compute remainder of division.",
    (double (*)(double))sqrt, "sqrt", "Compute square root.",
    (double (*)(double))cbrt, "cbrt", "Compute cubic root.",
    (double (*)(double, double))hypot, "hypot", "Compute hypotenuse.",
    (double (*)(double))floor, "floor", "Round down value.",
    (double (*)(double))ceil, "ceil", "Round up value.",
    (double (*)(double, int))ldexp, "ldexp",
      "Generate value from significand and exponent.",
    (double (*)(double))exp, "exp", "Compute exponential function.",
    (double (*)(double))cosh, "cosh", "Compute hyperbolic cosine,",
    (double (*)(double))sinh, "sinh", "Compute hyperbolic sine,",
    (double (*)(double))tanh, "tanh", "Compute hyperbolic tangent,",
    (double (*)(double))acos, "acos", "Compute arc cosine.",
    (double (*)(double))asin, "asin", "Compute arc sine.",
    (double (*)(double))atan, "atan", "Compute arc tangent.",
    (double (*)(double, double))atan2, "atan2",
      "Compute arc tangent with two parameters.",
    (double (*)(double))log, "log", "Compute natural logarithm.",
    (double (*)(double))log10, "log10", "Compute common logarithm.",
    (double (*)(double, double))pow, "pow", "Raise to power.",
    (double (*)(double, double))fdim, "fdim", "Positive difference.",
    (double (*)(double, double, double))fma, "fma", "Multiply-add.",
    (double (*)(double, double))fmax, "fmax", "Maximum value.",
    (double (*)(double, double))fmin, "fmin", "Minimum value.",
    (double (*)(double))trunc, "trunc", "Truncate value.",
    (double (*)(double))round, "round", "Round to nearest.",
    (long (*)(double))lround, "lround",
      "Round to nearest and cast to long integer.",
    (long (*)(double))lrint, "lrint", "Round and cast to long integer."));

  return 0;
}
