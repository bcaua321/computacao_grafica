#ifndef FACTORYOBJECT_H
#define FACTORYOBJECT_H

#include "primitiveobject.h"
#include <vector>
#include "points.h"

class FactoryObject
{
public:
    FactoryObject();
    vector<PrimitiveObject*> create_list();
    PrimitiveObject* create_point();
    PrimitiveObject* create_line();
    PrimitiveObject* create_polygon();
    PrimitiveObject* House();
    PrimitiveObject* create_retangle();
    vector<Points> create_windowCoordiantes(int xMin, int xMax, int yMin, int yMax);
};

#endif // FACTORYOBJECT_H
