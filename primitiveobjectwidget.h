#ifndef PRIMITIVEOBJECTWIDGET_H
#define PRIMITIVEOBJECTWIDGET_H

#include <QObject>
#include <QWidget>
#include "primitiveobject.h"

class QPaintEvent;
class PrimitiveObjectWidget : public QWidget
{
    Q_OBJECT
public:
    PrimitiveObjectWidget(QWidget *parent, PrimitiveObject *primitiveObject);
    ~PrimitiveObjectWidget() {}

    virtual void paintEvent(QPaintEvent* event);
private:
    PrimitiveObject *primitiveObject;
};

#endif // PRIMITIVEOBJECTWIDGET_H
