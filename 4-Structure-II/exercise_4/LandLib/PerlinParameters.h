/*
COPYRIGHT 2020 - ENTER. ALL RIGHTS RESERVED.
*/

#pragma once

#include "Point3D.h"

namespace LandLib
{
struct PerlinParameters
{
    Point3D point;
    
    int octaves; 
    double persistence; 
    double frequency;
};
}