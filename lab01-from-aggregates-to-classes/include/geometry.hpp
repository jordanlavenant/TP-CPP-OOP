#pragma once

#include <cmath>
#include <type_traits>

// GIVEN, except midpoint and the member translated, which part 1 asks you to
// write.
//
// A point of the drawing plane. Two coordinates, and no invariant: every pair
// of doubles is a point, so there is nothing for a constructor to guarantee.

struct point
{
  double x = 0.0;
  double y = 0.0;

  // TO WRITE. translated, a second time, as a member function.
  public:
    point translated(double dx, double dy) const
    {
      return {x + dx, y + dy};
    }
};

// Only a declared constructor, a private or protected field, a virtual
// function, or a non-public or virtual base would end the aggregate; a member
// function does not.
static_assert(std::is_aggregate_v<point>);

// These are free functions, and not members, because they need nothing that an
// outside caller could not reach: the two fields are public. A member would buy
// no access and would enlarge the type for nothing.

inline point translated(point p, double dx, double dy) { return {p.x + dx, p.y + dy}; }

inline point scaled(point p, double k) { return {p.x * k, p.y * k}; }

inline double distance(point a, point b)
{
  double const dx = a.x - b.x;
  double const dy = a.y - b.y;
  return std::sqrt(dx * dx + dy * dy);
}

// TO WRITE. midpoint, the middle of the segment between two points.
inline point midpoint(point a, point b)
{
  return {(a.x + b.x) / 2.0, (a.y + b.y) / 2.0};
}
