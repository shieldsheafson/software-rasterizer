#pragma once

#include <cmath>
#include <iostream>

template<typename T>
struct Point3 {
  T mX;
  T mY;
  T mZ;

  Point3(): mX(0), mY(0), mZ(0) {}
  Point3(T x, T y, T z): mX(x), mY(y), mZ(z) {}

  T Dot(const Point3<T>& other) { return mX * other.mX + mY * other.mY + mZ * other.mZ; }

  // arithmetic operators with other point---------------------
  Point3& operator+=(const Point3& rhs) {
    this->mX += rhs.mX;
    this->mY += rhs.mY;
    this->mZ += rhs.mZ;
    return *this;
  }
  Point3& operator-=(const Point3& rhs) {
    this->mX -= rhs.mX;
    this->mY -= rhs.mY;
    this->mZ -= rhs.mZ;
    return *this;
  }
  //-----------------------------------------------------------


  // arithmetic operators with scalar------------------------
  Point3& operator*=(const T& rhs) {
    this->mX *= rhs;
    this->mY *= rhs;
    this->mZ *= rhs;
    return *this;
  }

  Point3& operator/=(const T& rhs) {
    this->mX /= rhs;
    this->mY /= rhs;
    this->mZ /= rhs;
    return *this;
  }
  //-----------------------------------------------------------
};

// equality----------------------------------------------------
template<typename T>
bool operator==(const Point3<T>& lhs, const Point3<T>& rhs) {
  return lhs.mX == rhs.mX && lhs.mY == rhs.mY && lhs.mZ == rhs.mZ;
}
template<typename T>
bool operator!=(const Point3<T>& lhs, const Point3<T>& rhs) {
  return !(lhs == rhs);
}
//-------------------------------------------------------------



// arithmetic operators with other point-----------------------
template<typename T>
Point3<T> operator+(const Point3<T>& lhs, const Point3<T>& rhs) {
  return Point3<T>(lhs.mX + rhs.mX, lhs.mY + rhs.mY, lhs.mZ + rhs.mZ);
}
template<typename T>
Point3<T> operator-(const Point3<T>& lhs, const Point3<T>& rhs) {
  return Point3<T>(lhs.mX - rhs.mX, lhs.mY - rhs.mY, lhs.mZ - rhs.mZ);
}
//-------------------------------------------------------------



// arithmetic operators with scalar--------------------------
template<typename T>
Point3<T> operator*(const Point3<T>& lhs, const T& rhs) {
  return Point3<T>(lhs.mX * rhs, lhs.mY * rhs, lhs.mZ * rhs);
}
template<typename T>
Point3<T> operator/(const Point3<T>& lhs, const T& rhs) {
  return Point3<T>(lhs.mX / rhs, lhs.mY / rhs, lhs.mZ / rhs);
}
//--------------------------------------------------------------



// input/output-------------------------------------------------
template<typename T>
std::ostream& operator<<(std::ostream& os, const Point3<T>& p) {
  os << p.mX << " " << p.mY << " " << p.mZ;
  return os;
}
template<typename T>
std::istream& operator>>(std::istream& is, Point3<T>& p) {
  is >> p.mX  >> p.mY >> p.mZ;
  return is;
}
//--------------------------------------------------------------
