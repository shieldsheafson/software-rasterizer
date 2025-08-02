#pragma once

#include "point3.h"

#include <cmath>

template<typename T>
class Transform {
  private:
    T mPitch;
    T mYaw;
    T mRoll;
  public:
    Transform(): mPitch(0), mYaw(0), mRoll(0) {}
    Transform(T pitch, T yaw, T roll): mPitch(pitch), mYaw(yaw), mRoll(roll) {}

    void SetYaw(T yaw) { mYaw = yaw; }
    void SetPitch(T pitch) { mPitch = pitch; }
    void SetRoll(T roll) { mRoll = roll; }

    T GetYaw() const { return mYaw; }
    T GetPitch() const { return mPitch; }
    T GetRoll() const { return mRoll; }

    Point3<T> RotatePoint(const Point3<T>& p) const {
      T cosPitch = std::cos(mPitch);
      T sinPitch = std::sin(mPitch);

      T cosYaw = std::cos(mYaw);
      T sinYaw = std::sin(mYaw);
      
      T cosRoll = std::cos(mRoll);
      T sinRoll = std::sin(mRoll);

      T m00 = cosYaw * cosRoll;
      T m01 = cosYaw * sinRoll;
      T m02 = -sinYaw;
      T m10 = sinPitch * sinYaw * cosRoll - cosPitch * sinRoll;
      T m11 = sinPitch * sinYaw * sinRoll + cosPitch * cosRoll;
      T m12 = sinPitch * cosYaw;
      T m20 = cosPitch * sinYaw * cosRoll + sinPitch * sinRoll;
      T m21 = cosPitch * sinYaw * sinRoll - sinPitch * cosRoll;
      T m22 = cosPitch * cosYaw;

      return Point3<T>(
        m00 * p.mX + m01 * p.mY + m02 * p.mZ,
        m10 * p.mX + m11 * p.mY + m12 * p.mZ,
        m20 * p.mX + m21 * p.mY + m22 * p.mZ
      );
  }
};