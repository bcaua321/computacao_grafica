#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDesktopWidget>
#include <string>
#include "./utils/matrix.h"
#include "./utils/window.h"
#include <QRect>

GeometricTransformation transformation;
Window windowSCN(1200, 1000, 1200/2, 1000/2);
double angle = 0;

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
    ui->comboBox_2->clear();

    for (const auto& point : selected->points) {
        ui->comboBox_2->addItem(QString::fromStdString(coordenadasParaString(point)), QVariant(i));
        i++;
    }
}

QWidget* MainWindow::renderWidgets() {
    // Cria o widget pai que conterá os widgets filhos
    QWidget *layout = new QWidget(this);

    QHBoxLayout* hLayout = new QHBoxLayout(layout);

    // A seguir, adiciona os widgets filhos ao layout
    for (const auto& widget : MainWindow::displayFile) {
        hLayout->addWidget(widget); // Define o widget pai corretamente
    }

    // Retorna o widget com os widgets filhos já gerenciados pelo layout
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
    this->frame_width = ui->frame->width();
    this->frame_heigth = ui->frame->height();

    // push loaded primitiveObjets and convert to primitiveObjectWidget
    for (const auto& primitiveObject :  MainWindow::primitiveObjects) {
        PrimitiveObjectWidget *widget = new PrimitiveObjectWidget(parent, primitiveObject);
        displayFile.push_back(widget);
    }

    // Cria um layout para o centralWidget se ainda não tiver um
    QHBoxLayout *mainLayout = new QHBoxLayout(ui->centralwidget);
    ui->centralwidget->setLayout(mainLayout);

    // Define o frame ou qualquer outro widget para ser expansível
    ui->frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Adiciona o frame ao layout do centralWidget para que ele redimensione
    mainLayout->addWidget(ui->frame);
    mainLayout->addWidget(ui->frame_3);

    // Define um layout para os widgets internos do frame, caso necessário
    QHBoxLayout *frameLayout = new QHBoxLayout(ui->frame);
    frameLayout->setContentsMargins(0, 0, 0, 0);  // Remove as margens para ocupar todo o espaço
    frameLayout->setSpacing(0);

    ui->frame->setLayout(frameLayout);

    // Adiciona widgets ou containers dentro do frame
    QWidget *container = renderWidgets();

    frameLayout->addWidget(container);
    this->frame_width = ui->frame->width();
    this->frame_heigth = ui->frame->height();
    // Configurar o QTimer para recalcular as coordenadas
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
        double x_double = x.toDouble();
        double y_double = y.toDouble();

        if(x_double == 0) {
            x_double = 1;
        }

        if(y_double == 0) {
            y_double = 1;
        }

        vector<vector<double>> values = {
            {
            x_double,
            y_double }
        };


        transformation.Escalation(primitive->pointsOriginals, values);

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
        primitive->pointsOriginals = primitive->points;

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


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    renderComboBoxCoordinates(ui);
}


void MainWindow::on_pushButton_clicked()
{
}

void MainWindow::on_arrowUp_clicked()
{
    this->frame_width = ui->frame->width();
    this->frame_heigth = ui->frame->height();

    PrimitiveObject *primitive = selectedObject(ui);
    primitive->points = primitive->pointsOriginals;
    auto points = primitive->points;

    if (primitive != nullptr) {
        windowSCN.translateMatrix[0][1] += 10;
        auto x = windowSCN.translateMatrix[0][0];
        auto y =  windowSCN.translateMatrix[0][1];

        auto translationUpMatrix = Matrix().setTranslationMatrix({{0, 10}});
        auto windowPoints = windowSCN.points;
        for(int i = 0; i < windowPoints.size(); i++) {
            auto point = Matrix().pointToVector(windowPoints[i]);

            point = Matrix().multiply(point, translationUpMatrix);

            windowSCN.points[i] = Matrix().vectorToPoint(point);
        }

        windowSCN.pointCenter = Matrix().pointCenter(windowSCN.points);
        windowSCN.recalculateValues(windowSCN.pointCenter[0][0], windowSCN.pointCenter[0][1]);

        for(int i = 0; i < points.size(); i++) {
            auto point = Matrix().pointToVector(points[i]);

            point =  Matrix().multiply(point, windowSCN.getNormMatrix());

            auto res = windowSCN.transformNormToViewport(point[0][0], point[0][1], 0,  this->frame_width, 0, this->frame_heigth);

            points[i] = Matrix().vectorToPoint(res);
        }

        primitive->points = points;
        ui->frame->update();
    } else {
        qDebug() << "Objeto primitivo não encontrado!";
    }
}


void MainWindow::on_arrowDown_clicked()
{
    this->frame_width = ui->frame->width();
    this->frame_heigth = ui->frame->height();

    PrimitiveObject *primitive = selectedObject(ui);
    primitive->points = primitive->pointsOriginals;
    auto points = primitive->points;

    if (primitive != nullptr) {
        auto translationUpMatrix = Matrix().setTranslationMatrix({{0, -10}});
        auto windowPoints = windowSCN.points;

        for(int i = 0; i < windowPoints.size(); i++) {
            auto point = Matrix().pointToVector(windowPoints[i]);

            point = Matrix().multiply(point, translationUpMatrix);

            windowSCN.points[i] = Matrix().vectorToPoint(point);
        }


        windowSCN.pointCenter = Matrix().pointCenter(windowSCN.points);
        windowSCN.recalculateValues(windowSCN.pointCenter[0][0], windowSCN.pointCenter[0][1]);


        for(int i = 0; i < points.size(); i++) {
            auto point = Matrix().pointToVector(points[i]);

            point =  Matrix().multiply(point, windowSCN.getNormMatrix());

            auto res = windowSCN.transformNormToViewport(point[0][0], point[0][1], 0,  this->frame_width, 0, this->frame_heigth);

            points[i] = Matrix().vectorToPoint(res);
        }

        primitive->points = points;
        ui->frame->update();
    } else {
        qDebug() << "Objeto primitivo não encontrado!";
    }
}


