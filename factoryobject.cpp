#include "factoryobject.h"

FactoryObject::FactoryObject() {

}

vector<PrimitiveObject*> FactoryObject::create_list() {
    PrimitiveObject *line = this->create_line();
    PrimitiveObject *point = this->create_point();
    PrimitiveObject *polygon = this->create_polygon();

    vector<PrimitiveObject*> list_objects = {
        point,
        line,
        polygon
    };

    return list_objects;
}

PrimitiveObject* FactoryObject::create_point() {
    vector<Points> points = {
        Points(25, 25),
    };

    PrimitiveObject *point = new PrimitiveObject(1, "Point", Point, points);

    return point;
}


PrimitiveObject* FactoryObject::create_line() {
    vector<Points> points = {
        Points(50, 50),
        Points(50, 100)
    };

    PrimitiveObject *line = new PrimitiveObject(2, "Reta", Line, points);

    return line;
}

PrimitiveObject* FactoryObject::create_polygon() {
    vector<Points> points = {
        Points(150, 50),
        Points(50, 150),
        Points(150, 150)
    };

    PrimitiveObject *triangle = new PrimitiveObject(3, "Triangulo", Polygon, points);

    return triangle;
}

