#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include "matrix.h"
#include <cmath>
#include <algorithm>
#include "../factoryobject.h"
#include "../points.h"

using namespace std;

enum WindowTransformationDirection {
    Left,
    Right,
    Up,
    Down
};

class Window
{
public:
    double xMin, xMax;
    double yMin, yMax;
    vector<vector<double>> pointCenter;
    vector<Points> points;
    vector<double> viewUp;
    vector<vector<double>> values;
    double width, height;
    vector<vector<double>> translateMatrix  = {{0, 0}};
    double angle;

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

        angle = 0;

        pointCenter = Matrix().pointCenter(points);
    }

    void recalculateValues(double centerX, double centerY) {
        this->xMin = centerX - this->width/ 2.0;;
        this->xMax = centerX + this->width / 2.0;
        this->yMin = centerY - this->height/ 2.0;;
        this->yMax = centerY + this->height / 2.0;
        this->values = {{2.0/((this->xMax - this->xMin)), 2.0/ ((this->yMax - this->yMin))}};
    }

    vector<vector<double>> getNormMatrix(double angle = 0) {
        Matrix matrix;

        auto escalationMatrix = matrix.setScaleMatrix(this->values);
        auto rotationMatrix = matrix.setRotationMatrix(this->angle);
        auto translationMatrixNegative = matrix.setTranslationMatrix(matrix.negative(this->pointCenter));

        auto res = matrix.multiply(translationMatrixNegative, rotationMatrix);
        res = matrix.multiply(res, escalationMatrix);

        return res;
    }

    vector<Points> getNormCoordinates(vector<Points> points, double widthVP, double heightVP) {
        for(int i = 0; i < points.size(); i++) {
            // Converter ponto para vetor
            auto point = Matrix().pointToVector(points[i]);

            // Aplicar matriz de normalização ajustada com o ângulo calculado
            point = Matrix().multiply(point, this->getNormMatrix());

            // Aplicar transformação para a viewport
            auto res = this->transformNormToViewport(
                point[0][0], point[0][1],
                0, widthVP,
                0, heightVP
                );

            // Converter vetor de volta para ponto
            points[i] = Matrix().vectorToPoint(res);
        }


        return points;
    }

    vector<vector<double>> transformNormToViewport(double x_scn, double y_scn, double min_x, double max_x, double min_y, double max_y) {
        double x_view = ((x_scn + 1) / 2) * max_x;
        double y_view =  ((y_scn + 1) / 2) * max_y;

        return {{x_view, y_view}};
    }


    vector<Points> normtoViewport(vector<Points> points, double frameWidth, double frameHeight) {
        for(int i = 0; i < points.size(); i++) {
            auto point = Matrix().pointToVector(points[i]);

            point =  Matrix().multiply(point, this->getNormMatrix());

            auto res = this->transformNormToViewport(point[0][0], point[0][1], 0,  frameWidth, 0, frameHeight);

            points[i] = Matrix().vectorToPoint(res);
        }

        return points;
    }

    void translateWindow(WindowTransformationDirection direction) {
        Matrix matrix;

        vector<vector<double>> translationMatrix = {{0, 0}};

        if(direction == WindowTransformationDirection::Right) {
            translationMatrix = matrix.setTranslationMatrix({{10, 0}});
        }

        if(direction == WindowTransformationDirection::Left) {
            translationMatrix = matrix.setTranslationMatrix({{-10, 0}});
        }

        if(direction == WindowTransformationDirection::Up) {
            translationMatrix = matrix.setTranslationMatrix({{0, -10}});
        }

        if(direction == WindowTransformationDirection::Down) {
            translationMatrix = matrix.setTranslationMatrix({{0, 10}});
        }

        auto windowPoints = this->points;

        for(int i = 0; i < windowPoints.size(); i++) {
            auto point = matrix.pointToVector(windowPoints[i]);

            point = matrix.multiply(point, translationMatrix);

            this->points[i] = matrix.vectorToPoint(point);
        }


        this->pointCenter = matrix.pointCenter(this->points);
        this->recalculateValues(this->pointCenter[0][0], this->pointCenter[0][1]);
    }

};

#endif // WINDOW_H
