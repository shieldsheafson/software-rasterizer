#include "utils.h"

float PointDepth(const Point& point, const Point3& a, const Point3& b, const Point3& c) {
  float signedTriangleABPArea = SignedTriangleArea(a.TwoD(), b.TwoD(), point);
  float signedTriangleBCPArea = SignedTriangleArea(b.TwoD(), c.TwoD(), point);
  float signedTriangleCAPArea = SignedTriangleArea(c.TwoD(), a.TwoD(), point);

  if (signedTriangleABPArea < 0 || signedTriangleBCPArea < 0 || signedTriangleCAPArea < 0) {
    return -1;
  }

  float triangleABPArea = std::abs(signedTriangleABPArea);
  float triangleBCPArea = std::abs(signedTriangleBCPArea);
  float triangleCAPArea = std::abs(signedTriangleCAPArea);

  float totalTriangleArea = triangleABPArea + triangleBCPArea + triangleCAPArea;

  if (totalTriangleArea == 0) {
    return -1;
  }

  return a.mZ * (triangleBCPArea / totalTriangleArea)
         + b.mZ * (triangleCAPArea / totalTriangleArea)
         + c.mZ * (triangleABPArea / totalTriangleArea);
}

Point3 TransformToScreenCoordinates(const Point3& point, const Point& maxPoint, const Camera& camera) {
  // working under the assumption vfov == hfov
  // Point3 p = camera.GetTransform().RotatePoint(localPoint + modelWorldPosition - camera.GetPosition());

  double screenHeight = 2 * std::tan((camera.GetFov() / 2.0) * M_PI / 180.0);
  float pixelsPerWorldUnit = maxPoint.mY / screenHeight / point.mZ;

  Point pixelOffset = point.TwoD() * pixelsPerWorldUnit;
  Point screenPoint = maxPoint / 2.0f + pixelOffset;

  return Point3(screenPoint.mX, screenPoint.mY, point.mZ);
}

std::pair<Point, Point > BoundingBox(const Point& a, const Point& b, const Point& c) {
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

  Model movedModel = model + modelWorldPosition;
  movedModel.TransformModel(camera.GetTransform());

  std::vector<Triangle > triangles = movedModel.GetTriangles();

  for (unsigned int i = 0; i < triangles.size(); ++i) {
    Triangle triangle = triangles.at(i);

    if (triangle.GetA().mZ < 0 || triangle.GetB().mZ < 0 || triangle.GetC().mZ < 0) {
      continue;
    }

    Point maxPoint = Point(target.GetWidth(), target.GetHeight());

    // x y are screen coordinantes while z is the original depth
    Point3 a = TransformToScreenCoordinates(triangle.GetA(), maxPoint, camera);
    Point3 b = TransformToScreenCoordinates(triangle.GetB(), maxPoint, camera);
    Point3 c = TransformToScreenCoordinates(triangle.GetC(), maxPoint, camera);

    std::pair<Point, Point > boundingBox = BoundingBox(a.TwoD(), b.TwoD(), c.TwoD());
    int minX = std::max(static_cast<int>(boundingBox.first.mX), 0);
    int maxX = std::min(static_cast<int>(boundingBox.second.mX), target.GetWidth());
    int minY = std::max(static_cast<int>(boundingBox.first.mY), 0);
    int maxY = std::min(static_cast<int>(boundingBox.second.mY), target.GetHeight());

    for (int y = minY; y < maxY; ++y) {
      for (int x = minX; x < maxX; ++x) {
        Point currentScreenCoords = Point(x, y);

        float depth = PointDepth(currentScreenCoords, a, b, c);
        
        if (depth < depthBuffer.at(y).at(x) && depth >= 0) {
          depthBuffer.at(y).at(x) = depth;
          target.SetPixel(x, y, colors.at(i % 12));
        }
      }
    }
  }
}


float SignedTriangleArea(const Point& a, const Point& b, const Point& c) {
  Point ab = b - a;
  Point ac = c - a;
  Point abPerpendicular = ab.Perpendicular();
  return ac.Dot(abPerpendicular);
}