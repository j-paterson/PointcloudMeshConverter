#include "bbox.h"
#include "Point.h"
#include <vector>


using namespace std;

class OctreeNode {
  public:
   //CAN PUT ANY SEARCH OR OTHER NECESSARY FUNCTION HERE.

   OctreeNode(vector<Point> points, int depth, OctreeNode *Parent, BBox NodeBB, int maxDepth);   //OctreeNode* root; ///< root node of the OT
   //OctreeNode *construct_ot(const std::vector<Vector3D> points, size_t max_depth);
    BBox NodeBB; // this has max, min, and extent members
    vector<OctreeNode> Children;
    OctreeNode * Parent; // optional
    vector<Point> nodePoints; //POINT CLASS
    CGL::Vector3D     Center;
    CGL::Vector3D     HalfSize;
    bool         IsLeaf;
    int maxDepth;
    int depth;
};
