#ifndef MARCHINGCUBES_H
#define MARCHINGCUBES_H
#include "bbox.h"
#include "Point.h"
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "octree.h"

using namespace std;

typedef int (* vFunctionCall)(CGL::Vector3D args);

typedef struct {
    vector<CGL::Vector3D> points= * new vector<CGL::Vector3D>();
} Triangle;

typedef struct{
  vector<Triangle> triangles;
  vector<CGL::Vector3D> points;
  double price;
} Mesh;

void marchingCubes(OctreeNode currentNode, vFunctionCall IndicatorFunction, Mesh * final_mesh);
int IndicatorFunction(CGL::Vector3D point);

#endif // MARCHINGCUBES_H
