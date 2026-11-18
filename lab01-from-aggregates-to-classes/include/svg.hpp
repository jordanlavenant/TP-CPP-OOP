#pragma once

#include "color.hpp"
#include "geometry.hpp"

#include <iosfwd>
#include <vector>

// GIVEN WHOLE. Nothing to write here, and nothing to repair either -- not in
// this lab.
//
// Three free functions writing into a stream. A file is valid only if open has
// been called before any polyline and close after the last one, and nothing in
// these three signatures says so: the balance is left to the caller.
//
// Lab 2 turns these three functions into one class, whose constructor writes
// the header and whose destructor writes the closing tag. What you write here
// is what you will then have to stop writing.

namespace svg
{
  void open(std::ostream& out, int width, int height);

  void polyline(std::ostream& out, std::vector<point> const& points,
                color const& stroke, double thickness);

  void close(std::ostream& out);
}
