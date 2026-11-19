#include "canvas.hpp"
#include "color.hpp"
#include "geometry.hpp"
#include "shape.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <numbers>
#include <string>
#include <vector>

namespace
{
  int const COUNT = 520;

  // GIVEN. The angle a sunflower puts between two consecutive seeds. It is the
  // one angle for which no two seeds ever line up.
  double const GOLDEN = std::numbers::pi * (3.0 - std::sqrt(5.0));

  // GIVEN. One shape out of the three, chosen by rank. Nothing else in the
  // program ever asks which one came back.
  std::unique_ptr<shape> make_shape(int rank, point where)
  {
    switch (rank % 3)
    {
      case 0:  return std::make_unique<circle>(where, 10.0);
      case 1:  return std::make_unique<square>(where, 10.0);
      default: return std::make_unique<triangle>(where, 10.0);
    }
  }

  color shade(double t) { return mix(color{233, 84, 32}, color{58, 170, 226}, t); }
}

int main()
{
  int const width  = 900;
  int const height = 900;

  point const centre{width / 2.0, height / 2.0};

  std::vector<std::unique_ptr<shape>> garden;
  garden.reserve(COUNT);

  for (int i = 0; i < COUNT; ++i)
  {
    double const distance = 17.0 * std::sqrt(static_cast<double>(i));
    double const angle    = i * GOLDEN;

    // TO WRITE. Add the shape of rank i, placed at the point of the spiral,
    // then bring it to the area 30 + 1.6 * distance with the same call
    // whatever its kind.
    (void)distance;
    (void)angle;
  }

  std::cout << "shapes alive: " << shape::alive() << '\n';

  // The three kinds, built at the same size and brought to the same area by
  // the same call. Same area, three different sizes: that is the point.
  {
    std::vector<std::unique_ptr<shape>> trio;
    for (int i = 0; i < 3; ++i) { trio.push_back(make_shape(i, centre)); }

    // TO WRITE. Bring each of the three to the area 400, then print its
    // title, its area and its perimeter.
  }

  {
    std::ofstream file(std::string(OUT_DIR) + "/garden.svg");
    canvas sheet(file, width, height);

    for (std::size_t i = 0; i < garden.size(); ++i)
    {
      double const t = static_cast<double>(i) / (COUNT - 1);
      sheet.draw(*garden[i], shade(t));
    }

    std::cout << "drawn: " << sheet.strokes() << '\n';
  }

  garden.clear();

  std::cout << "shapes alive after clearing: " << shape::alive() << '\n';
  std::cout << "written: " << OUT_DIR << "/garden.svg\n";

  return 0;
}
