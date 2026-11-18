#include "color.hpp"

#include <cassert>
#include <cmath>

namespace
{
  // GIVEN. The value of one hexadecimal digit, or -1 for any other character.
  int hex_value(char c)
  {
    if (c >= '0' && c <= '9') { return c - '0'; }
    if (c >= 'a' && c <= 'f') { return c - 'a' + 10; }
    if (c >= 'A' && c <= 'F') { return c - 'A' + 10; }
    return -1;
  }

  // TO WRITE. Bring an int back inside 0..255, by saturation.
  std::uint8_t saturate(int v)
  {
    if (v < 0) { return 0; }
    if (v > 255) { return 255; }
    return static_cast<std::uint8_t>(v);
  }
}

color::color(int r, int g, int b)
{
  // TO WRITE. Name the three parameters, and initialise the three
  // components from them through saturate.
  red_ = saturate(r);
  green_ = saturate(g);
  blue_ = saturate(b);
}

color::color(std::string_view hex)
{
  assert(hex.size() == 7 && hex[0] == '#');

  int const r1 = hex_value(hex[1]);
  int const r2 = hex_value(hex[2]);
  int const g1 = hex_value(hex[3]);
  int const g2 = hex_value(hex[4]);
  int const b1 = hex_value(hex[5]);
  int const b2 = hex_value(hex[6]);

  assert(r1 != -1 && r2 != -1 && g1 != -1 && g2 != -1 && b1 != -1 && b2 != -1);

  red_   = static_cast<std::uint8_t>(r1 * 16 + r2);
  green_ = static_cast<std::uint8_t>(g1 * 16 + g2);
  blue_  = static_cast<std::uint8_t>(b1 * 16 + b2);
}

int color::red()   const { return red_;   }
int color::green() const { return green_; }
int color::blue()  const { return blue_;  }

std::string color::to_hex() const
{
  char const digits[] = "0123456789abcdef";
  return {
    '#',
    digits[red_ / 16],
    digits[red_ % 16],
    digits[green_ / 16],
    digits[green_ % 16],
    digits[blue_ / 16],
    digits[blue_ % 16]
  };
}

color mix(color const& a, color const& b, double t)
{
  int const r = static_cast<int>(std::round(a.red()   + (b.red()   - a.red())   * t));
  int const g = static_cast<int>(std::round(a.green() + (b.green() - a.green()) * t));
  int const bl = static_cast<int>(std::round(a.blue()  + (b.blue()  - a.blue())  * t));
  return color{r, g, bl};
}
