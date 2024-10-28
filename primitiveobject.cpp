#include "primitiveobject.h"

PrimitiveObject::PrimitiveObject(int id, string name, PrimitiveType type,  vector<Points> points) {
    this->id = id;
    this->name = name;
    this->type = type;
    this->points = points;
}
