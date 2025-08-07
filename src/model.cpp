#include "model.h"

void Model::TransformModel(Transform r) {
  for (Triangle& triangle : mTriangles) {
    triangle.TransformTriangle(r);
  }
}

// with scalar
Model& Model::operator*=(float rhs) {
  for (Triangle&  triangle : mTriangles) {
    triangle *= rhs;
  }
  return *this;
}
Model& Model::operator/=(float rhs) {
  for (Triangle& triangle : mTriangles) {
    triangle /= rhs;
  }
  return *this;
}

// with point
Model& Model::operator+=(const Point3& rhs) {
  for (Triangle& triangle : mTriangles) {
    triangle += rhs;
  }
  return *this;
}
Model& Model::operator-=(const Point3& rhs) {
  for (Triangle& triangle : mTriangles) {
    triangle -= rhs;
  }
  return *this;
}

// with scalar

Model operator*(const Model& lhs, float rhs) {
  const std::vector<Triangle >& oldTriangles = lhs.GetTriangles();
  std::vector<Triangle > newTriangles;
  newTriangles.reserve(oldTriangles.size());
  for (const Triangle& triangle : oldTriangles) {
    newTriangles.push_back(triangle * rhs);
  } 

  return Model(newTriangles);
}

Model operator/(const Model& lhs, float rhs) {
  const std::vector<Triangle >& oldTriangles = lhs.GetTriangles();
  std::vector<Triangle > newTriangles;
  newTriangles.reserve(oldTriangles.size());
  for (const Triangle& triangle : oldTriangles) {
    newTriangles.push_back(triangle / rhs);
  } 

  return Model(newTriangles);
}

// with point

Model operator+(const Model& lhs, const Point3& rhs) {
  const std::vector<Triangle >& oldTriangles = lhs.GetTriangles();
  std::vector<Triangle > newTriangles;
  newTriangles.reserve(oldTriangles.size());
  for (const Triangle& triangle : oldTriangles) {
    newTriangles.push_back(triangle + rhs);
  } 

  return Model(newTriangles);
}

Model operator-(const Model& lhs, const Point3& rhs) {
  const std::vector<Triangle >& oldTriangles = lhs.GetTriangles();
  std::vector<Triangle > newTriangles;
  newTriangles.reserve(oldTriangles.size());
  for (const Triangle& triangle : oldTriangles) {
    newTriangles.push_back(triangle - rhs);
  } 

  return Model(newTriangles);
}