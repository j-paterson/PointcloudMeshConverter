#ifndef CGL_BBOX_H
#define CGL_BBOX_H

#include <utility>
#include <algorithm>

#include "CGL/CGL.h"


//#include "ray.h"

using namespace CGL;
using namespace std;

//namespace CGL {

/**
 * Axis-aligned bounding box.
 * An AABB is given by two positions in space, the min and the max. An addition
 * component, the extent of the bounding box is stored as it is useful in a lot
 * of the operations on bounding boxes.
 */
 struct BBox {

   CGL::Vector3D max;	    ///< min corner of the bounding box
   CGL::Vector3D min;	    ///< max corner of the bounding box
   CGL::Vector3D extent;  ///< extent of the bounding box (min -> max) max - min

   /**
    * Constructor.
    * The default constructor creates a new bounding box which contains no
    * points.
    */
   BBox() {
       max = CGL::Vector3D(-10000000000.0, -1000000000.0, -10000000000.0);
       min = CGL::Vector3D(10000000000.0,  10000000000.0,  1000000000.0);
       extent = max - min;
   }

   /**
    * Constructor.
    * Creates a bounding box that includes a single point.
    */
     BBox(const CGL::Vector3D& p) : min(p), max(p) { extent = max - min; }

   /**
    * Constructor.
    * Creates a bounding box with given bounds.
    * \param min the min corner
    * \param max the max corner
    */
     BBox(const CGL::Vector3D& min, const CGL::Vector3D& max) :
        min(min), max(max) { extent = max - min; }

   /**
    * Constructor.
    * Creates a bounding box with given bounds (component wise).
    */
   BBox(const double minX, const double minY, const double minZ,
   const double maxX, const double maxY, const double maxZ) {
       min = CGL::Vector3D(minX, minY, minZ);
       max = CGL::Vector3D(maxX, maxY, maxZ);
       extent = max - min;
   }

   /**
    * Expand the bounding box to include another (union).
    * If the given bounding box is contained within *this*, nothing happens.
    * Otherwise *this* is expanded to the minimum volume that contains the
    * given input.
    * \param bbox the bounding box to be included
    */
   void expand(const BBox& bbox) {
     min.x = std::min(min.x, bbox.min.x);
     min.y = std::min(min.y, bbox.min.y);
     min.z = std::min(min.z, bbox.min.z);
     max.x = std::max(max.x, bbox.max.x);
     max.y = std::max(max.y, bbox.max.y);
     max.z = std::max(max.z, bbox.max.z);
     extent = max - min;
   }

   /**
    * Expand the bounding box to include a new point in space.
    * If the given point is already inside *this*, nothing happens.
    * Otherwise *this* is expanded to a minimum volume that contains the given
    * point.
    * \param p the point to be included
    */

   void expand(const CGL::Vector3D& p) {
     min.x = std::min(min.x, p.x);
     min.y = std::min(min.y, p.y);
     min.z = std::min(min.z, p.z);
     max.x = std::max(max.x, p.x);
     max.y = std::max(max.y, p.y);
     max.z = std::max(max.z, p.z);
     extent = max - min;
     printf("%f\n", min.x);
     printf("%f\n", p.x);
   }

   bool inside(CGL::Vector3D p) {
     bool inside = true;

     if (std::min(min.x, p.x) != min.x || std::min(min.y, p.y) != min.y || std::min(min.z, p.z) != min.z) {
       inside = false;
     }

     if (std::max(max.x, p.x) != max.x || std::max(max.y, p.y) != max.y || std::max(max.z, p.z) != max.z) {
       inside = false;
     }

     return inside;
   }

   CGL::Vector3D centroid() const {
     return (min + max) / 2;
   }

   //  BBox(const double minX, const double minY, const double minZ, const double maxX, const double maxY, const double maxZ) {
   std::vector<BBox> OctChildren() {
     //numbering system
     //when viewed from above 1 = NW, 2 = NE, 3 = SW, 4 = SE, then for below the same order follows 5 - 8
     std::vector<BBox> children;
     //BBox(const double minX, const double minY, const double minZ, const double maxX, const double maxY, const double maxZ)

    CGL::Vector3D centroid = (min + max) / 2;
    CGL::Vector3D maxHalfDist = centroid - max; //each component of this vector is the x,y,z halfdist
    CGL::Vector3D minHalfDist = centroid - min;


     BBox one(centroid.x, centroid.y, centroid.z, max.x, max.y, max.z);
     BBox two(centroid.x, centroid.y + maxHalfDist.y, centroid.z, max.x, max.y + maxHalfDist.y, max.z);
     BBox three(min.x, min.y, min.z + minHalfDist.z, centroid.x, centroid.y, centroid.z + minHalfDist.z);
     BBox four(centroid.x + maxHalfDist.x, centroid.y, centroid.z, max.x + maxHalfDist.x, max.y, max.z);

     BBox five(centroid.x, centroid.y, centroid.z + maxHalfDist.z, max.x, max.y, max.z + maxHalfDist.z);
     BBox six(min.x + minHalfDist.x, centroid.y + maxHalfDist.y, min.z, centroid.x + minHalfDist.x, centroid.y, centroid.z);
     BBox seven(min.x, min.y, min.z, centroid.x, centroid.y, centroid.z);
     BBox eight(min.x, min.y + minHalfDist.y, min.z, min.x + minHalfDist.x, min.y + 2.0 * minHalfDist.y, centroid.z);

     children.push_back(one);
     children.push_back(two);
     children.push_back(three);
     children.push_back(four);

     children.push_back(five);
     children.push_back(six);
     children.push_back(seven);
     children.push_back(eight);

     return children;
   }

   std::vector<CGL::Vector3D> getCorners() {
       std::vector<CGL::Vector3D> corners;
       //BBox(const double minX, const double minY, const double minZ, const double maxX, const double maxY, const double maxZ)

       CGL::Vector3D centroid = (min + max) / 2;
       CGL::Vector3D maxHalfDist = centroid - max; //each component of this vector is the x,y,z halfdist
       CGL::Vector3D minHalfDist = centroid - min;

       corners.push_back(CGL::Vector3D(max.x, max.y, max.z + 2.0 * maxHalfDist.z)); //0
       corners.push_back(CGL::Vector3D(min.x + 2.0 * minHalfDist.x, min.y, min.z)); //1
       corners.push_back(CGL::Vector3D(min.x, min.y, min.z)); //2
       corners.push_back(CGL::Vector3D(min.x, min.y + 2.0 * minHalfDist.y, min.z)); //3

       corners.push_back(CGL::Vector3D(max.x, max.y, max.z)); //4
       corners.push_back(CGL::Vector3D(max.x, max.y + 2.0 * maxHalfDist.y, max.z)); //5
       corners.push_back(CGL::Vector3D(min.x, min.y, min.z + 2.0 * minHalfDist.z)); //6
       corners.push_back(CGL::Vector3D(max.x + 2.0 * maxHalfDist.x, max.y, max.z)); //7

       return corners;
   }

   /**
    * Compute the surface area of the bounding box.
    * \return surface area of the bounding box.
    */
   double surface_area() const {
     if (empty()) return 0.0;
     return 2 * (extent.x * extent.z +
                 extent.x * extent.y +
                 extent.y * extent.z);
   }

   /**
    * Check if bounding box is empty.
    * Bounding box that has no size is considered empty. Note that since
    * bounding box are used for objects with positive volumes, a bounding
    * box of zero size (empty, or contains a single vertex) are considered
    * empty.
    */
   bool empty() const {
     return min.x > max.x || min.y > max.y || min.z > max.z;
   }

   /**
    * Ray - bbox intersection.
    * Intersects ray with bounding box, does not store shading information.
    * \param r the ray to intersect with
    * \param t0 lower bound of intersection time
    * \param t1 upper bound of intersection time
    */
   //bool intersect(const Ray& r, double& t0, double& t1) const;

   /**
    * Draw box wireframe with OpenGL.
    * \param c color of the wireframe
    */
   void draw(Color c) const;
 };

std::ostream& operator<<(std::ostream& os, const BBox& b);

 // namespace CGL

#endif // CGL_BBOX_H
