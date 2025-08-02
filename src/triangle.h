#pragma once

#include "point3.h"
#include "transform.h"

#include <iostream>

template<typename T>
class Triangle {
  private:
    Point3<T> mA;
    Point3<T> mB;
    Point3<T> mC;

  public:
    Triangle(Point3<T> a, Point3<T> b, Point3<T> c): mA(a), mB(b), mC(c) {}

    Point3<T> GetA() const { return mA; }
    Point3<T> GetB() const { return mB; }
    Point3<T> GetC() const { return mC; }

    void Transform(Transform<T> t) {
      mA = t.RotatePoint(mA);
      mB = t.RotatePoint(mB);
      mC = t.RotatePoint(mC);
    }

    // with scalar
    Triangle<T>& operator*=(const T& rhs) {
      this->mA *= rhs;
      this->mB *= rhs;
      this->mC *= rhs;
      return *this;
    }
    Triangle<T>& operator/=(const T& rhs) {
      this->mA /= rhs;
      this->mB /= rhs;
      this->mC /= rhs;
      return *this;
    }

    // with point
    Triangle<T>& operator+=(const Point3<T>& rhs) {
      this->mA += rhs;
      this->mB += rhs;
      this->mC += rhs;
      return *this;
    }
    Triangle<T>& operator-=(const Point3<T>& rhs) {
      this->mA -= rhs;
      this->mB -= rhs;
      this->mC -= rhs;
      return *this;
    }
};

// with scalar
template<typename T>
Triangle<T> operator*(const Triangle<T>& lhs, const T& rhs) {
  return Triangle<T>(lhs.GetA() * rhs, lhs.GetB() * rhs, lhs.GetC() * rhs);
}
template<typename T>
Triangle<T> operator/(const Triangle<T>& lhs, const T& rhs) {
  return Triangle<T>(lhs.GetA() / rhs, lhs.GetB() / rhs, lhs.GetC() / rhs);
}

// with point
template<typename T>
Triangle<T> operator+(const Triangle<T>& lhs, const Point3<T>& rhs) {
  return Triangle<T>(lhs.GetA() + rhs, lhs.GetB() + rhs, lhs.GetC() + rhs);
}
template<typename T>
Triangle<T> operator-(const Triangle<T>& lhs, const Point3<T>& rhs) {
  return Triangle<T>(lhs.GetA() - rhs, lhs.GetB() - rhs, lhs.GetC() - rhs);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Triangle<T>& it) {
  os << "Vertex A: " << it.GetA() << " Vertex B: " << it.GetB() << " Vertex C: " << it.GetC();
  return os;
}