void MainWindow::on_arrowLeft_clicked()
{
    this->frame_width = ui->frame->width();
    this->frame_heigth = ui->frame->height();

    PrimitiveObject *primitive = selectedObject(ui);
    primitive->points = primitive->pointsOriginals;
    auto points = primitive->points;

    if (primitive != nullptr) {
        auto translationUpMatrix = Matrix().setTranslationMatrix({{10, 0}});
        auto windowPoints = windowSCN.points;
        for(int i = 0; i < windowPoints.size(); i++) {
            auto point = Matrix().pointToVector(windowPoints[i]);

            point = Matrix().multiply(point, translationUpMatrix);

            windowSCN.points[i] = Matrix().vectorToPoint(point);
        }

        windowSCN.pointCenter = Matrix().pointCenter(windowSCN.points);
        windowSCN.recalculateValues(windowSCN.pointCenter[0][0], windowSCN.pointCenter[0][1]);

        for(int i = 0; i < points.size(); i++) {
            auto point = Matrix().pointToVector(points[i]);

            point =  Matrix().multiply(point, windowSCN.getNormMatrix());

            auto res = windowSCN.transformNormToViewport(point[0][0], point[0][1], 0,  this->frame_width, 0, this->frame_heigth);

            points[i] = Matrix().vectorToPoint(res);
        }

        primitive->points = points;
        ui->frame->update();
    } else {
        qDebug() << "Objeto primitivo não encontrado!";
    }
}


void MainWindow::on_arrowRight_clicked()
{
    this->frame_width = ui->frame->width();
    this->frame_heigth = ui->frame->height();

    PrimitiveObject *primitive = selectedObject(ui);
    primitive->points = primitive->pointsOriginals;
    auto points = primitive->points;

    if (primitive != nullptr) {
        windowSCN.translateMatrix[0][0] -= 10;

        auto translationUpMatrix = Matrix().setTranslationMatrix({{-10, 0}});
        auto windowPoints = windowSCN.points;

        for(int i = 0; i < windowPoints.size(); i++) {
            auto point = Matrix().pointToVector(windowPoints[i]);

            point = Matrix().multiply(point, translationUpMatrix);

            windowSCN.points[i] = Matrix().vectorToPoint(point);
        }

        windowSCN.pointCenter = Matrix().pointCenter(windowSCN.points);
        windowSCN.recalculateValues(windowSCN.pointCenter[0][0], windowSCN.pointCenter[0][1]);

        for(int i = 0; i < points.size(); i++) {
            auto point = Matrix().pointToVector(points[i]);

            point =  Matrix().multiply(point, windowSCN.getNormMatrix());

            auto res = windowSCN.transformNormToViewport(point[0][0], point[0][1], 0,  this->frame_width, 0, this->frame_heigth);

            points[i] = Matrix().vectorToPoint(res);
        }

        primitive->points = points;
        ui->frame->update();
    } else {
        qDebug() << "Objeto primitivo não encontrado!";
    }
}


void MainWindow::on_arroRotateLeft_clicked()
{
    Matrix matrix;
    GeometricTransformation geometric;

    this->frame_width = ui->frame->width();
    this->frame_heigth = ui->frame->height();

    PrimitiveObject *primitive = selectedObject(ui);
    auto points = primitive->points;

    geometric.RotationTest(windowSCN.points, 10);
    auto view = matrix.rotateVector(windowSCN.viewUp[0], windowSCN.viewUp[1], 0);

    if (primitive != nullptr) {

        for(int i = 0; i < points.size(); i++) {
             // Converter ponto para vetor
             auto point = Matrix().pointToVector(points[i]);

             // Aplicar matriz de normalização
             point = Matrix().multiply(point,  windowSCN.getNormMatrix());

             // Aplicar transformação para a viewport
             auto res = windowSCN.transformNormToViewport(
                 point[0][0], point[0][1],
                 400, this->frame_width,
                 400, this->frame_heigth
                 );

             // Converter vetor de volta para ponto
             points[i] = Matrix().vectorToPoint(res);
        }

        primitive->points = points;
        ui->frame->update();
    } else {
        qDebug() << "Objeto primitivo não encontrado!";
    }
}


void MainWindow::on_arroRotateRight_clicked()
{
    Matrix matrix;
    this->frame_width = ui->frame->width();
    this->frame_heigth = ui->frame->height();

    PrimitiveObject *primitive = selectedObject(ui);
    primitive->points = primitive->pointsOriginals;

    auto points = primitive->points;

    if (primitive != nullptr) {

        auto view = matrix.rotateVector(windowSCN.viewUp[0], windowSCN.viewUp[1], 0);

        for(int i = 0; i < points.size(); i++) {
            auto point = Matrix().pointToVector(points[i]);

            point =  Matrix().multiply(point, windowSCN.getNormMatrix());

            auto res = windowSCN.transformNormToViewport(point[0][0], point[0][1], 0,  this->frame_width, 0, this->frame_heigth);

            points[i] = Matrix().vectorToPoint(res);
        }

        primitive->points = points;
        ui->frame->update();
    } else {
        qDebug() << "Objeto primitivo não encontrado!";
    }
}

