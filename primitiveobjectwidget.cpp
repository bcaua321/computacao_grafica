#include "primitiveobjectwidget.h"
#include <QtGui>
#include <vector>
#include "points.h"
#include "primitiveobject.h"
#include "factoryobject.h"

PrimitiveObjectWidget::PrimitiveObjectWidget(QWidget *parent, PrimitiveObject *primitiveObject) : QWidget(parent) {
    this->primitiveObject = primitiveObject;
}

PrimitiveObject* PrimitiveObjectWidget::getCurrentPrimitive() {
    return this->primitiveObject;
}

void PrimitiveObjectWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    vector<Points> coordinates = this->primitiveObject->points;

    if(this->primitiveObject->type == Point) {
        painter.setBrush(Qt::black);
        painter.drawEllipse(coordinates[0].get_firstPoint(), coordinates[0].get_secondPoint(), 5, 5);
        return;
    }

    if(this->primitiveObject->type == Line) {
        painter.drawLine(coordinates[0].get_firstPoint(), coordinates[0].get_secondPoint(), coordinates[1].get_firstPoint(), coordinates[1].get_secondPoint());
        return;
    }

    if(this->primitiveObject->type == Polygon) {
        QPolygon polygon;
        polygon << QPoint(coordinates[0].get_firstPoint(), coordinates[0].get_secondPoint())
                << QPoint(coordinates[1].get_firstPoint(), coordinates[1].get_secondPoint())
                << QPoint(coordinates[2].get_firstPoint(), coordinates[2].get_secondPoint());

        painter.drawPolygon(polygon);
        return;
    }
}
