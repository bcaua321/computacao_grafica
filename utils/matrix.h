#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <cmath>
#include "../points.h"

using namespace std;

class Matrix
{
public:
    Matrix();

    vector<vector<double>> negative(vector<vector<double>> a);
    vector<vector<double>> multiply(vector<vector<double>> a, vector<vector<double>> b);
    vector<vector<double>> setRotationMatrix(double tetah);
    vector<vector<double>> setScaleMatrix(vector<vector<double>> values);
    vector<vector<double>> setTranslationMatrix(vector<vector<double>> values);
    vector<vector<double>> pointCenter(vector<Points> points);
    vector<double> pointCenterWindow(double xmin, double xmax, double ymin, double ymax);
    vector<vector<double>> pointToVector(Points points);
    vector<double> rotateVector(double x, double y, double theta);
    // Retorna a matriz de rotação para um dado ângulo (em radianos)
     vector<vector<double>> rotationMatrix(double theta) {
        return {
            {cos(theta), -sin(theta)},
            {sin(theta), cos(theta)}
        };
    }

    // Aplica a matriz de rotação a um ponto (x, y)
    vector<double> rotatePoint(vector<double> point, vector<vector<double>> rotationMatrix) {
        double x = point[0];
        double y = point[1];

        double xNew = rotationMatrix[0][0] * x + rotationMatrix[0][1] * y;
        double yNew = rotationMatrix[1][0] * x + rotationMatrix[1][1] * y;

        return {xNew, yNew};
    }

    Points vectorToPoint(vector<vector<double>> vec);
};

#endif // MATRIX_H
