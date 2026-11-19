#pragma once

#include "color.hpp"
#include "geometry.hpp"

#include <string>

// THE POINT OF THIS LAB.
//
// scale_to_area, at the bottom of the public section below, is not virtual.
// It is written once, in the base, and it works for a circle, for a square and
// for a triangle -- because the two things it uses, area and scale, are.
//
// That is what the drawing shows: five hundred shapes of three kinds, all of
// exactly the same area at the same distance from the centre. A wrong area on
// one of the three kinds comes out as a visibly wrong size, and nothing else
// has to be checked to see it.

class shape
{
  public:
    explicit shape(point centre);

    // Deleting one of the two would be enough to make the point; both are
    // deleted so that no copy of a shape happens by accident before a later lab
    // has said what a copy of a shape should be.
    shape(shape const&)            = delete;
    shape& operator=(shape const&) = delete;

    // The one that decides whether deleting through this base is defined
    // behaviour or not.
    virtual ~shape();

    // No sensible answer exists here: a shape with no kind has no area. The
    // = 0 says exactly that, and makes the class abstract.
    virtual double      area()      const;
    virtual double      perimeter() const;
    virtual std::string outline(color const& fill) const;
    virtual void        scale(double factor);

    // This one does have a sensible answer, so it is virtual without being
    // pure. Each kind gives a better one. A derived class that means to
    // replace it and misses is the case the lab looks at.
    virtual std::string title() const;

    point centre() const;
    void  translate(point delta);

    // Not virtual, and written once for every shape there will ever be.
    void scale_to_area(double target);

    static int alive();

  protected:
    point centre_;

  private:
    static int alive_;
};

class circle : public shape
{
  public:
    circle(point centre, double radius);

    double      area()      const override;
    double      perimeter() const override;
    std::string outline(color const& fill) const override;
    void        scale(double factor)              override;
    std::string title() const override;

    double radius() const;

  private:
    double radius_;
};

class square : public shape
{
  public:
    square(point centre, double side);

    double      area()      const override;
    double      perimeter() const override;
    std::string outline(color const& fill) const override;
    void        scale(double factor)              override;
    std::string title() const override;

    double side() const;

  private:
    double side_;
};

// Equilateral, and pointing up. Its area is the one of the three that cannot
// be guessed, which is why it is the one the drawing catches.
class triangle : public shape
{
  public:
    triangle(point centre, double side);

    double      area()      const override;
    double      perimeter() const override;
    std::string outline(color const& fill) const override;
    void        scale(double factor)              override;
    std::string title() const override;

    double side() const;

  private:
    double side_;
};
