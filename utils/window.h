#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include "matrix.h"
#include <cmath>
#include <algorithm>
#include "../factoryobject.h"
#include "../points.h"

using namespace std;

class Window
{
public:
    double xMin, xMax; // Limites horizontais
    double yMin, yMax; // Limites verticais
    vector<vector<double>> pointCenter;
    vector<Points> points;
    vector<double> viewUp; // Direção "para cima"
    vector<vector<double>> values;
    double width, height;

    // Construtor padrão
    Window(double centerX, double centerY, double widthSCR, double heightSCR, const vector<double>& initialViewUp = {0, 1})
        : viewUp(initialViewUp) {
        width = widthSCR;
        height = heightSCR;
        xMin = centerX - width/ 2.0;
        xMax = centerX + width / 2.0;
        yMin = centerY - height/ 2.0;;
        yMax = centerY + height / 2.0;
        values = {{2.0/((xMax - xMin)), 2.0/ ((yMax - yMin))}};
        points = {
            Points(xMin, yMin),
            Points(xMax, yMin),
            Points(xMax, yMax),
            Points(xMin, yMax)
        };
        pointCenter = Matrix().pointCenter(points);
    }

    void recalculateValues(double centerX, double centerY) {
        this->xMin = centerX - this->width/ 2.0;;
        this->xMax = centerX + this->width / 2.0;
        this->yMin = centerY - this->height/ 2.0;;
        this->yMax = centerY + this->height / 2.0;
        this->values = {{2.0/((this->xMax - this->xMin)), 2.0/ ((this->yMax - this->yMin))}};
    }

    vector<vector<double>> translateMatrix  = {{0, 0}};

    // Rotacionar o viewUp
    void rotateViewUp(double theta) {
        double cosTheta = std::cos(theta);
        double sinTheta = std::sin(theta);
        double u = viewUp[0];
        double v = viewUp[1];

        viewUp[0] = cosTheta * u - sinTheta * v;
        viewUp[1] = sinTheta * u + cosTheta * v;
    }

    // Rotacionar a própria window
    void rotateWindow(double theta) {
        double cosTheta = std::cos(theta);
        double sinTheta = std::sin(theta);

        std::vector<std::vector<double>> corners = {
            {xMin, yMin},
            {xMax, yMin},
            {xMax, yMax},
            {xMin, yMax}
        };

        double centerX = (xMin + xMax) / 2.0;
        double centerY = (yMin + yMax) / 2.0;

        for (auto& corner : corners) {
            double x = corner[0] - centerX;
            double y = corner[1] - centerY;

            double rotatedX = cosTheta * x - sinTheta * y;
            double rotatedY = sinTheta * x + cosTheta * y;

            corner[0] = rotatedX + centerX;
            corner[1] = rotatedY + centerY;
        }

        std::vector<double> xValues = {corners[0][0], corners[1][0], corners[2][0], corners[3][0]};
        std::vector<double> yValues = {corners[0][1], corners[1][1], corners[2][1], corners[3][1]};

        xMin = *std::min_element(xValues.begin(), xValues.end());
        xMax = *std::max_element(xValues.begin(), xValues.end());
        yMin = *std::min_element(yValues.begin(), yValues.end());
        yMax = *std::max_element(yValues.begin(), yValues.end());

        // Rotacionar o viewUp
        rotateViewUp(theta);
    }

    // Realinhar o viewUp para apontar para cima
    void alignViewUp() {
        // Calcular o ângulo entre o viewUp e o eixo Y
        double magnitude = std::sqrt(viewUp[0] * viewUp[0] + viewUp[1] * viewUp[1]);
        double angle = std::acos(viewUp[1] / magnitude);

        // Determinar o sentido da rotação usando o produto vetorial
        if (viewUp[0] < 0) {
            angle = -angle;
        }

        // Rotacionar a window para alinhar o viewUp ao eixo Y
        rotateWindow(-angle);
    }

    vector<vector<double>> getNormMatrix(double angle = 0) {
        Matrix matrix;

        auto escalationMatrix = matrix.setScaleMatrix(this->values);
        auto rotationMatrix = matrix.setRotationMatrix(angle);
        auto translationMatrixNegative = matrix.setTranslationMatrix(matrix.negative(this->pointCenter));

        auto res = matrix.multiply(translationMatrixNegative, rotationMatrix);
        res = matrix.multiply(res, escalationMatrix);

        return res;
    }

    vector<vector<double>> transformNormToViewport(double x_scn, double y_scn, double min_x, double max_x, double min_y, double max_y) {
        double x_view = ((x_scn + 1) / 2) * max_x;
        double y_view =  ((y_scn + 1) / 2) * max_y;

        return {{x_view, y_view}};
    }
};

#endif // WINDOW_H
