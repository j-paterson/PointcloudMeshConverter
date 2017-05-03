#include "plypase.h"

/*
PointCloud loadPointsAndNorms(FILE* file) {

  //should we negate the normals here?

  string currString = "";
  string elString = "";
  int numVertice = 0;
  CGL::Vector3D coordinatesHolder;
  CGL::Vector3D normalHolder;

  while (currString != "end_header") {
    fscanf(file, "%s", &currString);

    if (currString == "element") {
      fscanf(file, "%s", &elString);
      if (elString == "vertex") {
        fscanf(file, "%d", &numVertice);
      }
    }
  }

  PointCloud pc(numVertice);

  for (int i = 0; i < numVertice; i++) {

    fscanf(file, "%lf %lf %lf", coordinatesHolder.x, coordinatesHolder.y, coordinatesHolder.z);
    fscanf(file, "%lf %lf %lf", normalHolder.x, normalHolder.y, normalHolder.z);
    pc.points.push_back(Point(coordinatesHolder, normalHolder));

  }

  return pc;
}
*/
