#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDesktopWidget>
#include <string>
#include "./utils/matrix.h"
#include "./utils/window.h"
#include <QRect>
#include "customwidget.h"

GeometricTransformation transformation;
Window windowSCN(1200/2, 900/2, 1200, 900);
double angle = 0;

vector<PrimitiveObject*> MainWindow::primitiveObjects = {
    FactoryObject().create_polygon(),
    FactoryObject().create_retangle(),
    FactoryObject().House()
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
        hLayout->addWidget(widget);// Define o widget pai corretamente
    }

    layout->setLayout(hLayout);

    // Retorna o widget com os widgets filhos já gerenciados pelo layout
    return layout;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->frame_width = ui->frame->width();
    this->frame_heigth = ui->frame->height();

    renderComboBox(ui);
    renderComboBoxCoordinates(ui);
    // Use o caractere Unicode θ (U+03B8)
    QString unicodeChar = QString::fromUtf8("\u03B8");
    ui->label_angle->setText(unicodeChar);

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

    frameLayout->addWidget(new CustomWidget(MainWindow::primitiveObjects));
    // Configurar o QTimer para recalcular as coordenadas
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    this->frame_width = ui->frame->width();
    this->frame_heigth = ui->frame->height();

    for (int i = 0; i < MainWindow::primitiveObjects.size(); i++) {
        MainWindow::primitiveObjects[i]->pointsNorm = windowSCN.getNormCoordinates(
            MainWindow::primitiveObjects[i]->points,
            this->frame_width,
            this->frame_heigth
            );
    }

    ui->frame->update();
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
        primitive->pointsNorm = windowSCN.getNormCoordinates(primitive->points, this->frame_width, this->frame_heigth);

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


        transformation.Escalation(primitive->points, values);
        primitive->pointsNorm = windowSCN.getNormCoordinates(primitive->points, this->frame_width, this->frame_heigth);

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
        primitive->pointsNorm = windowSCN.getNormCoordinates(primitive->points, this->frame_width, this->frame_heigth);

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


void MainWindow::on_arrowUp_clicked()
{
    this->frame_width = ui->frame->width();
    this->frame_heigth = ui->frame->height();

    for (int i = 0; i < MainWindow::primitiveObjects.size(); i++) {
        windowSCN.translateWindow(WindowTransformationDirection::Up);

        primitiveObjects[i]->pointsNorm = windowSCN.normtoViewport(primitiveObjects[i]->points, this->frame_width, this->frame_heigth);
    }

    ui->frame->update();
}


void MainWindow::on_arrowDown_clicked()
{
    this->frame_width = ui->frame->width();
    this->frame_heigth = ui->frame->height();

    for (int i = 0; i < MainWindow::primitiveObjects.size(); i++) {
        windowSCN.translateWindow(WindowTransformationDirection::Down);

        primitiveObjects[i]->pointsNorm = windowSCN.normtoViewport(primitiveObjects[i]->points, this->frame_width, this->frame_heigth);
    }

    ui->frame->update();
}


void MainWindow::on_arrowLeft_clicked()
{
    this->frame_width = ui->frame->width();
    this->frame_heigth = ui->frame->height();

    for (int i = 0; i < MainWindow::primitiveObjects.size(); i++) {
        windowSCN.translateWindow(WindowTransformationDirection::Left);

        primitiveObjects[i]->pointsNorm = windowSCN.normtoViewport(primitiveObjects[i]->points, this->frame_width, this->frame_heigth);
    }

    ui->frame->update();
}


void MainWindow::on_arrowRight_clicked()
{
    this->frame_width = ui->frame->width();
    this->frame_heigth = ui->frame->height();

    for (int i = 0; i < MainWindow::primitiveObjects.size(); i++) {
        windowSCN.translateWindow(WindowTransformationDirection::Right);

        primitiveObjects[i]->pointsNorm = windowSCN.normtoViewport(primitiveObjects[i]->points, this->frame_width, this->frame_heigth);
    }

    ui->frame->update();
}

