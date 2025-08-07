#include "triangle.h"

void Triangle::TransformTriangle(Transform t) {
  mA = t.RotatePoint(mA);
  mB = t.RotatePoint(mB);
  mC = t.RotatePoint(mC);
}

// with scalar
Triangle& Triangle::operator*=(float rhs) {
  this->mA *= rhs;
  this->mB *= rhs;
  this->mC *= rhs;
  return *this;
}
Triangle& Triangle::operator/=(float rhs) {
  this->mA /= rhs;
  this->mB /= rhs;
  this->mC /= rhs;
  return *this;
}

// with point
Triangle& Triangle::operator+=(const Point3& rhs) {
  this->mA += rhs;
  this->mB += rhs;
  this->mC += rhs;
  return *this;
}
Triangle& Triangle::operator-=(const Point3& rhs) {
  this->mA -= rhs;
  this->mB -= rhs;
  this->mC -= rhs;
  return *this;
}

// with scalar
Triangle operator*(const Triangle& lhs, float rhs) {
  return Triangle(lhs.GetA() * rhs, lhs.GetB() * rhs, lhs.GetC() * rhs);
}
Triangle operator/(const Triangle& lhs, float rhs) {
  return Triangle(lhs.GetA() / rhs, lhs.GetB() / rhs, lhs.GetC() / rhs);
}

// with point
Triangle operator+(const Triangle& lhs, const Point3& rhs) {
  return Triangle(lhs.GetA() + rhs, lhs.GetB() + rhs, lhs.GetC() + rhs);
}
Triangle operator-(const Triangle& lhs, const Point3& rhs) {
  return Triangle(lhs.GetA() - rhs, lhs.GetB() - rhs, lhs.GetC() - rhs);
}


std::ostream& operator<<(std::ostream& os, const Triangle& it) {
  os << "Vertex A: " << it.GetA() << " Vertex B: " << it.GetB() << " Vertex C: " << it.GetC();
  return os;
}