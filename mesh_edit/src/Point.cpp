//
//  Point.cpp
//  facemeshTest
//
//  Created by Bryce Schmidtchen on 4/29/17.
//  Copyright (c) 2017 Bryce Schmidtchen. All rights reserved.
//

#include "Point.h"

Point::Point(CGL::Vector3D coordinates) {
    this->coordinates = coordinates;
}

Point::Point(CGL::Vector3D coordinates, CGL::Vector3D normal) {
  this->coordinates = coordinates;
  this->normal = normal;
}

Point::Point() {
  this->coordinates = CGL::Vector3D();
  this->normal = CGL::Vector3D();
}
