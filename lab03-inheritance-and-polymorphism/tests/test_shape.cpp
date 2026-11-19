#include "color.hpp"
#include "shape.hpp"

#include <cmath>
#include <iostream>
#include <memory>
#include <numbers>
#include <string>
#include <vector>

static int failures = 0;

static void check(bool condition, char const* what)
{
  if (!condition) { std::cerr << "FAILED: " << what << '\n'; ++failures; }
}

// Areas are doubles: they are compared to within a tolerance, never with ==.
static bool near(double a, double b) { return std::fabs(a - b) < 1e-9; }

int main()
{
  // ------------------------------------------------------------------ given

  {
    // Nothing has been built, so nothing is alive. The baseline the rest of
    // the checks are read against.
    check(shape::alive() == 0, "no shape exists before any is built");

    // shape is abstract: this line does not compile, and that is the answer to
    // the question on `= 0`.
    //
    //   shape s({0.0, 0.0});
  }

  // --------------------------------------------------------------- to write

  {
    // The checks the questions ask for go here. `near` above compares two
    // areas or two lengths to within a tolerance, never with ==.
    check(near(1.0, 1.0), "near agrees with itself");
  }

  // ------------------------------------------------------------------ part 4


  if (failures == 0) { std::cout << "all checks passed\n"; }

  return failures == 0 ? 0 : 1;
}
