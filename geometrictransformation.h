#ifndef GEOMETRICTRANSFORMATION_H
#define GEOMETRICTRANSFORMATION_H

#include <vector>
#include "points.h"

using namespace std;

class GeometricTransformation
{
public:
    GeometricTransformation();
    void Translation(vector<Points> coordinates, int size);
};

#endif // GEOMETRICTRANSFORMATION_H
