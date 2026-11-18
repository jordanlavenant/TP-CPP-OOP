#include "aggregate.hpp"
#include "color.hpp"
#include "geometry.hpp"
#include "svg.hpp"

#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <numbers>
#include <string>
#include <vector>

namespace
{
  // GIVEN. A hypotrochoid: the curve traced by a pen held at distance `pen`
  // from the centre of a circle of radius `small` rolling inside a circle of
  // radius `large`. Nothing about objects here, only trigonometry.
  std::vector<point> spirograph(double large, double small, double pen,
                                point centre, int steps, double turns)
  {
    std::vector<point> curve;
    curve.reserve(static_cast<std::size_t>(steps) + 1);

    double const rolled = large - small;

    for (int i = 0; i <= steps; ++i)
    {
      double const angle = turns * 2.0 * std::numbers::pi * i / steps;
      double const spin  = rolled / small * angle;

      curve.push_back(translated({rolled * std::cos(angle) + pen * std::cos(spin),
                                  rolled * std::sin(angle) - pen * std::sin(spin)},
                                 centre.x, centre.y));
    }

    return curve;
  }
}

int main()
{
  // GIVEN. The same color asked for twice, once of each kind. One of the two
  // answers is not a color, and part 3 is about which and why.
  std::cout << "aggregate: " << before::to_hex({300, 40, 0}) << '\n'
            << "class    : " << color{300, 40, 0}.to_hex()  << '\n';

  int const width  = 900;
  int const height = 900;

  point const centre{width / 2.0, height / 2.0};

  // 280 and 90 have 10 as their greatest common divisor, so the curve closes
  // after 90/10 turns and shows 280/10 petals.
  int const petals = 28;

  std::vector<point> const curve = spirograph(280.0, 90.0, 190.0, centre, 8000, 9.0);

  std::cout << "curve   : " << curve.size() << " points, " << petals << " petals\n";

  std::string const path = std::string(OUT_DIR) + "/spiro.svg";
  std::ofstream file(path);

  svg::open(file, width, height);

  // The two ends of the gradient. Part 4 interpolates between them.
  color const dawn{255, 92, 51};
  color const dusk{51, 156, 255};

  std::cout << "dawn " << mix(dawn, dusk, 2.0).to_hex() << '\n'
            << "dusk " << mix(dawn, dusk, -1.0).to_hex() << '\n';

  std::cout << "r " << before::mix({255, 92, 51}, {51, 156, 255}, 2.0).red << '\n'
            << "g " << before::mix({255, 92, 51}, {51, 156, 255}, 2.0).green << '\n'
            << "b " << before::mix({255, 92, 51}, {51, 156, 255}, 2.0).blue << '\n';

  int const pieces = 20 * petals;
  for (int i = 0; i < pieces; ++i)
  {
    std::size_t const start = static_cast<std::size_t>(i) * (curve.size() - 1) / pieces;
    std::size_t const stop  = static_cast<std::size_t>(i + 1) * (curve.size() - 1) / pieces;

    std::vector<point> const piece(curve.begin() + start, curve.begin() + stop + 1);

    double const angle = 2.0 * std::numbers::pi * i / 20.0;
    double const t = (1.0 - std::cos(angle)) / 2.0;

    svg::polyline(file, piece, mix(dawn, dusk, t), 2.0);
  }

  svg::close(file);

  std::cout << "written: " << path << '\n';

  return 0;
}
