#include "shape.hpp"

#include <cmath>
#include <memory>
#include <iomanip>
#include <numbers>
#include <sstream>

int shape::alive_  = 0;
int shape::cloned_ = 0;

namespace
{
  // GIVEN. A compact decimal, so the file stays readable.
  std::string number(double v)
  {
    std::ostringstream text;
    text << std::setprecision(5) << v;
    return text.str();
  }
}

shape::shape(point centre) : centre_(centre) { ++alive_; }

shape::~shape() { --alive_; }

point shape::centre() const { return centre_; }

void shape::translate(point delta) { centre_ = translated(centre_, delta.x, delta.y); }

int  shape::alive()  { return alive_;  }
int  shape::cloned() { return cloned_; }
void shape::forget_clones() { cloned_ = 0; }

std::string shape::title() const { return "a shape"; }

void shape::scale_to_area(double target)
{
  // Areas go as the square of a length, so the factor is the square root of
  // the ratio. Nothing here knows which kind of shape it is scaling, and
  // nothing has to: area and scale are the two questions it asks.
  double const current = area();
  if (current <= 0.0) { return; }

  scale(std::sqrt(target / current));
}

// ------------------------------------------------------------------- circle

circle::circle(point centre, double radius) : shape(centre), radius_(radius) {}

double circle::radius() const { return radius_; }

std::string circle::title() const { return "a circle"; }

std::unique_ptr<shape> circle::clone() const
{
  // TO WRITE. Two lines: increment cloned_, then return a new circle.
  cloned_++;
  return std::make_unique<circle>(centre_, radius_);
}

double circle::area() const
{
  return std::numbers::pi * radius_ * radius_;
}

double circle::perimeter() const
{
  return 2.0 * std::numbers::pi * radius_;
}

void circle::scale(double factor)
{
  radius_ *= factor;
}

std::string circle::outline(color const& fill) const
{
  return "<circle cx=\"" + number(centre_.x) + "\" cy=\"" + number(centre_.y) +
         "\" r=\"" + number(radius_) + "\" fill=\"" + fill.to_hex() + "\"/>";
}

// ------------------------------------------------------------------- square

square::square(point centre, double side) : shape(centre), side_(side) {}

double square::side() const { return side_; }

std::string square::title() const { return "a square"; }

std::unique_ptr<shape> square::clone() const
{
  // TO WRITE. Two lines: increment cloned_, then return a new square.
  cloned_++;
  return std::make_unique<square>(centre_, side_);

}

double square::area() const
{
  return side_ * side_;
}

double square::perimeter() const
{
  return 4.0 * side_;
}

void square::scale(double factor)
{
  side_ *= factor;
}

std::string square::outline(color const& fill) const
{
  // SVG places a rectangle by its top left corner, and the shape holds its
  // centre: half a side has to come off both coordinates.
  double const half = side_ / 2.0;

  return "<rect x=\"" + number(centre_.x - half) + "\" y=\"" + number(centre_.y - half) +
         "\" width=\"" + number(side_) + "\" height=\"" + number(side_) +
         "\" fill=\"" + fill.to_hex() + "\"/>";
}

// ----------------------------------------------------------------- triangle

triangle::triangle(point centre, double side) : shape(centre), side_(side) {}

double triangle::side() const { return side_; }

std::string triangle::title() const { return "a triangle"; }

std::unique_ptr<shape> triangle::clone() const
{
  // TO WRITE. Two lines: increment cloned_, then return a new triangle.
  cloned_++;
  return std::make_unique<triangle>(centre_, side_);

}

double triangle::area() const
{
  return std::sqrt(3.0) / 4.0 * side_ * side_;
}

double triangle::perimeter() const
{
  return 3.0 * side_;
}

void triangle::scale(double factor)
{
  side_ *= factor;
}

std::string triangle::outline(color const& fill) const
{
  // The centroid sits one third of the height above the base, so the apex is
  // two thirds of the height above it.
  double const height = std::sqrt(3.0) / 2.0 * side_;
  double const half   = side_ / 2.0;

  return "<polygon points=\"" +
         number(centre_.x) + "," + number(centre_.y - 2.0 * height / 3.0) + " " +
         number(centre_.x + half) + "," + number(centre_.y + height / 3.0) + " " +
         number(centre_.x - half) + "," + number(centre_.y + height / 3.0) +
         "\" fill=\"" + fill.to_hex() + "\"/>";
}
