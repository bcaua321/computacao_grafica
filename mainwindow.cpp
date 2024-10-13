#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtGui>
#include "points.h"
#include "primitiveobject.h"
#include "factoryobject.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    auto size = this->size();
    auto offset = 500;

    vector<PrimitiveObject> list = FactoryObject().create_list();

    auto point = list[0];
    auto line = list[1];
    auto triangle = list[2];

    QPolygon polygon;
    polygon << QPoint(triangle.points[0].get_firstPoint(), triangle.points[0].get_secondPoint())
            << QPoint(triangle.points[1].get_firstPoint(), triangle.points[1].get_secondPoint())
            << QPoint(triangle.points[2].get_firstPoint(), triangle.points[2].get_secondPoint());

    painter.drawPoint(point.points[0].get_firstPoint(), point.points[0].get_secondPoint());
    painter.drawLine(line.points[0].get_firstPoint(), line.points[0].get_secondPoint(), size.width() - offset, size.height() - offset);
    painter.drawPolygon(polygon);
}


