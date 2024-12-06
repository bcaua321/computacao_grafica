#include "factoryobject.h"

// Inicializa o contador estático
int FactoryObject::current_id = 1;

FactoryObject::FactoryObject() {}

vector<PrimitiveObject*> FactoryObject::create_list() {
    PrimitiveObject* point = create_point();
    PrimitiveObject* polygon = create_polygon();

    vector<PrimitiveObject*> list_objects = {
        point,
        polygon
    };

    return list_objects;
}

PrimitiveObject* FactoryObject::create_point() {
    vector<Points> points = {
        Points(25, 25),
    };

    PrimitiveObject* point = new PrimitiveObject(current_id++, "Point", Point, points);

    return point;
}

PrimitiveObject* FactoryObject::create_line(Points a, Points b) {
    vector<Points> points = {
        a,
        b
    };

    PrimitiveObject* line = new PrimitiveObject(current_id++, "Line", Line, points);

    return line;
}

PrimitiveObject* FactoryObject::create_polygon() {
    vector<Points> points = {
        Points(150, 50),
        Points(50, 150),
        Points(150, 150)
    };

    PrimitiveObject* triangle = new PrimitiveObject(current_id++, "Triangle", Polygon, points);
    return triangle;
}

PrimitiveObject* FactoryObject::create_rectangle() {
    vector<Points> points = {
        Points(10, 10),
        Points(100, 50)
    };

    PrimitiveObject* rectangle = new PrimitiveObject(current_id++, "Rectangle", Rect, points);
    return rectangle;
}

PrimitiveObject* FactoryObject::House() {
    vector<Points> housePoints = {
                                  // Base da casa
                                  Points(50, 150), Points(150, 150),
                                  Points(150, 50), Points(50, 50),
                                  Points(50, 150),

                                  // Telhado
                                  Points(50, 50), Points(100, 10),
                                  Points(150, 50),

                                  // Porta
                                  Points(90, 150), Points(90, 110),
                                  Points(110, 110), Points(110, 150),
                                  Points(90, 150),

                                  // Janela (esquerda)
                                  Points(60, 90), Points(80, 90),
                                  Points(80, 70), Points(60, 70),
                                  Points(60, 90),

                                  // Janela (direita)
                                  Points(120, 90), Points(140, 90),
                                  Points(140, 70), Points(120, 70),
                                  Points(120, 90)
    };

    PrimitiveObject* house = new PrimitiveObject(current_id++, "House", Polygon, housePoints);

    return house;
}

vector<Points> FactoryObject::create_windowCoordinates(int xMin, int xMax, int yMin, int yMax) {
    vector<Points> points = {
        Points(xMin, yMin),
        Points(xMax, yMin),
        Points(xMax, yMax),
        Points(xMin, yMax)
    };

    return points;
}
