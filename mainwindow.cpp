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

    ui->frame->setLayout(layout);
    ui->frame->setMinimumHeight(600);
}

MainWindow::~MainWindow()
{
    delete ui;
}
