#pragma once

#include <cmath>
#include <iostream>


struct Point {
  float mX;
  float mY;

  Point(): mX(0), mY(0) {}
  Point(float x, float y): mX(x), mY(y) {}

  float Dot(const Point& other) { return mX * other.mX + mY * other.mY; }
  Point Perpendicular() { return Point(mY, mX * -1); }

  // arithmetic operators with other point---------------------
  Point& operator+=(const Point& rhs);
  Point& operator-=(const Point& rhs);

  // arithmetic operators with scalar------------------------
  Point& operator*=(float rhs);
  Point& operator/=(float rhs);
};

// equality----------------------------------------------------
bool operator==(const Point& lhs, const Point& rhs);
bool operator!=(const Point& lhs, const Point& rhs);

// arithmetic operators with other point-----------------------
Point operator+(const Point& lhs, const Point& rhs);
Point operator-(const Point& lhs, const Point& rhs);

// arithmetic operators with scalar--------------------------
Point operator*(const Point& lhs, float rhs);
Point operator/(const Point& lhs, float rhs);

// input/output-------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Point& it);
std::istream& operator>>(std::istream& is, Point& p);
