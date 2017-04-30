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
#include "vector3D.h"

class Point {
public:
    Point(Vector3D p);
    Vector3D coordinates;
};

#endif
