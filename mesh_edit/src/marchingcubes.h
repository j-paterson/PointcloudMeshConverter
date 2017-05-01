#ifndef MARCHINGCUBES_H
#define MARCHINGCUBES_H
#include <vector>
#include "Point.h"
#include "octree.h"

using namespace std;

typedef int (* vFunctionCall)(Vector3D args);

typedef struct {
    vector<CGL::Vector3D> points;
} Triangle;

typedef struct{
  vector<Triangle> triangles;
  vector<CGL::Vector3D> points;
  double price;
} Mesh;

Mesh marchingCubes(OctreeNode currentNode, vFunctionCall IndicatorFunction);
int IndicatorFunction(CGL::Vector3D point);

#endif // MARCHINGCUBES_H
