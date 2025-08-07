#pragma once

#include "point3.h"
#include "transform.h"

class Camera {
  private:
    double mFov;
    Point3 mPosition;
    Transform mTransform;

  public:
    Camera()
      : mFov(60), mPosition(Point3(0,0,0)), mTransform(0, 0, 0) {}
    Camera(double fov, const Point3& position, double pitch, double yaw, double roll)
      : mFov(fov), mPosition(position), mTransform(pitch, yaw, roll) {}
    Camera(double fov, const Point3& position, const Transform& transform)
      : mFov(fov), mPosition(position), mTransform(transform) {}

    double GetFov() const { return mFov; }
    const Point3& GetPosition() const { return mPosition; }
    Point3& GetPosition() { return mPosition; }
    const Transform& GetTransform() const { return mTransform; }
    Transform& GetTransform() { return mTransform; }
    // double GetYaw() const { return mYaw; }
    // double GetPitch() const { return mPitch; }
    // double GetRoll() const { return mRoll; }

    void SetFov(double fov) { mFov = fov; }
    void SetPosition(const Point3& position) { mPosition = position; }
    void SetTransform(const Transform& transform) { mTransform = transform; }
    // void SetYaw(double yaw) { mYaw = yaw; }
    // void SetPitch(double pitch) { mPitch = pitch; }
    // void SetRoll(double roll) { mRoll = roll; }
};
