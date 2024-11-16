#ifndef GEOMETRICTRANSFORMATION_H
#define GEOMETRICTRANSFORMATION_H

#include <vector>
#include "points.h"
#include "primitiveobject.h"

using namespace std;

class GeometricTransformation
{
public:
    GeometricTransformation();
    void Translation(vector<Points>& points, vector<int> values);
    void Escalation(vector<Points>& points, vector<vector<double>> values);
    void Rotation(vector<Points>& points, double tetah, int pointIndex);
    void RotationTest(vector<Points>& points, double tetah);
};

#endif // GEOMETRICTRANSFORMATION_H
