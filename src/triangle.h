#pragma once

#include "point3.h"
#include "transform.h"

#include <iostream>

class Triangle {
  private:
    Point3 mA;
    Point3 mB;
    Point3 mC;

  public:
    Triangle(Point3 a, Point3 b, Point3 c): mA(a), mB(b), mC(c) {}

    Point3 GetA() const { return mA; }
    Point3 GetB() const { return mB; }
    Point3 GetC() const { return mC; }

    void TransformTriangle(Transform t);

    // with scalar
    Triangle& operator*=(float rhs);
    Triangle& operator/=(float rhs);

    // with point
    Triangle& operator+=(const Point3& rhs);
    Triangle& operator-=(const Point3& rhs);
};

// with scalar
Triangle operator*(const Triangle& lhs, float rhs);
Triangle operator/(const Triangle& lhs, float rhs);

// with point
Triangle operator+(const Triangle& lhs, const Point3& rhs);
Triangle operator-(const Triangle& lhs, const Point3& rhs);

std::ostream& operator<<(std::ostream& os, const Triangle& it);