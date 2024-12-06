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
    Points vectorToPoint(vector<vector<double>> vec);
};

#endif // MATRIX_H
