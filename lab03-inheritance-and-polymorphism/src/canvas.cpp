#include "canvas.hpp"

#include <ostream>

int canvas::alive_ = 0;

canvas::canvas(std::ostream& out, int width, int height)
: out_(out), width_(width), height_(height), centre_{width_ / 2.0, height_ / 2.0}
{
  ++alive_;

  out_ << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
       << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"" << width_
       << "\" height=\"" << height_
       << "\" viewBox=\"0 0 " << width_ << ' ' << height_ << "\">\n"
       << "<rect width=\"100%\" height=\"100%\" fill=\"#0d0d12\"/>\n";
}

// One constructor calling the other, in its own initialiser list. The header
// is written once, by the one that does the work.
canvas::canvas(std::ostream& out) : canvas(out, 900, 900)
{
}

canvas::~canvas()
{
  out_ << "</svg>\n";
  --alive_;
}

void canvas::line(point a, point b, color const& stroke, double thickness)
{
  out_ << "<line x1=\"" << a.x << "\" y1=\"" << a.y
       << "\" x2=\"" << b.x << "\" y2=\"" << b.y
       << "\" stroke=\"" << stroke.to_hex()
       << "\" stroke-width=\"" << thickness
       << "\" stroke-linecap=\"round\"/>\n";

  ++strokes_;
}

void canvas::draw(shape const& what, color const& fill)
{
  // The canvas asks and writes. It does not know, and never asks, which kind
  // of shape it is holding.
  out_ << what.outline(fill) << '\n';
  ++strokes_;
}

void canvas::open_group(std::string const& transform)
{
  out_ << "<g transform=\"" << transform << "\">\n";
  ++depth_;
}

void canvas::close_group()
{
  --depth_;
  out_ << "</g>\n";
}

int   canvas::width()   const { return width_;   }
int   canvas::height()  const { return height_;  }
point canvas::centre()  const { return centre_;  }
int   canvas::strokes() const { return strokes_; }
int   canvas::depth()   const { return depth_;   }

int canvas::alive() { return alive_; }

group::group(canvas& sheet, std::string const& transform) : sheet_(sheet)
{
  sheet_.open_group(transform);
}

group::~group() { sheet_.close_group(); }
