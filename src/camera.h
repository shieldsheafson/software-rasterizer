#pragma once

#include "point3.h"
#include "transform.h"

template<typename T>
class Camera {
  private:
    double mFov;
    Point3<T> mPosition;
    Transform<T> mTransform;

  public:
    Camera()
      : mFov(60), mPosition(Point3<T>(0,0,0)), mTransform(0, 0, 0) {}
    Camera(double fov, const Point3<T>& position, double pitch, double yaw, double roll)
      : mFov(fov), mPosition(position), mTransform(pitch, yaw, roll) {}
    Camera(double fov, const Point3<T>& position, const Transform<T>& transform)
      : mFov(fov), mPosition(position), mTransform(transform) {}

    double GetFov() const { return mFov; }
    const Point3<T>& GetPosition() const { return mPosition; }
    Point3<T>& GetPosition() { return mPosition; }
    const Transform<T>& GetTransform() const { return mTransform; }
    Transform<T>& GetTransform() { return mTransform; }
    // double GetYaw() const { return mYaw; }
    // double GetPitch() const { return mPitch; }
    // double GetRoll() const { return mRoll; }

    void SetFov(double fov) { mFov = fov; }
    void SetPosition(const Point3<T>& position) { mPosition = position; }
    void SetTransform(const Transform<T>& transform) { mTransform = transform; }
    // void SetYaw(double yaw) { mYaw = yaw; }
    // void SetPitch(double pitch) { mPitch = pitch; }
    // void SetRoll(double roll) { mRoll = roll; }
};
