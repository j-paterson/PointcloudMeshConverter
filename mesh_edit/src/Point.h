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
#include <vector>

union Neighbor
{
    float distance;
    float hashKey;
};

class Point {
public:
    Point();
    Point(CGL::Vector3D coordinates);
    Point(CGL::Vector3D coordinates, CGL::Vector3D normal);
    CGL::Vector3D coordinates;
    CGL::Vector3D vField;
    CGL::Vector3D normal;
    std::vector<Neighbor> neighbors;
};

#endif
