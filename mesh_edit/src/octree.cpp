#include "octree.h"
#include "bbox.h"
#include "Point.h"
#include <iostream>
#include <vector>

using namespace std;

//when we first call this consuctor, we will have an empty BBox so this constructor needs to
//when we first call this consuctor, we will have an empty BBox so this constructor needs to
OctreeNode::OctreeNode(vector<Point> points, int depth, OctreeNode *Parent, BBox NodeBB, int maxDepth) {

  //if the depth is zero, expand the bbox etc but if not do other things
  this->depth = depth;
  this->maxDepth = maxDepth;
  this->NodeBB = NodeBB;
  this->Parent = Parent;

  if (this->depth == 0 && this->depth != maxDepth) {
      for (int i = 0; i < points.size(); i++) {
        this->NodeBB.expand(points[i].coordinates); //should expand the parent's bbox to include all points provide in our .ply.
    }

    this->Parent = nullptr;

  } else if (this->depth == maxDepth) {
    this->IsLeaf = true;
  }

  for (int i = 0; i < points.size(); i++) {
      this->nodePoints.push_back(points[i]);
  }

  this->Center = NodeBB.centroid();

  //generate the 8 inner children of the current node.
  if (points.size() != 0 && this->depth != maxDepth) { //generate children when the current one isn't empty.
  //create 8 vectors of points and then call the function that splits the bboxs in 8. Then go through all points
  //in this current node, if one is in one of those bboxs then add it to the matching vector
  //after this process is complete for all points, we can call the consutrctors for these children
  //with the constructed bboxs and vectors. Don't forget to put them in the current node's pointer array also.
    vector<BBox> boxes = NodeBB.OctChildren();
    vector< vector<Point> > pnts(8); //vector of 8 vectors of points

    for(int i = 0; i < points.size(); i++) {
      if (boxes[0].inside(points[i].coordinates)) {
        pnts[0].push_back(points[i]);
      } else if (boxes[1].inside(points[i].coordinates)) {
        pnts[1].push_back(points[i]);
      } else if (boxes[2].inside(points[i].coordinates)) {
        pnts[2].push_back(points[i]);
      } else if (boxes[3].inside(points[i].coordinates)) {
        pnts[3].push_back(points[i]);
      } else if (boxes[4].inside(points[i].coordinates)) {
        pnts[4].push_back(points[i]);
      } else if (boxes[5].inside(points[i].coordinates)) {
        pnts[5].push_back(points[i]);
      } else if (boxes[6].inside(points[i].coordinates)) {
        pnts[6].push_back(points[i]);
      } else if (boxes[7].inside(points[i].coordinates)) {
        pnts[7].push_back(points[i]);
      }
    }

    this->Children.push_back(OctreeNode(pnts[0], this->depth + 1, this, boxes[0], this->maxDepth));
    this->Children.push_back(OctreeNode(pnts[1], this->depth + 1, this, boxes[1], this->maxDepth));
    this->Children.push_back(OctreeNode(pnts[2], this->depth + 1, this, boxes[2], this->maxDepth));
    this->Children.push_back(OctreeNode(pnts[3], this->depth + 1, this, boxes[3], this->maxDepth));
    this->Children.push_back(OctreeNode(pnts[4], this->depth + 1, this, boxes[4], this->maxDepth));
    this->Children.push_back(OctreeNode(pnts[5], this->depth + 1, this, boxes[5], this->maxDepth));
    this->Children.push_back(OctreeNode(pnts[6], this->depth + 1, this, boxes[6], this->maxDepth));
    this->Children.push_back(OctreeNode(pnts[7], this->depth + 1, this, boxes[7], this->maxDepth));


    }
  }
