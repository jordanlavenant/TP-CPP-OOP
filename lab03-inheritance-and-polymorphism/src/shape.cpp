#include "shape.hpp"

#include <cmath>
#include <iomanip>
#include <numbers>
#include <sstream>

int shape::alive_ = 0;

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

int shape::alive() { return alive_; }

std::string shape::title() const { return "a shape"; }

void shape::scale_to_area(double target)
{
  // TO WRITE. One line of arithmetic and two virtual calls. Written once
  // here, it must work unchanged for the three kinds below.
  double current = area();
  if (current == 0.0) { return; }
  double factor = std::sqrt(target / current);
  scale(factor);
}

// ------------------------------------------------------------------- circle

circle::circle(point centre, double radius) : shape(centre), radius_(radius) {}

double circle::radius() const { return radius_; }

std::string circle::title() const { return "a circle"; }

double circle::area() const
{
  // TO WRITE.
  return std::numbers::pi * radius_ * radius_;
}

double circle::perimeter() const
{
  // TO WRITE.
  return 2 * std::numbers::pi * radius_;
}

void circle::scale(double factor)
{
  // TO WRITE.
  radius_ *= factor;
}

std::string circle::outline(color const& fill) const
{
  // TO WRITE. `number` above writes a coordinate the way the file expects it.
  return "<circle cx=\"" + number(centre_.x) + "\" cy=\"" + number(centre_.y) + "\" r=\"" + number(radius_) + "\" fill=\"" + fill.to_hex() + "\" />";
}

// ------------------------------------------------------------------- square

square::square(point centre, double side) : shape(centre), side_(side) {}

double square::side() const { return side_; }

std::string square::title() const { return "a square"; }

double square::area() const
{
  // TO WRITE.
  return side_ * side_;
}

double square::perimeter() const
{
  // TO WRITE.
  return 4 * side_;
}

void square::scale(double factor)
{
  // TO WRITE.
  side_ *= factor;
}

std::string square::outline(color const& fill) const
{
  // TO WRITE.
  return "<rect x=\"" + number(centre_.x - side_ / 2) + "\" y=\"" + number(centre_.y - side_ / 2) + "\" width=\"" + number(side_) + "\" height=\"" + number(side_) + "\" fill=\"" + fill.to_hex() + "\" />";
}

// ----------------------------------------------------------------- triangle

triangle::triangle(point centre, double side) : shape(centre), side_(side) {}

double triangle::side() const { return side_; }

std::string triangle::title() const { return "a triangle"; }

double triangle::area() const
{
  // TO WRITE.
  return std::sqrt(3) / 4 * side_ * side_;
}

double triangle::perimeter() const
{
  // TO WRITE.
  return 3 * side_;
}

void triangle::scale(double factor)
{
  // TO WRITE.
  side_ *= factor;
}

std::string triangle::outline(color const& fill) const
{
  // TO WRITE.
  return "<polygon points=\"" + number(centre_.x) + "," + number(centre_.y - side_ * std::sqrt(3) / 3) + " " + number(centre_.x - side_ / 2) + "," + number(centre_.y + side_ * std::sqrt(3) / 6) + " " + number(centre_.x + side_ / 2) + "," + number(centre_.y + side_ * std::sqrt(3) / 6) + "\" fill=\"" + fill.to_hex() + "\" />";
}
