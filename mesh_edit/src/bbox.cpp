#include "bbox.h"

#include "GL/glew.h"

#include <algorithm>
#include <iostream>
#include "math.h"

namespace CGL {

bool BBox::intersect(const Ray& r, double& t0, double& t1) const {

  // Part 2, Task 2:
  // Implement ray - bounding box intersection test
  // If the ray intersected the bouding box within the range given by
  // t0, t1, update t0 and t1 with the new intersection times.
  /*
  Vector3D max;	    ///< min corner of the bounding box
  Vector3D min;	    ///< max corner of the bounding box
  Vector3D extent;
  */
  double t0x_new = ((this->min[0] - r.o[0]) / r.d[0]);
  double t1x_new = ((this->max[0] - r.o[0]) / r.d[0]);

  double t0y_new = ((this->min[1] - r.o[1]) / r.d[1]);
  double t1y_new = ((this->max[1] - r.o[1]) / r.d[1]);

  double t0z_new = ((this->min[2] - r.o[2]) / r.d[2]);
  double t1z_new = ((this->max[2] - r.o[2]) / r.d[2]);

  if(t0x_new > t1x_new){ //T0 should represent the nearer plane / intersection
    double temp = t1x_new;
    t1x_new = t0x_new;
    t0x_new = temp;
  }

  if(t0y_new > t1y_new){ //T0 should represent the nearer plane / intersection
    double temp = t1y_new;
    t1y_new = t0y_new;
    t0y_new = temp;
  }

  if(t0z_new > t1z_new){ //T0 should represent the nearer plane / intersection
    double temp = t1z_new;
    t1z_new = t0z_new;
    t0z_new = temp;
  }

  double t_min = std::max(t0x_new , std::max(t0y_new, t0z_new)); //
  double t_max = std::min(t1x_new , std::min(t1y_new, t1z_new));


  if(t_max >= t_min){ //if the values found are between the bound, set new values, if this is true, then the new values
    t0 = t_min; //should we be checking this? maybe t0 and t1 have no values in them
    t1 = t_max;

    //printf("%s\n", "TRUE");
    return true;
  }

  return false;


}

void BBox::draw(Color c) const {

  glColor4f(c.r, c.g, c.b, c.a);

	// top
	glBegin(GL_LINE_STRIP);
	glVertex3d(max.x, max.y, max.z);
  glVertex3d(max.x, max.y, min.z);
  glVertex3d(min.x, max.y, min.z);
  glVertex3d(min.x, max.y, max.z);
  glVertex3d(max.x, max.y, max.z);
	glEnd();

	// bottom
	glBegin(GL_LINE_STRIP);
  glVertex3d(min.x, min.y, min.z);
  glVertex3d(min.x, min.y, max.z);
  glVertex3d(max.x, min.y, max.z);
  glVertex3d(max.x, min.y, min.z);
  glVertex3d(min.x, min.y, min.z);
	glEnd();

	// side
	glBegin(GL_LINES);
	glVertex3d(max.x, max.y, max.z);
  glVertex3d(max.x, min.y, max.z);
	glVertex3d(max.x, max.y, min.z);
  glVertex3d(max.x, min.y, min.z);
	glVertex3d(min.x, max.y, min.z);
  glVertex3d(min.x, min.y, min.z);
	glVertex3d(min.x, max.y, max.z);
  glVertex3d(min.x, min.y, max.z);
	glEnd();

}

std::ostream& operator<<(std::ostream& os, const BBox& b) {
  return os << "BBOX(" << b.min << ", " << b.max << ")";
}

} // namespace CGL
