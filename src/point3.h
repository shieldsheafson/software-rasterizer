#pragma once

#include <cmath>
#include <iostream>


struct Point3 {
  float mX;
  float mY;
  float mZ;

  Point3(): mX(0), mY(0) {}
  Point3(float x, float y, float z): mX(x), mY(y), mZ(z) {}

  float Dot(const Point3& other) { return mX * other.mX + mY * other.mY + mZ * other.mZ; }

  // arithmetic operators with other point---------------------
  Point3& operator+=(const Point3& rhs);
  Point3& operator-=(const Point3& rhs);

  // arithmetic operators with scalar------------------------
  Point3& operator*=(float rhs);
  Point3& operator/=(float rhs);
};

// equality----------------------------------------------------
bool operator==(const Point3& lhs, const Point3& rhs);
bool operator!=(const Point3& lhs, const Point3& rhs);

// arithmetic operators with other point-----------------------
Point3 operator+(const Point3& lhs, const Point3& rhs);
Point3 operator-(const Point3& lhs, const Point3& rhs);

// arithmetic operators with scalar--------------------------
Point3 operator*(const Point3& lhs, float rhs);
Point3 operator/(const Point3& lhs, float rhs);

// input/output-------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Point3& it);
std::istream& operator>>(std::istream& is, Point3& p);
