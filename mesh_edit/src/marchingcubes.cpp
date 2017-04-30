#include "marchingcubes.h"
#include "octree.h"

namespace CGL {

typedef void (* vFunctionCall)(Vector3D args);

/*
    Calculate an index for the octree node's cube by checking the indicator function.
    Using the index, look up the list of edges from a precalculated table.
    Using the densities at each edge vertex, find the surface edge intersection via linear interpolation.
    Calculate a unit normal at each cube vertex using central differences. Interpolate the normal to each triangle vertex.
    Output the triangle vertices and vertex normals.
*/

struct Triangle{
    vector<Vector3D> points;
};

struct Mesh {
  vector<Triangle> triangles;
  vector<Vector3D> points;
  double price;
};

marchingCubes(OctreeNode currentNode, vFunctionCall IndicatorFunction)
{
    Mesh final_mesh = new Mesh;
    //checking to see if there are children for the current node
    if(!currentNode.IsLeaf && currentNode.nodePoints.size()!=0){
        for(int i = 0; i<8; i++){
            marchingCubes(currentNode.Children[i], IndicatorFunction);
        }
    }else if(currentNode.IsLeaf){
        //we have hit a leaf node, calculate an index for the octree node's cube.

        //Using the index, look up the list of edges from the precalculated table
    }
}

unsigned char getIndex(OctreeNode currentNode, vFunctionCall IndicatorFunction)
{
    unsigned char index=0;
    //Use Bryce's function to get all corners
    vector<Vector3D> corners = getCorners(currentNode);
    if (IndicatorFunction(corners[0])==1) index |=   1;
    if (IndicatorFunction(corners[1])==1) index |=   2;
    if (IndicatorFunction(corners[2])==1) index |=   4;
    if (IndicatorFunction(corners[3])==1) index |=   8;
    if (IndicatorFunction(corners[4])==1) index |=  16;
    if (IndicatorFunction(corners[5])==1) index |=  32;
    if (IndicatorFunction(corners[6])==1) index |=  64;
    if (IndicatorFunction(corners[7])==1) index |= 128;
    return index;
}


int IndicatorFunction(Vector3D point)
{
    Vector3D center(0,0,0);
    double radius = 10;
     if(pow((point.x - center.x),2) + pow((point.y - center.y),2) + pow((point.z - center.z),2) <= (radius*radius)){
         return 1;
     }else{
         return 0;
     }
}