void MainWindow::on_arroRotateLeft_clicked()
{
    Matrix matrix;
    GeometricTransformation geometric;

    this->frame_width = ui->frame->width();
    this->frame_heigth = ui->frame->height();

    PrimitiveObject *primitive = selectedObject(ui);
    primitive->points = primitive->pointsOriginals;
    auto points = primitive->points;
    angle += 10;

    // Aplicar rotação no mundo

    geometric.RotationTest(windowSCN.points, angle);
    windowSCN.pointCenter = Matrix().pointCenter(windowSCN.points);
    windowSCN.recalculateValues(windowSCN.pointCenter[0][0], windowSCN.pointCenter[0][1]);

    // Rotacionar o vetor viewUp corretamente
    windowSCN.viewUp = matrix.rotateVector(windowSCN.viewUp[0], windowSCN.viewUp[1], angle);

    // Calcular o ângulo formado pelo viewUp com o eixo Y
    double normVup = sqrt(windowSCN.viewUp[0] * windowSCN.viewUp[0] + windowSCN.viewUp[1] * windowSCN.viewUp[1]);
    double cosTheta = windowSCN.viewUp[1] / normVup;
    windowSCN.angle = acos(cosTheta); // Ângulo em radianos

    if (windowSCN.viewUp[0] < 0) {
        windowSCN.angle = -windowSCN.angle;
    }

    if (primitive != nullptr) {

        windowSCN.pointCenter = Matrix().pointCenter(windowSCN.points);
        windowSCN.recalculateValues(windowSCN.pointCenter[0][0], windowSCN.pointCenter[0][1]);

        // Atualizar os pontos transformados
        for(int i = 0; i < points.size(); i++) {
            // Converter ponto para vetor
            auto point = Matrix().pointToVector(points[i]);

            // Aplicar matriz de normalização ajustada com o ângulo calculado
            point = Matrix().multiply(point,  windowSCN.getNormMatrix());

            // Aplicar transformação para a viewport
            auto res = windowSCN.transformNormToViewport(
                point[0][0], point[0][1],
                0, this->frame_width,
                0, this->frame_heigth
                );

            // Converter vetor de volta para ponto
            points[i] = Matrix().vectorToPoint(res);
        }



        // Aplicar rotação reversa para corrigir a orientação da janela
        windowSCN.viewUp = matrix.rotateVector(windowSCN.viewUp[0], windowSCN.viewUp[1], -angle);
        geometric.RotationTest(windowSCN.points, -angle);

        // Atualizar os pontos do objeto
        primitive->pointsNorm = points;
        ui->frame->update();
    } else {
        qDebug() << "Objeto primitivo não encontrado!";
    }
}


void MainWindow::on_arroRotateRight_clicked()
{
    Matrix matrix;
    GeometricTransformation geometric;

    this->frame_width = ui->frame->width();
    this->frame_heigth = ui->frame->height();

    PrimitiveObject *primitive = selectedObject(ui);
    primitive->points = primitive->pointsOriginals;
    auto points = primitive->points;
    angle -= 10;
    // Aplicar rotação no mundo

    geometric.RotationTest(windowSCN.points, angle);
    windowSCN.pointCenter = Matrix().pointCenter(windowSCN.points);
    windowSCN.recalculateValues(windowSCN.pointCenter[0][0], windowSCN.pointCenter[0][1]);

    // Rotacionar o vetor viewUp corretamente
    windowSCN.viewUp = matrix.rotateVector(windowSCN.viewUp[0], windowSCN.viewUp[1], angle);

    // Calcular o ângulo formado pelo viewUp com o eixo Y
    double normVup = sqrt(windowSCN.viewUp[0] * windowSCN.viewUp[0] + windowSCN.viewUp[1] * windowSCN.viewUp[1]);
    double cosTheta = windowSCN.viewUp[1] / normVup;
    windowSCN.angle = acos(cosTheta); // Ângulo em radianos

    if (windowSCN.viewUp[0] < 0) {
        windowSCN.angle = -windowSCN.angle;
    }


    // Aplicar rotação reversa para corrigir a orientação da janela
    windowSCN.viewUp = matrix.rotateVector(windowSCN.viewUp[0], windowSCN.viewUp[1], -angle);

    if (primitive != nullptr) {
        windowSCN.pointCenter = Matrix().pointCenter(windowSCN.points);
        windowSCN.recalculateValues(windowSCN.pointCenter[0][0], windowSCN.pointCenter[0][1]);

        // Atualizar os pontos transformados
        for(int i = 0; i < points.size(); i++) {
            // Converter ponto para vetor
            auto point = Matrix().pointToVector(points[i]);

            // Aplicar matriz de normalização ajustada com o ângulo calculado
            point = Matrix().multiply(point,  windowSCN.getNormMatrix());

            // Aplicar transformação para a viewport
            auto res = windowSCN.transformNormToViewport(
                point[0][0], point[0][1],
                0, this->frame_width,
                0, this->frame_heigth
                );

            // Converter vetor de volta para ponto
            points[i] = Matrix().vectorToPoint(res);
        }

        // Atualizar os pontos do objeto
        primitive->pointsNorm = points;
        ui->frame->update();
    } else {
        qDebug() << "Objeto primitivo não encontrado!";
    }
}

