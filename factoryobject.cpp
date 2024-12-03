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

PrimitiveObject* FactoryObject::create_retangle() {
    vector<Points> points = {
        Points(10, 10),
        Points(100, 50)
    };

    PrimitiveObject *retangle = new PrimitiveObject(4, "Retangle", Rect, points);
    return retangle;
}

PrimitiveObject* FactoryObject::House() {
    vector<Points> housePoints = {
        // Base da casa
        Points(50, 50), Points(150, 50),
        Points(150, 150), Points(50, 150),
        Points(50, 50),

        // Telhado
        Points(50, 150), Points(100, 200),
        Points(150, 150),

        // Porta
        Points(90, 50), Points(90, 100),
        Points(110, 100), Points(110, 50),
        Points(90, 50),

        // Janela
        Points(60, 110), Points(80, 110),
        Points(80, 130), Points(60, 130),
        Points(60, 110)
    };

    PrimitiveObject *house = new PrimitiveObject(5, "House", Polygon, housePoints);

    return house;
}


vector<Points> FactoryObject::create_windowCoordiantes(int xMin, int xMax, int yMin, int yMax) {
    vector<Points> points = {
        Points(xMin, yMin),
        Points(xMax, yMin),
        Points(xMax, yMax),
        Points(xMin, yMax)
    };


    return points;
}

