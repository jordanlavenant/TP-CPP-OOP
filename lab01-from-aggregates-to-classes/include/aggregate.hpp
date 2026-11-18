#pragma once

#include <string>

// WHAT WE START FROM. Working as it stands; part 3 repairs to_hex here.
//
// This is a color as an aggregate: three public fields and free functions
// around them. Read it once before starting: parts 3 and 4 compare it with
// the class.
//
// It sits in the same project, under the eye, so that the comparison the lab
// keeps asking for costs nothing more than scrolling.

namespace before
{
  struct color
  {
    int red   = 0;
    int green = 0;
    int blue  = 0;
  };

  inline std::string to_hex(color const& c)
  {
    char const digits[] = "0123456789abcdef";
    std::string text = "#";

    // Each component is written in base sixteen, padded to two digits. A value
    // between 0 and 255 comes out on exactly two characters. A larger one comes
    // out on three, a negative one carries a minus sign, and in both cases the
    // result is no longer an SVG color.
    // Nothing here checks that the value is in range, and no other place does
    // either.
    for (int v : {c.red, c.green, c.blue})
    {
      if (v < 0) { v = 0; }
      else if (v > 255) { v = 255; }

      std::string component;
      bool const negative = v < 0;
      if (negative) { v = -v; }

      do { component.insert(component.begin(), digits[v % 16]); v /= 16; } while (v != 0);
      if (component.size() < 2) { component.insert(component.begin(), '0'); }

      text += (negative ? "-" : "") + component;
    }

    return text;
  }

  // t is meant to run from 0 to 1. Nothing says so in the signature, and
  // nothing here enforces it: mix(a, b, 1.4) is accepted and returns
  // components outside 0..255.
  inline color mix(color a, color b, double t)
  {
    return { static_cast<int>(a.red   + (b.red   - a.red)   * t),
             static_cast<int>(a.green + (b.green - a.green) * t),
             static_cast<int>(a.blue  + (b.blue  - a.blue)  * t) };
  }
}
