#pragma once

#include "color.hpp"
#include "geometry.hpp"

#include <iosfwd>
#include <string>

// WHAT THIS LAB IS ABOUT.
//
// Lab 1 wrote SVG through three free functions over a stream, and nothing
// forced open and close to balance. Forgetting close produced a file the
// browser refused, and the compiler had nothing to say about it.
//
// Here the header goes into a constructor and the closing tag into a
// destructor. The balance stops being a rule to remember and becomes a
// consequence of scope.
//
// The canvas takes a std::ostream&, and not a file name. That is what makes it
// checkable: the tests write into a std::ostringstream and read back what came
// out. Owning the file itself is lab 6.

class canvas
{
  public:
    canvas(std::ostream& out, int width, int height);

    // Delegating: the same thing on a 900 by 900 sheet. explicit, because
    // turning a stream into a canvas is not a conversion, it is a decision.
    explicit canvas(std::ostream& out);

    ~canvas();

    // Two canvases writing into one stream would each write a header and each
    // write a closing tag, into the same file. Lab 4 gives copying a meaning;
    // here it has none.
    canvas(canvas const&)            = delete;
    canvas& operator=(canvas const&) = delete;

    void line(point a, point b, color const& stroke, double thickness) const;

    // Called by group, which is the only thing that should call them: a group
    // opened by hand is a group that can be left open.
    void open_group(std::string const& transform);
    void close_group();

    int   width()   const;
    int   height()  const;
    point centre()  const;
    int   strokes() const;
    int   depth()   const;

    // How many canvases exist right now. Shared by the whole type rather than
    // held by each object, which is what static means on a member.
    static int alive();

  private:
    std::ostream& out_;
    int           width_;
    int           height_;
    
    // Computed from the two above, and therefore established after them. Which
    // is decided by the order of these declarations, and by nothing else.
    point         centre_;

    int           strokes_ = 0;
    int           depth_   = 0;

    static int alive_;
};

// A group of the drawing: writes an opening tag on construction, and the
// matching closing tag on destruction. Everything drawn in between lands in
// the coordinate system the transform sets up.
//
// Nothing else is needed to make the nesting right: the closing tags come out
// in the reverse order of the opening ones because destruction runs in the
// reverse order of construction.
class group
{
  public:
    group(canvas& sheet, std::string const& transform);
    ~group();

    group(group const&)            = delete;
    group& operator=(group const&) = delete;

  private:
    canvas& sheet_;
};
