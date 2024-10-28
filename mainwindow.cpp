#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDesktopWidget>
#include <string>
#include "./utils/matrix.h"

GeometricTransformation transformation;

vector<PrimitiveObject*> MainWindow::primitiveObjects = {
    FactoryObject().create_polygon()
};

vector<PrimitiveObjectWidget*>  MainWindow::displayFile;

string coordenadasParaString(Points point) {
    return "(" + to_string(point.get_firstPoint()) + ", " + to_string(point.get_secondPoint()) + ")";
}

PrimitiveObject* selectedObject(Ui::MainWindow* ui){
    QString selected = ui->comboBox->currentText();
    PrimitiveObject *primitive = NULL;

    // search for selected primitiveObject
    for (const auto& primitiveObject :  MainWindow::primitiveObjects) {
        if(primitiveObject->name == selected.toStdString()) {
            primitive = primitiveObject;
        }
    }

    return primitive;
}

int indexOfPoint(Ui::MainWindow* ui){
    QVariant selected = ui->comboBox_2->currentData();

    return selected.toInt();
}

void renderComboBox(Ui::MainWindow* ui) {
    int i = 0;

    // Get name from list of defined primitiveObjects, then add to combox
    for (const auto& primitiveObject : MainWindow::primitiveObjects) {
        ui->comboBox->addItem(QString::fromStdString(primitiveObject->name), QVariant(i));
        i++;
    }
}

void renderComboBoxCoordinates(Ui::MainWindow* ui) {
    int i = 0;
    auto selected = selectedObject(ui);
    Matrix matrix;
    if (!selected) {
        // Trata o caso de selected ser nullptr
        return;
    }

    auto pointCenter = matrix.pointCenter(selected->points);

    for (const auto& point : selected->points) {
        ui->comboBox_2->addItem(QString::fromStdString(coordenadasParaString(point)), QVariant(i));
        i++;
    }

    ui->comboBox_2->addItem(QString::fromStdString(coordenadasParaString(matrix.vectorToPoint(pointCenter))), QVariant(i));
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
    renderComboBoxCoordinates(ui);
    // Use o caractere Unicode θ (U+03B8)
    QString unicodeChar = QString::fromUtf8("\u03B8");
    ui->label_angle->setText(unicodeChar);

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

    PrimitiveObject *primitive = selectedObject(ui);

    if (primitive != nullptr) {
        vector<int> values = {
            x.toInt(),
            y.toInt()
        };

        transformation.Translation(primitive->points, values);

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

    PrimitiveObject *primitive = selectedObject(ui);;


    if (primitive != nullptr) {
        vector<vector<double>> values = {
            {
            x.toDouble(),
            y.toDouble()}
        };

        transformation.Escalation(primitive->points, values);

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
    QString tetah = ui->lineEdit_x_2->text();
    PrimitiveObject *primitive = selectedObject(ui);

    if (primitive != nullptr) {
        transformation.Rotation(primitive->points, tetah.toDouble(), indexOfPoint(ui));

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

