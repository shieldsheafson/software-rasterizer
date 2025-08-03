#pragma once

#include <cmath>
#include <iostream>

template<typename T>
struct Point {
  T mX;
  T mY;

  Point(): mX(0), mY(0) {}
  Point(T x, T y): mX(x), mY(y) {}

  T Dot(const Point<T>& other) { return mX * other.mX + mY * other.mY; }
  Point<T> Perpendicular() { return Point<T>(mY, mX * -1); }

  // arithmetic operators with other point---------------------
  Point& operator+=(const Point& rhs) {
    this->mX += rhs.mX;
    this->mY += rhs.mY;
    return *this;
  }
  Point& operator-=(const Point& rhs) {
    this->mX -= rhs.mX;
    this->mY -= rhs.mY;
    return *this;
  }
  //-----------------------------------------------------------


  // arithmetic operators with scalar------------------------
  Point& operator*=(const T& rhs) {
    this->mX *= rhs;
    this->mY *= rhs;
    return *this;
  }

  Point& operator/=(const T& rhs) {
    this->mX /= rhs;
    this->mY /= rhs;
    return *this;
  }
  //-----------------------------------------------------------
};

// equality----------------------------------------------------
template<typename T>
bool operator==(const Point<T>& lhs, const Point<T>& rhs) {
  return lhs.mX == rhs.mX && lhs.mY == rhs.mY;
}
template<typename T>
bool operator!=(const Point<T>& lhs, const Point<T>& rhs) {
  return !(lhs == rhs);
}
//-------------------------------------------------------------



// arithmetic operators with other point-----------------------
template<typename T>
Point<T> operator+(const Point<T>& lhs, const Point<T>& rhs) {
  return Point<T>(lhs.mX + rhs.mX, lhs.mY + rhs.mY);
}
template<typename T>
Point<T> operator-(const Point<T>& lhs, const Point<T>& rhs) {
  return Point<T>(lhs.mX - rhs.mX, lhs.mY - rhs.mY);
}
//-------------------------------------------------------------



// arithmetic operators with scalar--------------------------
template<typename T>
Point<T> operator*(const Point<T>& lhs, const T& rhs) {
  return Point<T>(lhs.mX * rhs, lhs.mY * rhs);
}
template<typename T>
Point<T> operator/(const Point<T>& lhs, const T& rhs) {
  return Point<T>(lhs.mX / rhs, lhs.mY / rhs);
}
//--------------------------------------------------------------


// input/output-------------------------------------------------
template<typename T>
std::ostream& operator<<(std::ostream& os, const Point<T>& it) {
  os << it.mX << " " << it.mY;
  return os;
}
template<typename T>
std::istream& operator>>(std::istream& is, Point<T>& p) {
  is >> p.mX  >> p.mY;
  return is;
}
//--------------------------------------------------------------
