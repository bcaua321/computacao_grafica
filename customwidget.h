#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QObject>
#include <QWidget>
#include "primitiveobject.h"
#include <QPainter>

using namespace std;

class CustomWidget : public QWidget {
    Q_OBJECT
public:
    explicit CustomWidget(vector<PrimitiveObject*> primitiveObjects, QWidget* parent = nullptr) : QWidget(parent) {
        this->primitiveObjects = primitiveObjects;
    }

private:
    vector<PrimitiveObject*> primitiveObjects;

protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);

        for (const auto& primitiveObject :  this->primitiveObjects) {
            vector<Points> coordinates = primitiveObject->pointsNorm;

            if(primitiveObject->type == Point) {
                painter.setBrush(Qt::black);
                painter.drawEllipse(coordinates[0].get_firstPoint(), coordinates[0].get_secondPoint(), 5, 5);
                continue;
            }

            if(primitiveObject->type == Line) {
                painter.drawLine(coordinates[0].get_firstPoint(), coordinates[0].get_secondPoint(), coordinates[1].get_firstPoint(), coordinates[1].get_secondPoint());
                continue;
            }

            if(primitiveObject->type == Rect) {
                painter.drawRect(10, 10, 1200, 900);
                continue;
            }

            if(primitiveObject->type == Polygon) {
                QPolygon polygon;

                for (int i = 0; i < coordinates.size(); i++) {
                    polygon << QPoint(coordinates[i].get_firstPoint(), coordinates[i].get_secondPoint());
                }

                painter.drawPolygon(polygon);
                continue;
            }
        }
    }
};


#endif // CUSTOMWIDGET_H
