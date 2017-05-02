//
//  Point.h
//  facemeshTest
//
//  Created by Bryce Schmidtchen on 4/29/17.
//  Copyright (c) 2017 Bryce Schmidtchen. All rights reserved.
//

#ifndef __facemeshTest__Point__
#define __facemeshTest__Point__

#include <stdio.h>
#include "../CGL/include/CGL/vector3D.h"
#include "octree.h"

class Point {
public:
    Point(CGL::Vector3D p);
    CGL::Vector3D coordinates;
    std::vector<tuple<float, OctreeNode>> neighbors;
};

#endif
