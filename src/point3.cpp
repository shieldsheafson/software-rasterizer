#include "point3.h"

// arithmetic operators with other point---------------------
Point3& Point3::operator+=(const Point3& rhs) {
  this->mX += rhs.mX;
  this->mY += rhs.mY;
  this->mZ += rhs.mZ;
  return *this;
}
Point3& Point3::operator-=(const Point3& rhs) {
  this->mX -= rhs.mX;
  this->mY -= rhs.mY;
  this->mZ -= rhs.mZ;
  return *this;
}
//-----------------------------------------------------------



// arithmetic operators with scalar------------------------
Point3& Point3::operator*=(float rhs) {
  this->mX *= rhs;
  this->mY *= rhs;
  this->mZ *= rhs;
  return *this;
}
Point3& Point3::operator/=(float rhs) {
  this->mX /= rhs;
  this->mY /= rhs;
  this->mZ /= rhs;
  return *this;
}
//-----------------------------------------------------------



// equality----------------------------------------------------
bool operator==(const Point3& lhs, const Point3& rhs) {
  return lhs.mX == rhs.mX && lhs.mY == rhs.mY && lhs.mZ == rhs.mZ;
}
bool operator!=(const Point3& lhs, const Point3& rhs) {
  return !(lhs == rhs);
}
//-------------------------------------------------------------



// arithmetic operators with other point-----------------------
Point3 operator+(const Point3& lhs, const Point3& rhs) {
  return Point3(lhs.mX + rhs.mX, lhs.mY + rhs.mY, lhs.mZ + rhs.mZ);
}
Point3 operator-(const Point3& lhs, const Point3& rhs) {
  return Point3(lhs.mX - rhs.mX, lhs.mY - rhs.mY, lhs.mZ - rhs.mZ);
}
//-------------------------------------------------------------



// arithmetic operators with scalar--------------------------
Point3 operator*(const Point3& lhs, float rhs) {
  return Point3(lhs.mX * rhs, lhs.mY * rhs, lhs.mZ * rhs);
}
Point3 operator/(const Point3& lhs, float rhs) {
  return Point3(lhs.mX / rhs, lhs.mY / rhs, lhs.mZ / rhs);
}
//--------------------------------------------------------------


// input/output-------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Point3& it) {
  os << it.mX << " " << it.mY << " " << it.mZ;
  return os;
}
std::istream& operator>>(std::istream& is, Point3& p) {
  is >> p.mX  >> p.mY >> p.mZ;
  return is;
}
//--------------------------------------------------------------