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
  // 1.1
  {
    circle const c({0.0, 0.0}, 2.0);
    check(near(c.area(), 4.0 * std::numbers::pi), "l'aire du cercle est 4*pi");
    check(near(c.perimeter(), 4.0 * std::numbers::pi), "le périm_tre du cercle est 4*pi");
    check(c.title() == "a circle", "le titre du cercle est 'a circle'");
  }
  // 1.2
  {
    square const s({0.0, 0.0}, 2.0);
    check(near(s.area(), 4.0), "l'aire du carré est 4");
    check(near(s.perimeter(), 8.0), "le périm_tre du cercle est 4*pi");
  }
  // 1.3
  {
    triangle const t({0.0, 0.0}, 2.0);

    check(near(t.area(), std::sqrt(3.0)), "aire du triangle est sqrt(3)");
    check(near(t.perimeter(), 6.0),       "perimètre du triangle est 6");
  }
  // 2.1
  {
    std::vector<std::unique_ptr<shape>> shapes;
    shapes.push_back(std::make_unique<circle>(point{0.0, 0.0}, 2.0));
    shapes.push_back(std::make_unique<square>(point{0.0, 0.0}, 2.0));
    shapes.push_back(std::make_unique<triangle>(point{0.0, 0.0}, 2.0));

    for (auto const& s : shapes) { s->scale_to_area(10.0); }
    for (auto const& s : shapes) { check(near(s->area(), 10.0), "les 3 formes ont une aire de 10 avec scale_to_area"); }
  }
  // 3.3
  {
    std::vector<std::unique_ptr<shape>> v;
    v.push_back(std::make_unique<circle>(point{0.0, 0.0}, 2.0));
  }
  
  {
    // The checks the questions ask for go here. `near` above compares two
    // areas or two lengths to within a tolerance, never with ==.
    check(near(1.0, 1.0), "near agrees with itself");
  }

  // ------------------------------------------------------------------ part 4


  if (failures == 0) { std::cout << "all checks passed\n"; }

  return failures == 0 ? 0 : 1;
}
