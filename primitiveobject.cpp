#include "primitiveobject.h"

PrimitiveObject::PrimitiveObject(string name, PrimitiveType type,  vector<Points> points) {
    this->name = name;
    this->type = type;
    this->points = points;
}
