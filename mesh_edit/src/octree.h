
#if 0
struct OctreeInnerNode //this is the middle nodes, essentially all except the
{
    BBox InnerBB;
    OctreeInnerNode * Children[8]; //use a vector?
    OctreeInnerNode * Parent;
    Object *          FirstObj;
    Vector3D          Center;
    Vector3D          HalfSize;
    bool              IsLeaf;
};

struct OctreeLeafNode //We will need the leaf nodes to store the data from our base function and vector field computations.
{
  BBox bb;
  OctreeInnerNode * Parent; // optional
  std::vector<Point> nodePoints;
  Object *          Objects;
  Vector3           Center;
  Vector3           Center;
  bool              IsLeaf;
};

void findMaxPoints(std::vector<Vector3D> points, BBox bb) {
  //this SHOULDNT be necessary anymore

  //going to go through all of the points and find the maximum needed boundaries for our octTree root,
  //pass a some vector3Ds for the max extent, then we can modify these value by reference.
  //Then we can find the middle of our entire octree from this.
  //can just use the root's bbox and then expand it based on all of these points, the resulting bbox will contain
  //the necessary information to then use a function performing the operation decribed below to populate the bbox.
  //we can adapt the BBOX class to also be able to return the center of the box based on the Max AND the Min: we will need the half length

}
#endif

#include "bbox.h";


class OctreeNode {
  public:
   //CAN PUT ANY SEARCH OR OTHER NECESSARY FUNCTION HERE.

   OctreeNode(vector<Point> points, int depth, Octree parent, BBox nodeBB);
   //OctreeNode* root; ///< root node of the OT
   //OctreeNode *construct_ot(const std::vector<Vector3D> points, size_t max_depth);

  private:
    BBox NodeBB; // this has max, min, and extent members
    OctreeNode Children[8];
    OctreeNode * Parent; // optional
    std::vector<Point> nodePoints; //POINT CLASS
    Vector3D     Center;
    Vector3D     HalfSize;
    bool         IsLeaf;
    int depth;
}
