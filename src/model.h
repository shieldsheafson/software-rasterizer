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

class Model {
  private:
    std::vector<Triangle > mTriangles;

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
      std::vector<Point3 > vertices;
      vertices.reserve(1000);
      mTriangles.reserve(333);

      std::string line;
      while (std::getline(ifs, line)) {
        std::istringstream iss(line);
        std::string id;

        iss >> id;
        
        if (id == "v") {
          Point3 p;
          iss >> p;
          vertices.push_back(p);
        } else if (id == "f") {
          std::string face;
          Point3 a, b, c;

          int i = 0;
          while (iss >> face) {
            auto [vertexIndex, textureCoordinateIndex, vertexNormalIndex] = SplitFace(face);
            Point3 vertex = vertices.at(vertexIndex - 1);

            switch (i++) {
              case (0):
                a = vertex;
                break;
              case (1):
                b = vertex;
                break;
              case (2):
                c = vertex;
                mTriangles.push_back(Triangle(a, b, c));
                break;
              default:
                b = c;
                c = vertex;
                mTriangles.push_back(Triangle(a, b, c));
            }
          }
        }
      }
    }

  public:
    Model() {}
    Model(std::vector<Triangle > triangles): mTriangles(triangles) {}
    Model(std::string objFilePath) {
      std::ifstream ifs(objFilePath);

      if (!ifs.is_open()) {
        throw std::invalid_argument("File did not open");
      }

      LoadObjFile(ifs);
    }

    const std::vector<Triangle >& GetTriangles() const { return mTriangles; }

    void TransformModel(Transform r);

    // with scalar
    Model& operator*=(float rhs);
    Model& operator/=(float rhs);

    // with point
    Model& operator+=(const Point3& rhs);
    Model& operator-=(const Point3& rhs);
};

// with scalar
Model operator*(const Model& lhs, float rhs);
Model operator/(const Model& lhs, float rhs);

// with point
Model operator+(const Model& lhs, const Point3& rhs);
Model operator-(const Model& lhs, const Point3& rhs);