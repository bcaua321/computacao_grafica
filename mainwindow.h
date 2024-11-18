#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QHBoxLayout>
#include <vector>
#include <algorithm>
#include <QtGui>
#include "primitiveobjectwidget.h"
#include "factoryobject.h"
#include "geometrictransformation.h"
#include <QResizeEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

//class QPaintEvent;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QWidget* renderWidgets();

    static vector<PrimitiveObject*> primitiveObjects;
    static vector<PrimitiveObjectWidget*> displayFile;

private slots:
    void on_transformationButton_clicked();

    void on_escalationButton_clicked();

    void on_rotationButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_arrowUp_clicked();

    void on_arrowDown_clicked();

    void on_arrowLeft_clicked();

    void on_arrowRight_clicked();

    void on_arroRotateLeft_clicked();

    void on_arroRotateRight_clicked();

private:
    Ui::MainWindow *ui;
    int frame_width, frame_heigth;
};


#endif // MAINWINDOW_H
