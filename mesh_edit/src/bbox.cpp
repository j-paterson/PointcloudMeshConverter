#include "bbox.h"
#include "GL/glew.h"
#include <algorithm>
#include <iostream>
#include "math.h"

//namespace CGL {

void BBox::draw(Color c) const {


  printf("Color 1\n", "hi");

  glColor4f(c.r, c.g, c.b, c.a);

  printf("Color 1.5\n", "hi");
  glBegin(GL_LINES);
  glVertex3d(max.x, max.y, max.z);
  printf("Color 1.7\n", "hi");
  glVertex3d(max.x, max.y, min.z);
  glEnd();

  /*
	// top
	glBegin(GL_LINE_STRIP);
  printf("Color 1.5\n", "hi");
	glVertex3d(max.x, max.y, max.z);
  printf("Color 1.7\n", "hi");
  glVertex3d(max.x, max.y, min.z);
  glVertex3d(min.x, max.y, min.z);
  glVertex3d(min.x, max.y, max.z);
  glVertex3d(max.x, max.y, max.z);
	glEnd();

  printf("Color 2\n", "hi");

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
  */

}

std::ostream& operator<<(std::ostream& os, const BBox& b) {
  return os << "BBOX(" << b.min << ", " << b.max << ")";
}

//} // namespace CGL
