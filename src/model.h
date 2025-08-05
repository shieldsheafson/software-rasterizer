#pragma once

#include "point.h"
#include "point3.h"
#include "transform.h"
#include "triangle.h"

#include <fstream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

template<typename T>
class Model {
  private:
    std::vector<Triangle<T> > mTriangles;

    std::tuple<int, int, int> SplitFace(const std::string& s) {
      std::istringstream iss(s);
      std::string token;
      int values[3] = {0, 0, 0};
      int index = 0;
      
      while (std::getline(iss, token, '/') && index < 3 && token != "") {
        values[index++] = std::stoi(token);
      }
      
      return std::make_tuple(values[0], values[1], values[2]);
    }

    void LoadObjFile(std::ifstream& ifs) {
      // doesn't read from texture file yet
      std::vector<Point3<T> > vertices;
      vertices.reserve(1000);
      mTriangles.reserve(333);

      std::string line;
      while (std::getline(ifs, line)) {
        std::istringstream iss(line);
        std::string id;

        iss >> id;
        
        if (id == "v") {
          Point3<T> p;
          iss >> p;
          vertices.push_back(p);
        } else if (id == "f") {
          std::string face;
          Point3<T> a, b, c;

          int i = 0;
          while (iss >> face) {
            auto [vertexIndex, textureCoordinateIndex, vertexNormalIndex] = SplitFace(face);
            Point3<T> vertex = vertices.at(vertexIndex - 1);

            switch (i++) {
              case (0):
                a = vertex;
                break;
              case (1):
                b = vertex;
                break;
              case (2):
                c = vertex;
                mTriangles.push_back(Triangle<T>(a, b, c));
                break;
              default:
                b = c;
                c = vertex;
                mTriangles.push_back(Triangle<T>(a, b, c));
            }
          }
        }
      }
    }

  public:
    Model() {}
    Model(std::vector<Triangle<T> > triangles): mTriangles(triangles) {}
    Model(std::string objFilePath) {
      std::ifstream ifs(objFilePath);

      if (!ifs.is_open()) {
        throw std::invalid_argument("File did not open");
      }

      LoadObjFile(ifs);
    }

    const std::vector<Triangle<T> >& GetTriangles() const { return mTriangles; }

    void Transform(Transform<T> r) {
      for (Triangle<T>& triangle : mTriangles) {
        triangle.Transform(r);
      }
    }

    // with scalar
    Model<T>& operator*=(const T& rhs) {
      for (Triangle<T>&  triangle : mTriangles) {
        triangle *= rhs;
      }
      return *this;
    }
    Model<T>& operator/=(const T& rhs) {
      for (Triangle<T>& triangle : mTriangles) {
        triangle /= rhs;
      }
      return *this;
    }

    // with point
    Model<T>& operator+=(const Point3<T>& rhs) {
      for (Triangle<T>& triangle : mTriangles) {
        triangle += rhs;
      }
      return *this;
    }
    Model<T>& operator-=(const Point3<T>& rhs) {
      for (Triangle<T>& triangle : mTriangles) {
        triangle -= rhs;
      }
      return *this;
    }
  
};

// with scalar
template<typename T>
Model<T> operator*(const Model<T>& lhs, const T& rhs) {
  const std::vector<Triangle<T> >& oldTriangles = lhs.GetTriangles();
  std::vector<Triangle<T> > newTriangles;
  newTriangles.reserve(oldTriangles.size());
  for (const Triangle<T>& triangle : oldTriangles) {
    newTriangles.push_back(triangle * rhs);
  } 

  return Model(newTriangles);
}
template<typename T>
Model<T> operator/(const Model<T>& lhs, const T& rhs) {
  const std::vector<Triangle<T> >& oldTriangles = lhs.GetTriangles();
  std::vector<Triangle<T> > newTriangles;
  newTriangles.reserve(oldTriangles.size());
  for (const Triangle<T>& triangle : oldTriangles) {
    newTriangles.push_back(triangle / rhs);
  } 

  return Model(newTriangles);
}

// with point
template<typename T>
Model<T> operator+(const Model<T>& lhs, const Point3<T>& rhs) {
  const std::vector<Triangle<T> >& oldTriangles = lhs.GetTriangles();
  std::vector<Triangle<T> > newTriangles;
  newTriangles.reserve(oldTriangles.size());
  for (const Triangle<T>& triangle : oldTriangles) {
    newTriangles.push_back(triangle + rhs);
  } 

  return Model(newTriangles);
}
template<typename T>
Model<T> operator-(const Model<T>& lhs, const Point3<T>& rhs) {
  const std::vector<Triangle<T> >& oldTriangles = lhs.GetTriangles();
  std::vector<Triangle<T> > newTriangles;
  newTriangles.reserve(oldTriangles.size());
  for (const Triangle<T>& triangle : oldTriangles) {
    newTriangles.push_back(triangle - rhs);
  } 

  return Model(newTriangles);
}