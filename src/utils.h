// temp file until i can figure out where these bits should actually go

#pragma once

#include "camera.h"
#include "color.h"
#include "model.h"
#include "point.h"
#include "point3.h"
#include "rendertarget.h"
#include "triangle.h"

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

template<typename T>
std::pair<Point<T>, Point<T> > BoundingBox(const Point3<T>& a, const Point3<T>& b, const Point3<T>& c) {
  T minX = std::min({a.mX, b.mX, c.mX});
  T minY = std::min({a.mY, b.mY, c.mY});

  T maxX = std::max({a.mX, b.mX, c.mX});
  T maxY = std::max({a.mY, b.mY, c.mY});
  
  return std::make_pair(Point<T>(minX, minY), Point<T>(maxX, maxY));
}

template<typename T>
void Render(const Model<T>& model, const Point3<T>& modelWorldPosition, RenderTarget& target, const Camera<T>& camera) {
  std::vector<Color> colors = {
    Color(255, 0, 0),    // Red
    Color(0, 255, 0),    // Lime
    Color(0, 0, 255),    // Blue
    Color(255, 255, 0),  // Yellow
    Color(255, 0, 255),  // Magenta
    Color(0, 255, 255),  // Cyan
    Color(255, 128, 0),  // Orange
    Color(128, 0, 255),  // Purple
    Color(0, 128, 255),  // Sky Blue
    Color(255, 0, 128),  // Hot Pink
    Color(128, 128, 0),  // Olive
    Color(0, 128, 128)   // Teal
};

  std::vector<std::vector<float> > depthBuffer(target.GetHeight(), std::vector<float>(target.GetWidth(), std::numeric_limits<float>::max()));


  std::vector<Triangle<T> > triangles = model.GetTriangles();

  for (unsigned int i = 0; i < triangles.size(); ++i) {
    const Triangle<T>& triangle = triangles.at(i);
    Point<T> numPixels = Point<T>(target.GetWidth(), target.GetHeight());
    Point3<T> a = TransformToScreenCoordinates(triangle.GetA(), modelWorldPosition, numPixels, camera);
    Point3<T> b = TransformToScreenCoordinates(triangle.GetB(), modelWorldPosition, numPixels, camera);
    Point3<T> c = TransformToScreenCoordinates(triangle.GetC(), modelWorldPosition, numPixels, camera);

    // ignore backfaces of triangles
    if (PointOnLeftSideOfVector(Point<T>(a.mX, a.mY), Point<T>(b.mX, b.mY), Point<T>(c.mX, c.mY))) {
      continue;
    }

    std::pair<Point<T>, Point<T> > boundingBox = BoundingBox(a, b, c);
    int minX = std::max(static_cast<int>(boundingBox.first.mX), 0);
    int maxX = std::min(static_cast<int>(boundingBox.second.mX), target.GetWidth());
    int minY = std::max(static_cast<int>(boundingBox.first.mY), 0);
    int maxY = std::min(static_cast<int>(boundingBox.second.mY), target.GetHeight());

    for (int y = minY; y < maxY; ++y) {
      for (int x = minX; x < maxX; ++x) {
        if (PointInTriangle(a, b, c, Point<T>(x, y))) {
          target.SetPixel(x, y, colors.at(i % 12));
        }
      }
    }
  }
}

template<typename T>
bool PointOnLeftSideOfVector(const Point<T>& a, const Point<T>& b, const Point<T>& p) {
  Point<T> ab = b - a;
  Point<T> ap = p - a;
  Point<T> abPerpendicular = ab.Perpendicular();
  return ap.Dot(abPerpendicular) < 0;
}

template<typename T>
bool PointInTriangle(const Point3<T>& a, const Point3<T>& b, const Point3<T>& c, const Point<T>& p) {
  // Point is inside the triangle if it is on the same side of all edges
  // We avoid rendering the back of triangles by only checking
  // if the point is on the left side of all edges
  if (PointOnLeftSideOfVector(Point<T>(a.mX, a.mY), Point<T>(b.mX, b.mY), p)) return false;
  if (PointOnLeftSideOfVector(Point<T>(b.mX, b.mY), Point<T>(c.mX, c.mY), p)) return false;
  if (PointOnLeftSideOfVector(Point<T>(c.mX, c.mY), Point<T>(a.mX, a.mY), p)) return false;
  return true;
}

template<typename T>
Point3<T> TransformToScreenCoordinates(const Point3<T>& localPoint, const Point3<T>& modelWorldPosition, const Point<T> numPixels, const Camera<T>& camera) {
  // working under the assumption vfov == hfov
  Point3<T> p = camera.GetTransform().RotatePoint(localPoint + modelWorldPosition - camera.GetPosition());

  double screenHeight = 2 * std::tan((camera.GetFov() / 2.0) * M_PI / 180.0);
  T pixelsPerWorldUnit = numPixels.mY / screenHeight / p.mZ;

  Point<T> pixelOffset = Point<T>(p.mX, p.mY) * pixelsPerWorldUnit;
  Point<T> screenPoint = numPixels / static_cast<T>(2) + pixelOffset;

  return Point3<T>(screenPoint.mX, screenPoint.mY, p.mZ);
}