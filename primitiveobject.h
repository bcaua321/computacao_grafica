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
    PrimitiveObject(int id, string name, PrimitiveType type, vector<Points> points);
    int id;
    string name;
    PrimitiveType type;
    vector<Points> points;
};

#endif // PRIMITIVEOBJECT_H
