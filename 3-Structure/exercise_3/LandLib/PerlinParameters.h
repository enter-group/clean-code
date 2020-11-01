/*
COPYRIGHT 2020 - ENTER. ALL RIGHTS RESERVED.
*/

#ifndef PERLIN_PARAMETERS_H_
#define PERLIN_PARAMETERS_H_

#include "Point3D.h"

struct PerlinParameters
{
    Point3D point;
    
    int octaves; 
    double persistence; 
    double frequency;
};

#endif // PERLIN_PARAMETERS_H_