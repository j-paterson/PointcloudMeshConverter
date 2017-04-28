
struct OctreeNode //this is the parent
{
    BBox NodeBB; // this has max, min, and extent members
    OctreeInnerNode * Children[8];
    OctreeNode * Parent; // optional
    std::vector<Point> nodePoints; //POINT CLASS
    Vector3D     Center;
    Vector3D     HalfSize;
    bool         IsLeaf;
    int depth;

    OctreeNode(std::vector<Point> points) {
      //construct the root, go through all points in the provided vector and determine if they are in any of the children?
      //we should made a function that takes a node and computes the children's boundaries, shouldnt be too difficult
      //then we need a function which will take this of children extents and see if any of the points within the
      //parent node are within this child, if there are, then we can create that node and add any points to it that
      //are within it. If we don't find any

      //we can just initialize the bbox to be like NULL then use the expand operation on the list of points to expand to our needed size. then
      //we will have the dimension of the octree that we need.

      for (Point p : points) {
          NodeBB.expand(p.coordinates); //should expand the parent's bbox to include all points provide in our .ply.
      }

      Center = NodeBB.centroid();
      //NOW we already have the center of the box, we need to get the half size.
      //ALSO: Create a function which returns 8 such BBoxs from the current BBox.

      //generate the 8 inner children of the current node.
      if (points.size() != 0) { //generate children when the current one isn't empty.




      }



    }
};

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


class Octree {
  public:

   //CAN PUT ANY SEARCH OR OTHER NECESSARY FUNCTION HERE.
  private:
   OctreeNode* root; ///< root node of the OT
   OctreeNode *construct_ot(const std::vector<Vector3D> points, size_t max_depth);
}
