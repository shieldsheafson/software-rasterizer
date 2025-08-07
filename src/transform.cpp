#include "transform.h"

Point3 Transform::RotatePoint(const Point3& p) const {
  double cosPitch = std::cos(mPitch);
  double sinPitch = std::sin(mPitch);

  double cosYaw = std::cos(mYaw);
  double sinYaw = std::sin(mYaw);
  
  double cosRoll = std::cos(mRoll);
  double sinRoll = std::sin(mRoll);

  double m00 = cosYaw * cosRoll;
  double m01 = cosYaw * sinRoll;
  double m02 = -sinYaw;
  double m10 = sinPitch * sinYaw * cosRoll - cosPitch * sinRoll;
  double m11 = sinPitch * sinYaw * sinRoll + cosPitch * cosRoll;
  double m12 = sinPitch * cosYaw;
  double m20 = cosPitch * sinYaw * cosRoll + sinPitch * sinRoll;
  double m21 = cosPitch * sinYaw * sinRoll - sinPitch * cosRoll;
  double m22 = cosPitch * cosYaw;

  return Point3(
    m00 * p.mX + m01 * p.mY + m02 * p.mZ,
    m10 * p.mX + m11 * p.mY + m12 * p.mZ,
    m20 * p.mX + m21 * p.mY + m22 * p.mZ
  );
}