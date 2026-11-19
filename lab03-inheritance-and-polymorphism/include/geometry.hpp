#pragma once

#include <cmath>

// GIVEN WHOLE. Nothing to write here.
//
// A point of the drawing plane. Two coordinates, and no invariant: every pair
// of doubles is a point, so there is nothing for a constructor to guarantee.
//
// That is what separates it from color, which has one.

struct point
{
  double x = 0.0;
  double y = 0.0;
};

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
