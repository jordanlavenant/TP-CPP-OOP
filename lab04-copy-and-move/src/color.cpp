#include "color.hpp"

#include <cassert>

namespace
{
  // The value of one hexadecimal digit, or -1 for any other character.
  int hex_value(char c)
  {
    if (c >= '0' && c <= '9') { return c - '0'; }
    if (c >= 'a' && c <= 'f') { return c - 'a' + 10; }
    if (c >= 'A' && c <= 'F') { return c - 'A' + 10; }
    return -1;
  }

  // Bring an int back inside 0..255, by saturation.
  std::uint8_t saturate(int v)
  {
    if (v < 0)   { return 0; }
    if (v > 255) { return 255; }
    return static_cast<std::uint8_t>(v);
  }
}

color::color(int r, int g, int b)
: red_(saturate(r)), green_(saturate(g)), blue_(saturate(b))
{
}

color::color(std::string_view hex)
{
  // The check comes before the first access: hex[1] on an empty string reads
  // out of bounds.
  assert(hex.size() == 7 && hex[0] == '#');

  std::uint8_t* const component[3] = {&red_, &green_, &blue_};

  for (std::size_t i = 0; i < 3; ++i)
  {
    int const high = hex_value(hex[1 + 2 * i]);
    int const low  = hex_value(hex[2 + 2 * i]);

    assert(high >= 0 && low >= 0);

    *component[i] = static_cast<std::uint8_t>(high * 16 + low);
  }
}

int color::red()   const { return red_;   }
int color::green() const { return green_; }
int color::blue()  const { return blue_;  }

std::string color::to_hex() const
{
  static char const* const digits = "0123456789abcdef";

  // No padding, no sign, no length to check: the field type already says the
  // value is between 0 and 255, so two digits are always enough and always
  // needed. Compare with before::to_hex, which cannot say that.
  std::string text = "#";

  for (std::uint8_t const v : {red_, green_, blue_})
  {
    text += digits[v / 16];
    text += digits[v % 16];
  }

  return text;
}

color mix(color const& a, color const& b, double t)
{
  // t is not brought back into 0..1 here. It does not have to be: whatever
  // the three sums below come to, they go through the constructor, which
  // saturates, so the guarantee holds without mix doing anything for it.
  auto const blend = [t](int x, int y)
  { return static_cast<int>(x + (y - x) * t + 0.5); };

  return color{blend(a.red(),   b.red()),
                blend(a.green(), b.green()),
                blend(a.blue(),  b.blue())};
}
