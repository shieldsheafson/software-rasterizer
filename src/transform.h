#pragma once

#include "point3.h"

#include <cmath>

template<typename T>
class Transform {
  private:
    double mPitch;
    double mYaw;
    double mRoll;

    Point3<T> mPosition;
  public:
    Transform(): mPitch(0), mYaw(0), mRoll(0), mPosition(Point3<T>(0,0,0)) {}
    Transform(double pitch, double yaw, double roll)
      : mPitch(pitch), mYaw(yaw), mRoll(roll), mPosition(Point3<T>(0,0,0)) {}
    Transform(double pitch, double yaw, double roll, Point3<T> position)
      : mPitch(pitch), mYaw(yaw), mRoll(roll), mPosition(position) {}

    void SetYaw(double yaw) { mYaw = yaw; }
    void SetPitch(double pitch) { mPitch = pitch; }
    void SetRoll(double roll) { mRoll = roll; }

    double GetYaw() const { return mYaw; }
    double GetPitch() const { return mPitch; }
    double GetRoll() const { return mRoll; }

    Point3<T> TranslatePoint(const Point3<T>& p) const {
      return p + mPosition;
    }

    Point3<T> RotatePoint(const Point3<T>& p) const {
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

      return Point3<T>(
        m00 * p.mX + m01 * p.mY + m02 * p.mZ,
        m10 * p.mX + m11 * p.mY + m12 * p.mZ,
        m20 * p.mX + m21 * p.mY + m22 * p.mZ
      );
  }
};