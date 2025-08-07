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

std::pair<Point, Point > BoundingBox(const Point3& a, const Point3& b, const Point3& c);

void Render(const Model& model, const Point3& modelWorldPosition, RenderTarget& target, const Camera& camera);

bool PointOnLeftSideOfVector(const Point& a, const Point& b, const Point& p);

float SignedTriangleArea(const Point& a, const Point& b, const Point& c);

bool PointInTriangle(const Point3& a, const Point3& b, const Point3& c, const Point& p);

Point3 TransformToScreenCoordinates(const Point3& localPoint, const Point3& modelWorldPosition, const Point numPixels, const Camera& camera);