#include "octree.h"


OctreeNode * Octree::construct_ot(const std::vector<Vector3D> points, size_t max_depth) {
  //take points and construct tree from the node.
}

//when we first call this consuctor, we will have an empty BBox so this constructor needs to
Octree::Octree(std::vector<Point> points, int depth, Octree parent, BBox nodeBB, int maxDepth) {

  //if the depth is zero, expand the bbox etc but if not do other things
  if (depth == 0) {
    for (Point p : points) {
        NodeBB.expand(p.coordinates); //should expand the parent's bbox to include all points provide in our .ply.
        nodePoints.push_back(p);
    }

    this.maxDepth = maxDepth;


  } else {

  }

  Center = NodeBB.centroid();

  //generate the 8 inner children of the current node.
  if (points.size() != 0) { //generate children when the current one isn't empty.
  //create 8 vectors of points and then call the function that splits the bboxs in 8. Then go through all points
  //in this current node, if one is in one of those bboxs then add it to the matching vector
  //after this process is complete for all points, we can call the consutrctors for these children
  //with the constructed bboxs and vectors. Don't forget to put them in the current node's pointer array also.
  



  }


}
