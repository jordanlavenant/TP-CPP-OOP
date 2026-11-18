#include "aggregate.hpp"
#include "color.hpp"
#include "geometry.hpp"

#include <cmath>
#include <iostream>
#include <string>

static int failures = 0;

static void check(bool condition, char const* what)
{
  if (!condition) { std::cerr << "FAILED: " << what << '\n'; ++failures; }
}

int main()
{
  // ------------------------------------------------------------------ given

  {
    point const a{3.0, 4.0};
    point const b = translated(a, -3.0, -4.0);

    check(b.x == 0.0 && b.y == 0.0, "translating a point");
    check(distance(a, b) == 5.0,    "the distance between two points");
    check(scaled(a, 2.0).x == 6.0,  "scaling a point");
  }


  {
    // The aggregate is right on a value that is in range.
    check(before::to_hex({255, 128, 0}) == "#ff8000", "the aggregate on a color");

    // Now repaired: both produce a valid 7-character hex color.
    check(before::to_hex({300, 40, 0}).size() == 7,
          "the aggregate clamps a component out of range");

    check(before::to_hex(before::mix({0, 0, 0}, {255, 255, 255}, 2.0)).size() == 7,
          "the aggregate clamps an out-of-range interpolation");
  }
  
  // --------------------------------------------------------------- to write
  // Partie 1
  {
    point const a{3.0, 4.0};
    point const b = translated(a, -3.0, -4.0);
    check(midpoint(a, b).x == 1.5 && midpoint(a, b).y == 2.0, "midpoint of a point");
  }
  {
    point const a{3.0, 4.0};
    point b = a.translated(-3.0, -4.0);
    check(b.x == 0.0 && b.y == 0.0, "translated from a member function");
  }
  // Partie 2
  {
    // 2.1
    check(color{}.to_hex() == "#000000", "couleur par défaut");
    check(color{255, 128, 0}.to_hex() == "#ff8000", "couleur dans les bornes");
    check(color{300, 128, -20}.to_hex() == "#ff8000", "couleur dont une composante dépasse 255 et une autre négative");
    check(color{"#ff8000"}.to_hex() == "#ff8000", "couleur lu à partir d'une chaîne ");
    // 2.6
    check(color{0, 0, 0}.to_hex() == "#000000", "0");
    check(color{15, 15, 15}.to_hex() == "#0f0f0f", "15");
    check(color{16, 16, 16}.to_hex() == "#101010", "16");
    check(color{255, 255, 255}.to_hex() == "#ffffff", "255");
  }
  // Partie 3
  {
    // 3.1
    check(color{300, 40, 0}.to_hex().size() == 7, "vérification que (300, 40, 0) est bien ramené dans les bornes");
    // 3.4
    check(before::color{300, 40, 0}.red == 300, "la composante rouge de before::color vaut 300");
  }
  // Partie 4
  {
    check(mix(color{0, 0, 0}, color{255, 255, 255}, 0.5).red() == 128, "la composante rouge de la couleur mixée vaut 128");
  }

  if (failures == 0) { std::cout << "all checks passed\n"; }

  return failures == 0 ? 0 : 1;
}
