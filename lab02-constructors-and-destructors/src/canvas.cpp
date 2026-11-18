#include "canvas.hpp"

#include <ostream>

int canvas::alive_ = 0;

canvas::canvas(std::ostream& out, int w, int h)
: out_(out), width_(w), height_(h), centre_{static_cast<double>(w) / 2.0, static_cast<double>(h) / 2.0}
{
  // TO WRITE. Establish the four members from the two parameters, then
  // write the header. The reference to the stream must be established in the
  // initialiser list: a reference cannot be assigned afterwards.

  out_ << "<svg width=\"" << width_ << "\" height=\"" << height_ << "\">" << std::endl;
  ++alive_;
}

canvas::canvas(std::ostream& out) : out_(out), width_(900), height_(900), centre_{450.0, 450.0}
{
  // TO WRITE. This repeats the other constructor instead of calling it.
  // Make it delegate, and check that the header is still written exactly once.
  out << "<svg width=\"" << width_ << "\" height=\"" << height_ << "\">" << std::endl;
  ++alive_;
}

canvas::~canvas()
{
  // TO WRITE.
  out_ << "</svg>" << std::endl;
  --alive_;
}

void canvas::line(point a, point b, color const& stroke, double thickness)
{
  // TO WRITE.
  (void)a; (void)b; (void)stroke; (void)thickness;
}

void canvas::open_group(std::string const& transform)
{
  // TO WRITE.
  (void)transform;
}

void canvas::close_group()
{
  // TO WRITE.
}

int   canvas::width()   const { return width_;   }
int   canvas::height()  const { return height_;  }
point canvas::centre()  const { return centre_;  }
int   canvas::strokes() const { return strokes_; }
int   canvas::depth()   const { return depth_;   }

int canvas::alive() { return alive_; }

group::group(canvas& sheet, std::string const&) : sheet_(sheet)
{
  // TO WRITE. Open the group here, and close it in the destructor
  // below. Those two lines are the whole class.
}

group::~group()
{
  // TO WRITE.
}
