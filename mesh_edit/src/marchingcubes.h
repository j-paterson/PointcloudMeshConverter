#ifndef MARCHINGCUBES_H
#define MARCHINGCUBES_H

typedef struct {
    vector<Vector3D> points;
} Triangle;

typedef struct{
  vector<Triangle> triangles;
  vector<Vector3D> points;
  double price;
} Mesh;

Mesh marchingCubes(OctreeNode currentNode, vFunctionCall IndicatorFunction);


#endif // MARCHINGCUBES_H
