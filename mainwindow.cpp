#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtGui>
#include "primitiveobjectwidget.h"
#include "factoryobject.h"
#include <QHBoxLayout>
#include <QSizePolicy>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *container = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(container);

    PrimitiveObject *ponto = FactoryObject().create_point();
    PrimitiveObject *linha = FactoryObject().create_line();
    PrimitiveObject *triangulo = FactoryObject().create_polygon();

    PrimitiveObjectWidget *widget_point = new PrimitiveObjectWidget(parent, ponto);
    PrimitiveObjectWidget *widget_linha = new PrimitiveObjectWidget(parent, linha);
    PrimitiveObjectWidget *widget_triangulo = new PrimitiveObjectWidget(parent, triangulo);

    layout->addWidget(widget_point);
    layout->addWidget(widget_linha);
    layout->addWidget(widget_triangulo);

    widget_point->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    widget_linha->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    widget_triangulo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    container->setLayout(layout);

    // Definindo o container como o widget central da janela
    setCentralWidget(container);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// void MainWindow::paintEvent(QPaintEvent* event) {
//     QPainter painter(this);

//     auto size = this->size();
//     auto offset = 500;

//     vector<PrimitiveObject> list = FactoryObject().create_list();

//     auto point = list[0];
//     auto line = list[1];
//     auto triangle = list[2];

//     QPolygon polygon;
//     polygon << QPoint(triangle.points[0].get_firstPoint(), triangle.points[0].get_secondPoint())
//             << QPoint(triangle.points[1].get_firstPoint(), triangle.points[1].get_secondPoint())
//             << QPoint(triangle.points[2].get_firstPoint(), triangle.points[2].get_secondPoint());

//     painter.drawPoint(point.points[0].get_firstPoint(), point.points[0].get_secondPoint());
//     painter.drawLine(line.points[0].get_firstPoint(), line.points[0].get_secondPoint(), size.width() - offset, size.height() - offset);
//     painter.drawPolygon(polygon);
// }


