#include "canvas.hpp"
#include "color.hpp"
#include "drawing.hpp"
#include "geometry.hpp"
#include "shape.hpp"

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <numbers>
#include <sstream>
#include <string>
#include <utility>

namespace
{
  int const ARMS = 24;

  // GIVEN. A compact decimal, so the transforms stay readable in the file.
  std::string number(double v)
  {
    std::ostringstream text;
    text << std::setprecision(5) << v;
    return text.str();
  }

  // GIVEN. One arm of the mandala, drawn upwards from the origin: nine shapes
  // along a ray, the three kinds in turn, swelling and then tapering.
  drawing petal()
  {
    drawing one;

    for (int i = 0; i < 9; ++i)
    {
      double const along = 45.0 + 40.0 * i;
      point  const where{0.0, -along};

      std::unique_ptr<shape> made;
      switch (i % 3)
      {
        case 0:  made = std::make_unique<circle>(where, 10.0);   break;
        case 1:  made = std::make_unique<square>(where, 10.0);   break;
        default: made = std::make_unique<triangle>(where, 10.0); break;
      }

      // Widest in the middle of the arm, so the petal has a shape of its own.
      made->scale_to_area(120.0 + 900.0 * std::sin(std::numbers::pi * (i + 1) / 10.0));
      one.add(std::move(made));
    }

    return one;
  }
}

// The whole of the work, in its own scope, so that the count main prints
// afterwards is taken once every drawing has been destroyed.
static void run()
{
  drawing const motif = petal();

  std::cout << "the motif holds " << motif.size() << " shapes, total area "
            << motif.total_area() << '\n';

  // ------------------------------------------------------- copy, then move

  {
    shape::forget_clones();

    drawing copy = motif;
    std::cout << "copying it cloned " << shape::cloned() << " shapes\n";

    copy.scale_all(0.25);

    std::cout << "after shrinking the copy, the copy is " << copy.total_area()
              << " and the motif is still " << motif.total_area() << '\n';

    shape::forget_clones();

    drawing moved = std::move(copy);
    std::cout << "moving it cloned " << shape::cloned() << " shapes, and left "
              << copy.size() << " behind\n";
  }

  // ------------------------------------------------------------ the drawing

  {
    int const width  = 900;
    int const height = 900;

    std::ofstream file(std::string(OUT_DIR) + "/mandala.svg");
    canvas sheet(file, width, height);

    group const placed(sheet, "translate(" + number(sheet.centre().x) + "," +
                              number(sheet.centre().y) + ")");

    // TO WRITE. One copy per arm, each scaled by its own factor, each
    // drawn inside a group turned by its share of the circle. The motif is
    // const: nothing here may change it.
    for (int k = 0; k < ARMS; ++k)
    {
      drawing arm = motif;
      arm.scale_all(0.68 + 0.32 * std::cos(2.0 * std::numbers::pi * 3.0 * k / ARMS));
      group const rotation(sheet, "rotate(" + number(360.0 * k / ARMS) + ")");
      arm.draw_into(sheet, color{"#ff6a3d"}, color{"#3aa2e2"});
    }

    std::cout << "drawn " << sheet.strokes() << " shapes over " << ARMS << " arms\n";
  }
}

int main()
{
  run();

  std::cout << "shapes alive at the end: " << shape::alive() << '\n';
  std::cout << "written: " << OUT_DIR << "/mandala.svg\n";

  return 0;
}
