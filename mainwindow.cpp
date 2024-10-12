#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtGui>

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
    auto offset = 4;


    painter.drawEllipse(0, 0, size.width() - offset, size.height() - offset);
}
