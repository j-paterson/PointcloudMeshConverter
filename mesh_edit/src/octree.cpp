#include "octree.h"
#include "bbox.h"
#include "math.h"
#include <iostream>
#include <vector>

using namespace std;


float getHashKey(Vector3D rootValues, Vector3D leafValues, Vector3D currMin, Vector3D rootMin) {
  // The actual position value hashed is the offset from the minimum bounds of the grid
  // This offset should always be positive
  float offset_x = currMin.x - rootMin.x;
  float offset_y = currMin.y - rootMin.y;
  float offset_z = currMin.z - rootMin.z;

  //Total number of nodes in the x direction
  float total_w = floor(rootValues[0] / leafValues[0]);
  //Current node is the hash_x -th node from the minimum
  float hash_x = floor(offset_x / leafValues[0]);

  //Total number of nodes in the y direction
  float total_h = floor(rootValues[1] / leafValues[1]);
  //curent node is the hash_y -th node from the minimum.
  float hash_y = floor(offset_y / leafValues[1]);

  //current node is the hash_z -th node from the minimum
  float hash_z = floor(rootValues[2] / leafValues[2]);

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

void assignNeighbors(OctreeNode centerNode, std::unordered_map<float, OctreeNode> hashMap){
    bool finished = false;
    while(!finished){
        int internalRadius = 0;
        int externalRadius = 1;
        for(int x = -externalRadius; x < externalRadius; x++){
            for(int y = -externalRadius; y < externalRadius; y++){
                for(int z = -externalRadius; z < externalRadius; z++){
                    //if we make it all the way through the current perimeter and the points are full, finished will stay true.
                    finished=true;
                    //check to ensure that we are not within the internal radius.
                    bool insideInternalRadius = (abs(x)<internalRadius)&&(abs(y)<internalRadius)&&(abs(z)<internalRadius);

                    //We only want to be scanning the perimiter of the cube.
                    if(!insideInternalRadius){

                        //Checkpos is the location of the node we are indexing over to
                        Vector3D checkPos(centerNode.NodeBB.min.x + (x*centerNode.HLW[0]),
                                          centerNode.NodeBB.min.y + (y*centerNode.HLW[1]),
                                          centerNode.NodeBB.min.z + (x*centerNode.HLW[0]));

                        //Get the hashkey for that location
                        float hashKey = getHashKey(centerNode.root->HLW, centerNode.HLW, checkPos, centerNode.root->NodeBB.min);

                        //Make sure there is a leaf node at that location
                        if(hashMap.count(hashKey)>0){

                            //Scan through each point in the inputed leaf node
                            for(int p = 0; p < centerNode.nodePoints.size(); p++){

                                Point currentPoint=centerNode.nodePoints[p];

                                //calculate squared distance from the center of the current Node to the current Point
                                Vector3D currentNodePoint = hashMap.at(hashKey).NodeBB.min;
                                float currDistance = pow((currentPoint.coordinates.x-currentNodePoint.x),2)
                                                     +pow((currentPoint.coordinates.y-currentNodePoint.y),2)
                                                     +pow((currentPoint.coordinates.z-currentNodePoint.z),2);

                                //If the neighbors vector is <8, we can just add onto it.
                                if(currentPoint.neighbors.size()<8){
                                    Neighbor newNeighbor;
                                    newNeighbor.distance=currDistance;
                                    newNeighbor.hashKey= hashKey;
                                    currentPoint.neighbors.push_back(newNeighbor);
                                } else {
                                    //Otherwise, we must compare the distances already in the neighbors vector
                                    // to the current calculated distance.

                                    int replace_n=-1;
                                    int replace_dist=-1;

                                    for(int n = 0; n<currentPoint.neighbors.size(); n++){

                                        // For each neighbor, check if the distance to the current Node
                                        // is less than the distance to that neighbor
                                        float checkDistance = currentPoint.neighbors[n].distance;

                                        if(currDistance < checkDistance){

                                            /* if the distance to the current point is less than the
                                             * distance to one of the neighbors it might replace that neighbor.
                                             *
                                             */
                                            if(replace_dist<checkDistance || replace_dist==-1){
                                                replace_dist=checkDistance;
                                                replace_n=n;
                                            }
                                        }
                                    }
                                    if(replace_n!=-1){
                                        //This means we found a neighbor whose distance was greater than the distance to the current Node
                                        Neighbor newNeighbor;
                                        newNeighbor.distance=currDistance;
                                        newNeighbor.hashKey= hashKey;
                                        currentPoint.neighbors[replace_n] = newNeighbor;
                                    }
                                }
                                if(currentPoint.neighbors.size()<8){
                                    //If any of the points are under the total size, we need to expand the search radius
                                    finished=false;
                                }
                            }
                        }
                    }
                }
            }
        }
        internalRadius++;
        externalRadius++;
    }
}

int baseFunction(double t) {
  if (abs(t) < 0.5) {
    return 1;
  } else {
    return 0;
  }
}

double F(CGL::Vector3D v) {
  //n should equal 3, the number of convolutions
  double F = baseFunction(v.x) * baseFunction(v.y) * baseFunction(v.z);

  return F;
}

double Fo(CGL::Vector3D v, CGL::Vector3D nodeCenter, double nodeWidth)  {
  CGL::Vector3D newVec = (v - nodeCenter) / nodeWidth;
  return F(newVec) * ( 1.0 / pow(nodeWidth, 3));
}

//when we first call this consuctor, we will have an empty BBox so this constructor needs to
OctreeNode::OctreeNode(OctreeNode* root, vector<Point> points, int depth, OctreeNode *Parent, BBox NodeBB, int maxDepth) {

    //printf("hi im at depth: %d\n", depth);
    //if the depth is zero, expand the bbox etc but if not do other things
    this->depth = depth;
    this->maxDepth = maxDepth;
    this->NodeBB = NodeBB;
    this->Parent = Parent;
    this->hasChildren = false;
    this->root = root;

    if (this->depth == 0 && this->depth != maxDepth) {
      for (int i = 0; i < points.size(); i++) {
        //printf("%s\n", "Expanding!");
        this->NodeBB.expand(points[i].coordinates); //should expand the parent's bbox to include all points provide in our .ply.
      }
    //printf("max: %f\n", this->NodeBB.max.x);
    //printf("min: %f\n", this->NodeBB.min.x);

    this->root = this;
    this->Parent = nullptr;

    } else if (this->depth == maxDepth) {
      this->IsLeaf = true;
    }

    for (int i = 0; i < points.size(); i++) {
      this->nodePoints.push_back(points[i]);
    }

    this->Center = NodeBB.centroid();

    //Vector3D HLW = this->NodeBB.max - this->NodeBB.min;
    //this->HLW[0] = HLW[0];
    //this->HLW[1] = HLW[1];
    //this->HLW[2] = HLW[2];

    if (this->IsLeaf && points.size() != 0) {
      Vector3D pointSum;
      Vector3D normSum;
      for (int i = 0; i < points.size(); i++) {
        pointSum+=points[i].coordinates;
        normSum+=points[i].normal;
      }
      pointSum/=points.size();
      normSum/=points.size();

      this->avgPoint = pointSum;
      this->avgNorm = normSum;
    }

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

    CGL::Vector3D OctreeNode::projectPoint(CGL::Vector3D cornerPoint) {
      /*
      The projection of a point q = (x, y, z) onto a plane given by a point p = (a, b, c) and a normal n = (d, e, f) is

      q_proj = q - dot(q - p, n) * n
      This calculation assumes that n is a unit vector.

      this function projects "cornerPoint" onto the plane defined in the current node
      */
      Vector3D proj = cornerPoint - this->avgPoint;
      Vector3D unitAvg = this->avgNorm.unit();
      double dist = (unitAvg.x * proj.x) + (unitAvg.y * proj.y) + (unitAvg.z * proj.z);
      Vector3D projected_point = cornerPoint - dist*unitAvg;
      //Vector3D proj = cornerPoint - dot(cornerPoint - this->avgPoint, this->avgNorm.norm()) * this->avgNorm.norm();

      return projected_point;

    }
