#pragma once

#include "canvas.hpp"
#include "color.hpp"
#include "geometry.hpp"
#include "shape.hpp"

#include <cstddef>
#include <memory>
#include <vector>

// THE POINT OF THIS LAB.
//
// A drawing holds shapes, any number of them, of any kind. It holds them by
// pointer, because it does not know their kinds -- and by owning pointer,
// because nobody else is going to destroy them.
//
// That one decision takes away the copy constructor. std::unique_ptr does not
// copy, so a vector of them does not either: the class is move-only without
// anyone having asked.
//
// Getting the copy back is not a matter of putting = default somewhere. It
// means saying what a copy of a shape is, when the only thing holding it is a
// pointer to a base that cannot copy itself. That is what clone is for, and it
// is the whole of part 2.

class drawing
{
  public:
    drawing() = default;

    // Deep: the copy owns its own shapes, and scaling one of them changes nothing
    // in the original. A check in tests/ holds it to that.
    drawing(drawing const& other);

    // Shallow on purpose: the pointers change hands, and not one shape is
    // built. The clone counter is what proves it.
    drawing(drawing&& other) noexcept;

    drawing& operator=(drawing const& other);
    drawing& operator=(drawing&& other) noexcept;

    ~drawing() = default;

    void add(std::unique_ptr<shape> what);

    std::size_t size()       const;
    double      total_area() const;

    // Applied to every shape the drawing owns. On a copy, they must leave the
    // original alone; that is the property the picture is built to show.
    void scale_all(double factor);
    void translate_all(point delta);

    void draw_into(canvas& sheet, color const& from, color const& to) const;

  private:
    std::vector<std::unique_ptr<shape>> shapes_;
};
