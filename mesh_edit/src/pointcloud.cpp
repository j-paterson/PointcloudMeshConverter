#include "pointcloud.h"
#include <unordered_map>
#include <unordered_set>

using namespace std;

namespace CGL {
  PointCloud::PointCloud(int pts) {
    this->points = std::vector<Vector3D>(pts);
  }

  void PointCloud::add2mesh(Polymesh* mesh) const
  {
    for (int i = 0; i < (this->points.size() / 3); i++) {
        Vector3D v0, v1, v2;
        v0 = this->points[i];
        v1 = this->points[i + 1];
        v2 = this->points[i + 2];
        addTriangle(mesh, v0, v1, v2);
    }
  }

  void PointCloud::addTriangle(Polymesh* mesh, const Vector3D& v0, const Vector3D& v1, const Vector3D& v2) const
  {
    size_t base = mesh->vertices.size();
    mesh->vertices.push_back(v0);
    mesh->vertices.push_back(v1);
    mesh->vertices.push_back(v2);

    Polygon poly;
    poly.vertex_indices.push_back(base);
    poly.vertex_indices.push_back(base+1);
    poly.vertex_indices.push_back(base+2);
    mesh->polygons.push_back(poly);
  }

  void PointCloud::loadMesh(Polymesh* mesh, Mesh marchingCubesResult){
    for(int i =0; i<marchingCubesResult.triangles.size(); i++){
        addTriangle(mesh, marchingCubesResult.triangles[i].points[0],
                            marchingCubesResult.triangles[i].points[1],
                            marchingCubesResult.triangles[i].points[2]);
    }
  }

  void PointCloud::loadPoints(FILE* file) {
      for(int j = 0; j < this->points.size() / 3; j++)
      {
        fscanf(file, "%lf %lf %lf", &points[j].x, &points[j].y, &points[j].z);
        printf("loading points: %lf, %lf, %lf \n", points[j].x, points[j].y, points[j].z);
      }
  }

}
