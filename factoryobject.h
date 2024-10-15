#ifndef FACTORYOBJECT_H
#define FACTORYOBJECT_H

#include "primitiveobject.h"
#include <vector>

class FactoryObject
{
public:
    FactoryObject();
    vector<PrimitiveObject*> create_list();
    PrimitiveObject* create_point();
    PrimitiveObject* create_line();
    PrimitiveObject* create_polygon();
};

#endif // FACTORYOBJECT_H
