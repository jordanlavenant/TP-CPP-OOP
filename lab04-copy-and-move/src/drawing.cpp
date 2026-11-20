#include "drawing.hpp"

#include <utility>

drawing::drawing(drawing const& other)
{
  // TO WRITE. One loop. The vector cannot copy its elements, so
  // something else has to say what a copy of a shape is.
  // shapes_.reserve(other.shapes_.size());
  for (auto const& s : other.shapes_)
  {
    shapes_.push_back(s->clone());
  }
}

drawing::drawing(drawing&& other) noexcept
: shapes_(std::move(other.shapes_))
{
  // TO WRITE. The vector moves. Nothing here builds a shape.
}

drawing& drawing::operator=(drawing const& other)
{
  // TO WRITE.
  drawing copy = other;
  std::swap(shapes_, copy.shapes_);
  return *this;
}

drawing& drawing::operator=(drawing&& other) noexcept
{
  // TO WRITE.
  shapes_ = std::move(other.shapes_);
  return *this;
}

void drawing::add(std::unique_ptr<shape> what) { shapes_.push_back(std::move(what)); }

std::size_t drawing::size() const { return shapes_.size(); }

double drawing::total_area() const
{
  double total = 0.0;
  for (auto const& one : shapes_) { total += one->area(); }
  return total;
}

void drawing::scale_all(double factor)
{
  for (auto const& one : shapes_) { one->scale(factor); }
}

void drawing::translate_all(point delta)
{
  for (auto const& one : shapes_) { one->translate(delta); }
}

void drawing::draw_into(canvas& sheet, color const& from, color const& to) const
{
  if (shapes_.empty()) { return; }

  for (std::size_t i = 0; i < shapes_.size(); ++i)
  {
    double const t = shapes_.size() == 1
                   ? 0.0
                   : static_cast<double>(i) / static_cast<double>(shapes_.size() - 1);

    sheet.draw(*shapes_[i], mix(from, to, t));
  }
}
