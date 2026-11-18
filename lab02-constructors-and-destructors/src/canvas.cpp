#include "canvas.hpp"

#include <ostream>

int canvas::alive_ = 0;

canvas::canvas(std::ostream& out, int w, int h)
: out_(out), width_(w), height_(h), centre_{static_cast<double>(width_) / 2.0, static_cast<double>(height_) / 2.0}
{
  // TO WRITE. Establish the four members from the two parameters, then
  // write the header. The reference to the stream must be established in the
  // initialiser list: a reference cannot be assigned afterwards.

  out_ << "<svg width=\"" << width_ << "\" height=\"" << height_ << "\">" << std::endl;
  ++alive_;
}

canvas::canvas(std::ostream& out) : canvas(out, 900, 900)
{
}

canvas::~canvas()
{
  // TO WRITE.
  out_ << "</svg>" << std::endl;
  --alive_;
}

void canvas::line(point a, point b, color const& stroke, double thickness) const
{
  // TO WRITE.
  out_ << "<line x1=\"" << a.x << "\" y1=\"" << a.y << "\" x2=\"" << b.x << "\" y2=\"" << b.y
      << "\" stroke=\"" << stroke.to_hex() << "\" stroke-width=\"" << thickness << "\" />" << std::endl;
  // ++strokes_;
}

void canvas::open_group(std::string const& transform)
{
  // TO WRITE.
  out_ << "<g transform=\"" << transform << "\">" << std::endl;
  ++depth_;
}

void canvas::close_group()
{
  // TO WRITE.
  out_ << "</g>" << std::endl;
  --depth_;
}

int   canvas::width()   const { return width_;   }
int   canvas::height()  const { return height_;  }
point canvas::centre()  const { return centre_;  }
int   canvas::strokes() const { return strokes_; }
int   canvas::depth()   const { return depth_;   }

int canvas::alive() { return alive_; }

group::group(canvas& sheet, std::string const& transform) : sheet_(sheet)
{
  // TO WRITE. Open the group here, and close it in the destructor
  // below. Those two lines are the whole class.
  sheet_.open_group(transform);
}

group::~group()
{
  // TO WRITE.
  sheet_.close_group();
}
