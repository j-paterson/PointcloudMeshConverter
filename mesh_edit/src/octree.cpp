#include "octree.h"


OctreeNode * OctreeNode::construct_ot(const std::vector<Vector3D> points, size_t max_depth) {
  //take points and construct tree from the node.
}

//when we first call this consuctor, we will have an empty BBox so this constructor needs to
OctreeNode::OctreeNode(std::vector<Point> points, int depth, Octree parent, BBox nodeBB, int maxDepth) {

  //if the depth is zero, expand the bbox etc but if not do other things
  this.depth = depth;
  this.maxDepth = maxDepth;
  if (this.depth == 0 && this.depth != maxDepth) {
    for (Point p : points) {
        NodeBB.expand(p.coordinates); //should expand the parent's bbox to include all points provide in our .ply.
        nodePoints.push_back(p);
    }

    parent = nullptr;

  } else if (this.depth = maxDepth){
    this.isLeaf = true;


  }

  this.Center = NodeBB.centroid();

  //generate the 8 inner children of the current node.
  if (points.size() != 0) { //generate children when the current one isn't empty.
  //create 8 vectors of points and then call the function that splits the bboxs in 8. Then go through all points
  //in this current node, if one is in one of those bboxs then add it to the matching vector
  //after this process is complete for all points, we can call the consutrctors for these children
  //with the constructed bboxs and vectors. Don't forget to put them in the current node's pointer array also.
    std::vector<BBox> boxes = NodeBB.OctChildren();
    std::vector<<vector<Point>> pnts(8); //vector of 8 vectors of points

    for(Point p : points) {
      if (boxes[0].inside(p.coordinates)) {
        pnts[0].push_back(p);
      } else if (boxes[1].inside(p.coordinates)) {
        pnts[1].push_back(p);
      } else if (boxes[2].inside(p.coordinates)) {
        pnts[2].push_back(p);
      } else if (boxes[3].inside(p.coordinates)) {
        pnts[3].push_back(p);
      } else if (boxes[4].inside(p.coordinates)) {
        pnts[4].push_back(p);
      } else if (boxes[5].inside(p.coordinates)) {
        pnts[5].push_back(p);
      } else if (boxes[6].inside(p.coordinates)) {
        pnts[6].push_back(p);
      } else if (boxes[7].inside(p.coordinates)) {
        pnts[7].push_back(p);
      }
    }

    this.Children[0] = OctreeNode(pnts[0], this.depth + 1, boxes[0], this.maxDepth);
    this.Children[1] = OctreeNode(pnts[1], this.depth + 1, boxes[1], this.maxDepth);
    this.Children[2] = OctreeNode(pnts[2], this.depth + 1, boxes[2], this.maxDepth);
    this.Children[3] = OctreeNode(pnts[3], this.depth + 1, boxes[3], this.maxDepth);
    this.Children[4] = OctreeNode(pnts[4], this.depth + 1, boxes[4], this.maxDepth);
    this.Children[5] = OctreeNode(pnts[5], this.depth + 1, boxes[5], this.maxDepth);
    this.Children[6] = OctreeNode(pnts[6], this.depth + 1, boxes[6], this.maxDepth);
    this.Children[7] = OctreeNode(pnts[7], this.depth + 1, boxes[7], this.maxDepth);

    }
  }


}
