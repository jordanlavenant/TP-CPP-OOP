#pragma once

#include "color.hpp"
#include "geometry.hpp"

#include <memory>
#include <string>

// GIVEN, except for clone.
//
// This is the hierarchy of lab 3, with clone and its counter added. A shape is still
// not copyable: the two deleted operations below are still deleted, and lab 3
// left the reason open. This lab closes it.
//
// A shape held by its base cannot be copied by value -- what would the copy
// even be, when nobody at that point knows the kind? clone is the answer: the
// object copies itself, because it is the only one that knows what it is.

class shape
{
  public:
    explicit shape(point centre);

    // Still deleted. Copying is not forbidden here because it is dangerous,
    // but because through the base it is not expressible. clone replaces it.
    shape(shape const&)            = delete;
    shape& operator=(shape const&) = delete;

    virtual ~shape();

    virtual double      area()      const = 0;
    virtual double      perimeter() const = 0;
    virtual std::string outline(color const& fill) const = 0;
    virtual void        scale(double factor)              = 0;

    // The copy the base cannot perform, done by the object that can. Every
    // implementation has the same two lines: one increments cloned_, the other
    // creates the copy.
    virtual std::unique_ptr<shape> clone() const = 0;

    virtual std::string title() const;

    point centre() const;
    void  translate(point delta);
    void  scale_to_area(double target);

    static int alive();

    // How many shapes have been produced by clone since the last forget_clones.
    // Part 3 uses it to show that a move produces none.
    static int cloned();
    static void forget_clones();

  protected:
    point centre_;

    // Incremented by clone, and by nothing else.
    static int cloned_;

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

    std::unique_ptr<shape> clone() const override;

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

    std::unique_ptr<shape> clone() const override;

    double side() const;

  private:
    double side_;
};

class triangle : public shape
{
  public:
    triangle(point centre, double side);

    double      area()      const override;
    double      perimeter() const override;
    std::string outline(color const& fill) const override;
    void        scale(double factor)              override;
    std::string title() const override;

    std::unique_ptr<shape> clone() const override;

    double side() const;

  private:
    double side_;
};
