#include "svg.hpp"

#include <ostream>

namespace svg
{
  void open(std::ostream& out, int width, int height)
  {
    out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"" << width
        << "\" height=\"" << height
        << "\" viewBox=\"0 0 " << width << ' ' << height << "\">\n"
        << "<rect width=\"100%\" height=\"100%\" fill=\"#0d0d12\"/>\n";
  }

  void polyline(std::ostream& out, std::vector<point> const& points,
                color const& stroke, double thickness)
  {
    if (points.empty()) { return; }

    // stroke.to_hex() is written into the file as it comes. Nothing here
    // checks it: a color that is not a color becomes an attribute that is
    // not an attribute, and the browser is the one that finds out.
    out << "<polyline fill=\"none\" stroke=\"" << stroke.to_hex()
        << "\" stroke-width=\"" << thickness
        << "\" stroke-linecap=\"round\" stroke-linejoin=\"round\" points=\"";

    for (point const& p : points) { out << p.x << ',' << p.y << ' '; }

    out << "\"/>\n";
  }

  void close(std::ostream& out) { out << "</svg>\n"; }
}
