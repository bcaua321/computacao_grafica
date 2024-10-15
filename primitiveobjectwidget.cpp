#include "primitiveobjectwidget.h"
#include <QtGui>
#include <vector>
#include "points.h"
#include "primitiveobject.h"
#include "factoryobject.h"

PrimitiveObjectWidget::PrimitiveObjectWidget(QWidget *parent, PrimitiveObject *primitiveObject) : QWidget(parent) {
    this->primitiveObject = primitiveObject;
}

void PrimitiveObjectWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    auto size = this->size();
    auto offset = 500;
    vector<Points> coordinates = this->primitiveObject->points;

    if(this->primitiveObject->type == Point) {
        painter.setBrush(Qt::black);
        painter.drawEllipse(coordinates[0].get_firstPoint(), coordinates[0].get_secondPoint(), 5, 5);
        return;
    }

    if(this->primitiveObject->type == Line) {
        painter.drawLine(coordinates[0].get_firstPoint(), coordinates[0].get_secondPoint(), size.width() - offset, size.height() - offset);
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

