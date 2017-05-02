#include "octree.h"
#include "bbox.h"
#include <iostream>
#include <vector>

using namespace std;

float hash_position(Vector3D currMin, Vector3D currMax, Vector3D rootMin, Vector3D rootMax) {
  // The actual position value hashed is the offset from the minimum bounds of the grid
  // This offset should always be positive
  float rootWidth = rootMax.x - rootMin.x;
  float rootHeight = rootMax.y - rootMin.y;
  float rootDepth = rootMax.z - rootMin.z;

  float leafWidth = currMax.x - currMin.x;
  float leafHeight = currMax.y - currMin.y;
  float leafDepth = currMax.z - currMin.z;

  float offset_x = currMin.x - rootMin.x;
  float offset_y = currMin.y - rootMin.y;
  float offset_z = currMin.z - rootMin.z;

  //Total number of nodes in the x direction
  float total_w = floor(rootWidth / leafWidth);
  //Current node is the hash_x -th node from the minimum
  float hash_x = floor(offset_x / leafWidth);

  //Total number of nodes in the y direction
  float total_h = floor(rootHeight / leafHeight);
  //curent node is the hash_y -th node from the minimum.
  float hash_y = floor(offset_y / leafHeight);

  //current node is the hash_z -th node from the minimum
  float hash_z = floor(offset_z / leafDepth);

  float hash = hash_x + (hash_y*total_w) + (hash_z*total_w*total_h);
//  if(hash>0){
//    cout<<"hash_x: ";
//    cout<<hash_x<<endl;
//    cout<<"hash_y: ";
//    cout<<hash_y<<endl;
//    cout<<"hash_z: ";
//    cout<<hash_z<<endl;
//    cout<<hash<<endl;
//  }
  return hash;
}

//when we first call this consuctor, we will have an empty BBox so this constructor needs to
OctreeNode::OctreeNode(OctreeNode* root, vector<Point> points, int depth, OctreeNode *Parent, BBox NodeBB, int maxDepth) {

    //if the depth is zero, expand the bbox etc but if not do other things
    this->depth = depth;
    this->maxDepth = maxDepth;
    this->NodeBB = NodeBB;
    this->Parent = Parent;
    this->hasChildren = false;
    this->root = root;

    if (this->depth == 0 && this->depth != maxDepth) {
      for (int i = 0; i < points.size(); i++) {
        this->NodeBB.expand(points[i].coordinates); //should expand the parent's bbox to include all points provide in our .ply.
    }

    this->root = this;
    this->Parent = nullptr;

    } else if (this->depth == maxDepth) {
      this->IsLeaf = true;
    }

    for (int i = 0; i < points.size(); i++) {
      this->nodePoints.push_back(points[i]);
    }

    this->Center = NodeBB.centroid();

    Vector3D HLW = this->NodeBB.max - this->NodeBB.min;
    this->HLW[0] = HLW[0];
    this->HLW[1] = HLW[1];
    this->HLW[2] = HLW[2];

    //generate the 8 inner children of the current node.
    if (points.size() != 0 && this->depth != maxDepth) { //generate children when the current one isn't empty.
    //create 8 vectors of points and then call the function that splits the bboxs in 8. Then go through all points
    //in this current node, if one is in one of those bboxs then add it to the matching vector
    //after this process is complete for all points, we can call the consutrctors for these children
    //with the constructed bboxs and vectors. Don't forget to put them in the current node's pointer array also.
      this->hasChildren = true;
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

    this->Children.push_back(OctreeNode(this->root, pnts[0], this->depth + 1, this, boxes[0], this->maxDepth));
    this->Children.push_back(OctreeNode(this->root, pnts[1], this->depth + 1, this, boxes[1], this->maxDepth));
    this->Children.push_back(OctreeNode(this->root, pnts[2], this->depth + 1, this, boxes[2], this->maxDepth));
    this->Children.push_back(OctreeNode(this->root, pnts[3], this->depth + 1, this, boxes[3], this->maxDepth));
    this->Children.push_back(OctreeNode(this->root, pnts[4], this->depth + 1, this, boxes[4], this->maxDepth));
    this->Children.push_back(OctreeNode(this->root, pnts[5], this->depth + 1, this, boxes[5], this->maxDepth));
    this->Children.push_back(OctreeNode(this->root, pnts[6], this->depth + 1, this, boxes[6], this->maxDepth));
    this->Children.push_back(OctreeNode(this->root, pnts[7], this->depth + 1, this, boxes[7], this->maxDepth));
    }
  }

   OctreeNode::OctreeNode(OctreeNode* root, int depth, BBox NodeBB, int maxDepth) {
      this->depth = depth;
      this->maxDepth = maxDepth;
      this->NodeBB = NodeBB;
      this->Center = NodeBB.centroid();
      this->hasChildren = false;
      this->root = root;

      if (depth == 0) {
        this->root = this;
      }

      if (depth == maxDepth) {
        this->IsLeaf = true;
      } else {
        this->IsLeaf = false;
      }

      Vector3D HLW = this->NodeBB.max - this->NodeBB.min;
      this->HLW[0] = HLW[0];
      this->HLW[1] = HLW[1];
      this->HLW[2] = HLW[2];

      if (depth != maxDepth) {
        vector<BBox> boxes = NodeBB.OctChildren();
        this->Children.push_back(OctreeNode(this->root, this->depth + 1, boxes[0], this->maxDepth));
        this->Children.push_back(OctreeNode(this->root, this->depth + 1, boxes[1], this->maxDepth));
        this->Children.push_back(OctreeNode(this->root, this->depth + 1, boxes[2], this->maxDepth));
        this->Children.push_back(OctreeNode(this->root, this->depth + 1, boxes[3], this->maxDepth));
        this->Children.push_back(OctreeNode(this->root, this->depth + 1, boxes[4], this->maxDepth));
        this->Children.push_back(OctreeNode(this->root, this->depth + 1, boxes[5], this->maxDepth));
        this->Children.push_back(OctreeNode(this->root, this->depth + 1, boxes[6], this->maxDepth));
        this->Children.push_back(OctreeNode(this->root, this->depth + 1, boxes[7], this->maxDepth));
        this->hasChildren = true;
      }
    }


    /*
    void OctreeNode::draw(OctreeNode *node, const Color& c) const {
      if (OctreeNode->isLeaf()) {
        for (Primitive *p : *(node->prims))
          p->draw(c);
      } else {
        draw(node->l, c);
        draw(node->r, c);
      }
    }

    void OctreeNode::drawOutline(OctreeNode *node, const Color& c) const {
      if (node->isLeaf()) {
        for (Primitive *p : *(node->prims))
          p->drawOutline(c);
      } else {
        drawOutline(node->l, c);
        drawOutline(node->r, c);
      }
      */
