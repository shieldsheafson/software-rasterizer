#include "point.h"

// arithmetic operators with other point---------------------
Point& Point::operator+=(const Point& rhs) {
  this->mX += rhs.mX;
  this->mY += rhs.mY;
  return *this;
}
Point& Point::operator-=(const Point& rhs) {
  this->mX -= rhs.mX;
  this->mY -= rhs.mY;
  return *this;
}
//-----------------------------------------------------------



// arithmetic operators with scalar------------------------
Point& Point::operator*=(float rhs) {
  this->mX *= rhs;
  this->mY *= rhs;
  return *this;
}
Point& Point::operator/=(float rhs) {
  this->mX /= rhs;
  this->mY /= rhs;
  return *this;
}
//-----------------------------------------------------------



// equality----------------------------------------------------
bool operator==(const Point& lhs, const Point& rhs) {
  return lhs.mX == rhs.mX && lhs.mY == rhs.mY;
}
bool operator!=(const Point& lhs, const Point& rhs) {
  return !(lhs == rhs);
}
//-------------------------------------------------------------



// arithmetic operators with other point-----------------------
Point operator+(const Point& lhs, const Point& rhs) {
  return Point(lhs.mX + rhs.mX, lhs.mY + rhs.mY);
}
Point operator-(const Point& lhs, const Point& rhs) {
  return Point(lhs.mX - rhs.mX, lhs.mY - rhs.mY);
}
//-------------------------------------------------------------



// arithmetic operators with scalar--------------------------
Point operator*(const Point& lhs, float rhs) {
  return Point(lhs.mX * rhs, lhs.mY * rhs);
}
Point operator/(const Point& lhs, float rhs) {
  return Point(lhs.mX / rhs, lhs.mY / rhs);
}
//--------------------------------------------------------------


// input/output-------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Point& it) {
  os << it.mX << " " << it.mY;
  return os;
}
std::istream& operator>>(std::istream& is, Point& p) {
  is >> p.mX  >> p.mY;
  return is;
}
//--------------------------------------------------------------