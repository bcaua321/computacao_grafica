#ifndef FACTORYOBJECT_H
#define FACTORYOBJECT_H

#include "primitiveobject.h"
#include <vector>
#include "points.h"

class FactoryObject {
public:
    FactoryObject();

    static vector<PrimitiveObject*> create_list();
    static PrimitiveObject* create_point();
    static PrimitiveObject* create_line(Points a, Points b);
    static PrimitiveObject* create_polygon();
    static PrimitiveObject* create_rectangle();
    static PrimitiveObject* House();
    static vector<Points> create_windowCoordinates(int xMin, int xMax, int yMin, int yMax);

private:
    static int current_id; // Contador de IDs
};

#endif // FACTORYOBJECT_H
