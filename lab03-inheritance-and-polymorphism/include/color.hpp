#pragma once

#include <cstdint>
#include <string>
#include <string_view>

// THE INVARIANT.
//
// At every instant, the three components of a color are between 0 and 255.
// That is not a writing convention, it is a guarantee: no path leads to the
// three fields without going through a constructor that establishes it.
//
// Half of that guarantee is carried by the choice of the field type, and the
// other half by the constructors: the type carries the range, the
// constructors carry the meaning.

class color
{
  public:
    // Black, opaque. The default member initialisers below are what makes this
    // one legitimate: a color built by default is a color, not a shape of
    // three unspecified bytes.
    color() = default;

    // Three components. Anything outside 0..255 saturates: a caller asking for
    // 300 gets 255, and the object still holds its invariant.
    color(int r, int g, int b);

    // A color written "#ff8000". A string that is not one is a programming
    // error: this constructor asserts, where the one above saturates. An
    // out-of-range number has a nearest color, an ill-formed string has none.
    explicit color(std::string_view hex);

    int red()   const;
    int green() const;
    int blue()  const;

    // Always seven characters, whatever the color was built from.
    std::string to_hex() const;

  private:
    std::uint8_t red_   = 0;
    std::uint8_t green_ = 0;
    std::uint8_t blue_  = 0;
};

// A free function, not a member: it reads three components and builds a fourth
// color, all through the public interface. Making it a member would buy no
// access it does not already have.
color mix(color const& a, color const& b, double t);
