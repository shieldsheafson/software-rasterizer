#include "utils.h"

std::pair<Point, Point > BoundingBox(const Point3& a, const Point3& b, const Point3& c) {
  float minX = std::min({a.mX, b.mX, c.mX});
  float minY = std::min({a.mY, b.mY, c.mY});

  float maxX = std::max({a.mX, b.mX, c.mX});
  float maxY = std::max({a.mY, b.mY, c.mY});
  
  return std::make_pair(Point(minX, minY), Point(maxX, maxY));
}


void Render(const Model& model, const Point3& modelWorldPosition, RenderTarget& target, const Camera& camera) {
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


  std::vector<Triangle > triangles = model.GetTriangles();

  for (unsigned int i = 0; i < triangles.size(); ++i) {
    const Triangle& triangle = triangles.at(i);
    Point numPixels = Point(target.GetWidth(), target.GetHeight());
    Point3 a = TransformToScreenCoordinates(triangle.GetA(), modelWorldPosition, numPixels, camera);
    Point3 b = TransformToScreenCoordinates(triangle.GetB(), modelWorldPosition, numPixels, camera);
    Point3 c = TransformToScreenCoordinates(triangle.GetC(), modelWorldPosition, numPixels, camera);

    // ignore backfaces of triangles
    if (PointOnLeftSideOfVector(Point(a.mX, a.mY), Point(b.mX, b.mY), Point(c.mX, c.mY))) {
      continue;
    }

    std::pair<Point, Point > boundingBox = BoundingBox(a, b, c);
    int minX = std::max(static_cast<int>(boundingBox.first.mX), 0);
    int maxX = std::min(static_cast<int>(boundingBox.second.mX), target.GetWidth());
    int minY = std::max(static_cast<int>(boundingBox.first.mY), 0);
    int maxY = std::min(static_cast<int>(boundingBox.second.mY), target.GetHeight());

    for (int y = minY; y < maxY; ++y) {
      for (int x = minX; x < maxX; ++x) {
        if (PointInTriangle(a, b, c, Point(x, y))) {
          target.SetPixel(x, y, colors.at(i % 12));
        }
      }
    }
  }
}


bool PointOnLeftSideOfVector(const Point& a, const Point& b, const Point& p) {
  Point ab = b - a;
  Point ap = p - a;
  Point abPerpendicular = ab.Perpendicular();
  return ap.Dot(abPerpendicular) < 0;
}


float SignedTriangleArea(const Point& a, const Point& b, const Point& c) {
  Point ab = b - a;
  Point ac = c - a;
  Point abPerpendicular = ab.Perpendicular();
  return ac.Dot(abPerpendicular);
}


bool PointInTriangle(const Point3& a, const Point3& b, const Point3& c, const Point& p) {
  // Point is inside the triangle if it is on the same side of all edges
  // We avoid rendering the back of triangles by only checking
  // if the point is on the left side of all edges
  if (PointOnLeftSideOfVector(Point(a.mX, a.mY), Point(b.mX, b.mY), p)) return false;
  if (PointOnLeftSideOfVector(Point(b.mX, b.mY), Point(c.mX, c.mY), p)) return false;
  if (PointOnLeftSideOfVector(Point(c.mX, c.mY), Point(a.mX, a.mY), p)) return false;
  return true;
}


Point3 TransformToScreenCoordinates(const Point3& localPoint, const Point3& modelWorldPosition, const Point numPixels, const Camera& camera) {
  // working under the assumption vfov == hfov
  Point3 p = camera.GetTransform().RotatePoint(localPoint + modelWorldPosition - camera.GetPosition());

  double screenHeight = 2 * std::tan((camera.GetFov() / 2.0) * M_PI / 180.0);
  float pixelsPerWorldUnit = numPixels.mY / screenHeight / p.mZ;

  Point pixelOffset = Point(p.mX, p.mY) * pixelsPerWorldUnit;
  Point screenPoint = numPixels / 2.0f + pixelOffset;

  return Point3(screenPoint.mX, screenPoint.mY, p.mZ);
}