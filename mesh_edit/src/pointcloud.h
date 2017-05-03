#ifndef POINTCLOUD_H
#define	POINTCLOUD_H

#include "CGL/CGL.h"
#include "mesh.h"
#include "marchingcubes.h"

namespace CGL {

  class PointCloud {
    public:
      PointCloud(int pts);
      void add2mesh(Polymesh* mesh) const;
      void loadPoints(FILE* file);
      void loadMesh(Polymesh* mesh, Mesh marchingCubesResult);
      void addTriangle(Polymesh* mesh, const Vector3D& v0, const Vector3D& v1, const Vector3D& v2) const;

      std::vector<Point> points;
  };

}
#endif
