#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDesktopWidget>

GeometricTransformation transformation();

vector<PrimitiveObject*> MainWindow::primitiveObjects = {
    FactoryObject().create_polygon()
};

vector<PrimitiveObjectWidget*>  MainWindow::displayFile;

void renderComboBox(Ui::MainWindow* ui) {
    int i = 0;

    // Get name from list of defined primitiveObjects
    for (const auto& primitiveObject : MainWindow::primitiveObjects) {
        ui->comboBox->addItem(QString::fromStdString(primitiveObject->name), QVariant(i));
        i++;
    }
}

QHBoxLayout* MainWindow::renderWidgets() {
    QWidget *container = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(container);

    // Get widget from display file
    for (const auto& widget :  MainWindow::displayFile) {
        layout->addWidget(widget);
    }

    return layout;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    renderComboBox(ui);

    // push loaded primitiveObjets and convert to primitiveObjectWidget
    for (const auto& primitiveObject :  MainWindow::primitiveObjects) {
        PrimitiveObjectWidget *widget = new PrimitiveObjectWidget(parent, primitiveObject);
        displayFile.push_back(widget);
    }

    QHBoxLayout *layout = renderWidgets();

    ui->frame->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_transformationButton_clicked()
{
    QString x = ui->lineEdit_x->text();
    QString y = ui->lineEdit_y->text();

    QString selected = ui->comboBox->currentText();
    PrimitiveObject *primitive = NULL;

    // search for selected primitiveObject
    for (const auto& primitiveObjectWidget :  MainWindow::displayFile) {
        auto tempPrimitiveObject = primitiveObjectWidget->getCurrentPrimitive();
        if(tempPrimitiveObject->name == selected.toStdString()) {
            primitive = tempPrimitiveObject;
        }
    }

    if (primitive != nullptr) {
        vector<int> values = {
            x.toInt(),
            y.toInt()
        };

        GeometricTransformation().Translation(primitive->points, values);

        // update the coordinates
        for (int i = 0; i < MainWindow::primitiveObjects.size(); i++) {
            if(primitiveObjects[i]->id == primitive->id) {
                primitiveObjects[i] = primitive;
            }
        }

        ui->frame->update();  // Atualiza apenas o frame especificado
    } else {
        qDebug() << "Objeto primitivo não encontrado!";
    }
}

void MainWindow::on_escalationButton_clicked()
{
    QString x = ui->lineEdit_x_4->text();
    QString y = ui->lineEdit_y_2->text();

    QString selected = ui->comboBox->currentText();
    PrimitiveObject *primitive = NULL;

    // search for selected primitiveObject
    for (const auto& primitiveObjectWidget :  MainWindow::displayFile) {
        auto tempPrimitiveObject = primitiveObjectWidget->getCurrentPrimitive();
        if(tempPrimitiveObject->name == selected.toStdString()) {
            primitive = tempPrimitiveObject;
        }
    }

    if (primitive != nullptr) {
        vector<vector<int>> values = {
            {
            x.toInt(),
             y.toInt()}
        };

        GeometricTransformation().Escalation(primitive->points, values);

        // update the coordinates
        for (int i = 0; i < MainWindow::primitiveObjects.size(); i++) {
            if(primitiveObjects[i]->id == primitive->id) {
                primitiveObjects[i] = primitive;
            }
        }

        ui->frame->update();  // Atualiza apenas o frame especificado
    } else {
        qDebug() << "Objeto primitivo não encontrado!";
    }
}


void MainWindow::on_rotationButton_clicked()
{
    QString x = ui->lineEdit_x_2->text();

    QString selected = ui->comboBox->currentText();
    PrimitiveObject *primitive = NULL;

    // search for selected primitiveObject
    for (const auto& primitiveObjectWidget :  MainWindow::displayFile) {
        auto tempPrimitiveObject = primitiveObjectWidget->getCurrentPrimitive();
        if(tempPrimitiveObject->name == selected.toStdString()) {
            primitive = tempPrimitiveObject;
        }
    }

    if (primitive != nullptr) {
        GeometricTransformation().Rotation(primitive->points, x.toDouble());

        // update the coordinates
        for (int i = 0; i < MainWindow::primitiveObjects.size(); i++) {
            if(primitiveObjects[i]->id == primitive->id) {
                primitiveObjects[i] = primitive;
            }
        }

        ui->frame->update();  // repaint primitiveObjectWidget
    } else {
        qDebug() << "Objeto primitivo não encontrado!";
    }
}

