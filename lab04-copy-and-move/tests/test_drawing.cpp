#include "drawing.hpp"
#include "shape.hpp"

#include <cmath>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

static int failures = 0;

static void check(bool condition, char const* what)
{
  if (!condition) { std::cerr << "FAILED: " << what << '\n'; ++failures; }
}

static bool near(double a, double b) { return std::fabs(a - b) < 1e-9; }

// Three shapes, one of each kind, at a known total area.
static drawing sample()
{
  drawing one;
  one.add(std::make_unique<circle>(point{0.0, 0.0}, 1.0));
  one.add(std::make_unique<square>(point{0.0, 0.0}, 2.0));
  one.add(std::make_unique<triangle>(point{0.0, 0.0}, 3.0));
  return one;
}

int main()
{
  // --------------------------------------------------------------- to write

  {
    // The checks the questions ask for go here, in blocks of their own. `sample`
    // above builds a drawing of three shapes, and `near` compares two areas.
    drawing const first = sample();
    check(first.size() == 3, "the sample holds three shapes");
    check(near(first.total_area(), sample().total_area()), "and two samples have the same area");
  }

  // 1.2
  {
    drawing a = sample();
    drawing b = std::move(a);
  }

  // 2.4
  {
    drawing dessin = sample(); // 3 dessins de base
    shape::forget_clones();
    drawing copie = dessin;

    check(shape::cloned() == 3, "vérifie qu'il y a 3 clones");
    check(shape::alive() == 6, "vérifie qu'il y a 6 formes");
    check(copie.size() == 3, "véirfie que la copie a 3 formes");
    check(near(copie.total_area(), dessin.total_area()), "même aire totale entre l'original et la copie");

    double const aire_dessin = dessin.total_area();
    copie.scale_all(2.0);

    check(near(copie.total_area(), 4.0 * aire_dessin), "vérifie que l'aire à quadruplé");
    check(near(dessin.total_area(), aire_dessin), "l'aire du dessin original n'a pas changé");
  }
  check(shape::alive() == 0, "vérifie qu'il n'y a plus de formes vivantes");

  // 3.1 & 3.2
  {
    // 3.1
    drawing dessin = sample();
    shape::forget_clones();
    double const aire_dessin = dessin.total_area();
    drawing copie = std::move(dessin);
    
    check(shape::cloned() == 0, "vérifie qu'il n'y a pas eu de clones");
    check(shape::alive() == 3, "vérifie qu'il y a 3 formes vivantes");
    check(copie.size() == 3, "vérifie que la copie a 3 formes");
    check(near(copie.total_area(), aire_dessin), "vérifie que l'aire totale est la même");
    
    // 3.2
    drawing dessin2 = sample();
    double const aire_dessin2 = dessin2.total_area();
    drawing copie2 = std::move(dessin2);

    check(copie2.size() == 3, "le nouveau dessin contient 3 formes");
    check(near(copie2.total_area(), aire_dessin2), "vérifie que l'aire totale est la même");
  }

  // 3.3
  {
    shape::forget_clones();
    std::vector<drawing> dessins;
    for (int i = 0; i < 8; ++i)
    {
      drawing d;
      d.add(std::make_unique<circle>(point{0.0, 0.0}, 1.0));
      dessins.push_back(std::move(d));
    }

    check(dessins.size() == 8, "vérifie qu'il y a 8 dessins");
    check(shape::cloned() == 0, "vérifie qu'il n'y a pas eu de clones");

    std::cout << "shape::cloned() = " << shape::cloned() << '\n';
  }

  // 4.1
  {
    drawing a = sample();
    drawing b = sample();

    a.scale_all(2.0);
    shape::forget_clones();
    a = b;

    check(shape::cloned() == 3, "vérifie qu'il y a 3 clones");
    check(shape::alive() == 6, "vérifie qu'il y a 6 formes vivantes");
    check(a.total_area() == b.total_area(), "vérifie que les deux dessins ont la même aire");
  }

  // 4.2
  {
    drawing a = sample();
    double const aire_avant = a.total_area();
    std::size_t const taille_avant = a.size();

    drawing& same = a;
    a = same;

    check(a.size() == taille_avant, "le nombre de forme est inchangé");
    check(a.total_area() == aire_avant, "l'aire totale est inchangée");
  }

  if (failures == 0) { std::cout << "all checks passed\n"; }

  return failures == 0 ? 0 : 1;
}
