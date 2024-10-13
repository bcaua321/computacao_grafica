#ifndef PRIMITIVEOBJECT_H
#define PRIMITIVEOBJECT_H

#include <string>
#include <vector>
#include "points.h"

using namespace std;

enum PrimitiveType {
    Point,
    Line,
    Polygon
};

class PrimitiveObject
{
public:
    PrimitiveObject(string name, PrimitiveType type, vector<Points> points);
    string name;
    PrimitiveType type;
    vector<Points> points;
};

#endif // PRIMITIVEOBJECT_H
