// temp file until i can figure out where these bits should actually go

#pragma once

#include "color.h"
#include "model.h"
#include "point.h"
#include "point3.h"
#include "rendertarget.h"
#include "triangle.h"

#include <fstream>
#include <utility>
#include <cstdlib>
#include <string>
#include <tuple>
#include <vector>

template<typename T>
std::pair<Point<T>, Point<T> > BoundingBox(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
  T minX = std::min({a.mX, b.mX, c.mX});
  T minY = std::min({a.mY, b.mY, c.mY});

  T maxX = std::max({a.mX, b.mX, c.mX});
  T maxY = std::max({a.mY, b.mY, c.mY});
  
  return std::make_pair(Point<T>(minX, minY), Point<T>(maxX, maxY));
}

template<typename T>
void Render(const Model<T>& model, RenderTarget& target) {
  std::vector<Triangle<T> > triangles = model.GetTriangles();

  for (unsigned int i = 0; i < triangles.size(); ++i) {
    const Triangle<T>& triangle = triangles.at(i);
    Point<T> numPixels = Point<T>(target.GetWidth(), target.GetHeight());
    Point<T> a = TransformToScreenCoordinates(triangle.GetA(), numPixels);
    Point<T> b = TransformToScreenCoordinates(triangle.GetB(), numPixels);
    Point<T> c = TransformToScreenCoordinates(triangle.GetC(), numPixels);

    std::pair<Point<T>, Point<T> > boundingBox = BoundingBox(a, b, c);
    int minX = std::max(static_cast<int>(boundingBox.first.mX), 0);
    int maxX = std::min(static_cast<int>(boundingBox.second.mX), target.GetWidth());
    int minY = std::max(static_cast<int>(boundingBox.first.mY), 0);
    int maxY = std::min(static_cast<int>(boundingBox.second.mY), target.GetHeight());
    for (int y = minY; y < maxY; ++y) {
      for (int x = minX; x < maxX; ++x) {
        if (PointInTriangle(a, b, c, Point<T>(x, y))) {
          switch (i % 6) {
            case (0):
              target.SetPixel(x, y, Color(255, 0, 0));
              break;
            case (1):
              target.SetPixel(x, y, Color(0, 255, 0));
              break;
            case (2):
              target.SetPixel(x, y, Color(0, 0, 255));
              break;
            case (3):
              target.SetPixel(x, y, Color(255, 255, 0));
              break;
            case (4):
              target.SetPixel(x, y, Color(0, 255, 255));
              break;
            case (5):
              target.SetPixel(x, y, Color(255, 0, 255));
              break;
          }
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
bool PointInTriangle(const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& p) {
  if (PointOnLeftSideOfVector(a, b, p)) return false;
  if (PointOnLeftSideOfVector(b, c, p)) return false;
  if (PointOnLeftSideOfVector(c, a, p)) return false;
  return true;
}

template<typename T>
Point<T> TransformToScreenCoordinates(const Point3<T>& p, const Point<T> numPixels) {
  T pixelsPerWorldUnit = numPixels.mY / 5;

  Point<T> pixelOffset = Point<T>(p.mX, p.mY) * pixelsPerWorldUnit;

  return numPixels / static_cast<T>(2) + pixelOffset;
}