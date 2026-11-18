#include "canvas.hpp"
#include "color.hpp"
#include "geometry.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace
{
  int const DEPTH  = 11;
  double const LENGTH = 150.0;

  // GIVEN. A compact decimal, so that the transforms stay readable in the file.
  std::string number(double v)
  {
    std::ostringstream text;
    text << std::setprecision(4) << v;
    return text.str();
  }

  // GIVEN. Move to the end of the branch, turn, and shrink. Written in the
  // order SVG applies them: rightmost first.
  std::string transform(double dy, double angle, double factor)
  {
    return "translate(0," + number(dy) + ") rotate(" + number(angle) +
           ") scale(" + number(factor) + ")";
  }

  // GIVEN. Amber at the trunk, cyan at the tips.
  color shade(int depth)
  {
    double const t = (DEPTH - depth) / static_cast<double>(DEPTH - 1);
    return mix(color{181, 118, 58}, color{127, 227, 255}, t);
  }

  // GIVEN. The tree, drawn in the coordinate system of its own trunk: every
  // branch starts at the origin and grows upwards, whatever its real place and
  // angle in the picture. What puts it there is the enclosing group, and
  // nothing in this function knows about it.
  void branch(canvas& sheet, int depth, double thickness)
  {
    if (depth == 0) { return; }

    // Below about half a pixel a stroke fades out of the picture, so the
    // outermost twigs are drawn at a floor rather than at their own width.
    sheet.line({0.0, 0.0}, {0.0, -LENGTH}, shade(depth), thickness < 0.7 ? 0.7 : thickness);

    {
      group const left(sheet, transform(-LENGTH, -27.0, 0.78));
      branch(sheet, depth - 1, thickness * 0.76);
    }

    {
      group const right(sheet, transform(-LENGTH, 31.0, 0.74));
      branch(sheet, depth - 1, thickness * 0.76);
    }
  }

  // GIVEN. The same tree, with one branch that gives up in the middle. Used by
  // part 4: the file it leaves behind is valid, and the destructors are the
  // only reason why.
  void fragile(canvas& sheet, int depth, double thickness)
  {
    if (depth == 0) { return; }
    if (sheet.strokes() >= 400) { throw std::runtime_error("this branch gives up"); }

    // Below about half a pixel a stroke fades out of the picture, so the
    // outermost twigs are drawn at a floor rather than at their own width.
    sheet.line({0.0, 0.0}, {0.0, -LENGTH}, shade(depth), thickness < 0.7 ? 0.7 : thickness);

    {
      group const left(sheet, transform(-LENGTH, -27.0, 0.78));
      fragile(sheet, depth - 1, thickness * 0.76);
    }

    {
      group const right(sheet, transform(-LENGTH, 31.0, 0.74));
      fragile(sheet, depth - 1, thickness * 0.76);
    }
  }

  void draw_tree(std::ostream& out)
  {
    canvas sheet(out);

    std::cout << "alive during the drawing: " << canvas::alive() << '\n';

    // TO WRITE. Place the tree inside one group, in its own scope, then
    // call branch. Where the closing brace goes is what decides where the
    // closing tag goes.
    {
      group const feuille(sheet, "translate(450,860)");
      branch(sheet, DEPTH, 11.0);
    }

    // Every group opened has been closed, and no line below wrote a closing
    // tag: the closing brace above did.
    std::cout << "strokes: " << sheet.strokes()
              << ", groups still open: " << sheet.depth() << '\n';
  }
}

int main()
{
  std::cout << "alive before anything: " << canvas::alive() << '\n';

  {
    std::ofstream file(std::string(OUT_DIR) + "/tree.svg");
    draw_tree(file);
  }

  std::cout << "alive after: " << canvas::alive() << '\n';

  // The tree that gives up. Everything the exception crosses is destroyed on
  // its way out, so every tag opened is closed and the file still opens.
  {
    std::ofstream file(std::string(OUT_DIR) + "/broken.svg");
    canvas sheet(file);
    group const trunk(sheet, "translate(450,860)");

    try                                  { fragile(sheet, DEPTH, 11.0); }
    catch (std::runtime_error const& e)  { std::cout << "caught: " << e.what() << '\n'; }
  }

  std::cout << "written: " << OUT_DIR << "/tree.svg and broken.svg\n";

  return 0;
}
