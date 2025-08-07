#pragma once

#include "point3.h"

#include <cmath>

class Transform {
  private:
    double mPitch;
    double mYaw;
    double mRoll;

    Point3 mPosition;
  public:
    Transform(): mPitch(0), mYaw(0), mRoll(0), mPosition(Point3(0,0,0)) {}
    Transform(double pitch, double yaw, double roll)
      : mPitch(pitch), mYaw(yaw), mRoll(roll), mPosition(Point3(0,0,0)) {}
    Transform(double pitch, double yaw, double roll, Point3 position)
      : mPitch(pitch), mYaw(yaw), mRoll(roll), mPosition(position) {}

    void SetYaw(double yaw) { mYaw = yaw; }
    void SetPitch(double pitch) { mPitch = pitch; }
    void SetRoll(double roll) { mRoll = roll; }

    double GetYaw() const { return mYaw; }
    double GetPitch() const { return mPitch; }
    double GetRoll() const { return mRoll; }

    Point3 TranslatePoint(const Point3& p) const { return p + mPosition; }

    Point3 RotatePoint(const Point3& p) const;
};