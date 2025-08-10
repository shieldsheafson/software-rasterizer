#pragma once

#include "point3.h"
#include "transform.h"

class Camera {
  private:
    double mFov;
    Transform mTransform;

  public:
    Camera()
      : mFov(60), mTransform(0, 0, 0) {}
    Camera(double fov, const Point3& position, double pitch, double yaw, double roll)
      : mFov(fov), mTransform(pitch, yaw, roll) {}
    Camera(double fov, const Point3& position, const Transform& transform)
      : mFov(fov), mTransform(transform) {}

    double GetFov() const { return mFov; }
    const Transform& GetTransform() const { return mTransform; }
    Transform& GetTransform() { return mTransform; }

    void SetFov(double fov) { mFov = fov; }
    void SetTransform(const Transform& transform) { mTransform = transform; }

    void Forward(float distance) {
      double cosPitch = std::cos(mTransform.GetPitch());
      double sinPitch = std::sin(mTransform.GetPitch());
      double cosYaw = std::cos(mTransform.GetYaw());
      double sinYaw = std::sin(mTransform.GetYaw());
      double cosRoll = std::cos(mTransform.GetRoll());
      double sinRoll = std::sin(mTransform.GetRoll());
      
      mTransform.SetPosition(mTransform.GetPosition() - Point3(sinYaw, 0, cosYaw) * distance);
    }

    void Backward(float distance) { Forward(-1 * distance); }
    void Left(float distance) {
      double cosPitch = std::cos(mTransform.GetPitch());
      double sinPitch = std::sin(mTransform.GetPitch());
      double cosYaw = std::cos(-mTransform.GetYaw());
      double sinYaw = std::sin(-mTransform.GetYaw());
      double cosRoll = std::cos(mTransform.GetRoll());
      double sinRoll = std::sin(mTransform.GetRoll());

      double leftX = -(cosYaw * cosRoll);
      double leftY = -(sinPitch * sinYaw * cosRoll - cosPitch * sinRoll);
      double leftZ = -(cosPitch * sinYaw * cosRoll + sinPitch * sinRoll);
      
      mTransform.SetPosition(mTransform.GetPosition() - Point3(leftX, leftY, leftZ) * distance);
    }
    void Right(float distance) { Left(-1 * distance); }

    void PanUp(double radians) { mTransform.SetPitch(mTransform.GetPitch() + radians); }
    void PanDown(double radians) { mTransform.SetPitch(mTransform.GetPitch() - radians); }
    void PanLeft(double radians) { mTransform.SetYaw(mTransform.GetYaw() - radians); }
    void PanRight(double radians) { mTransform.SetYaw(mTransform.GetYaw() + radians); }
};
