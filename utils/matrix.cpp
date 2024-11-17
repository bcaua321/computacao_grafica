#include "matrix.h"
#include "../points.h"
#include <QDebug>

using namespace std;

Matrix::Matrix() {}

// multiply two matrix's
vector<vector<double>> Matrix::multiply(vector<vector<double>> a, vector<vector<double>> b){
    vector<vector<double>> c(a.size(), vector<double>(b[0].size(), 0));

    for(int i = 0; i < a.size(); i++) {
        for(int j = 0; j < b[0].size(); j++) {
            for(int k = 0; k <  a[0].size(); k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return c;
}

// multiply all elements of a matrix for -1
vector<vector<double>> Matrix::negative(vector<vector<double>> a){
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a[0].size(); ++j) {
            a[i][j] = a[i][j] * -1;
        }
    }

    return a;
}

vector<double> Matrix::rotateVector(double x, double y, double theta) {
    // Cálculo da rotação
    double cosTheta = cos(theta * (M_PI / 180.0) );
    double sinTheta = sin(theta * (M_PI / 180.0));

    // Aplicando a matriz de rotação
    double xNew = cosTheta * x - sinTheta * y;
    double yNew = sinTheta * x + cosTheta * y;

    // Retorna o vetor rotacionado
    return {xNew, yNew};
}

// set a rotation matrix for the angle
vector<vector<double>> Matrix::setRotationMatrix(double tetah){
    vector<vector<double>> rotationMatrix = {
        {cos(tetah), -sin(tetah), 0},
        {sin(tetah), cos(tetah), 0},
        {0, 0, 1}
    };

    return rotationMatrix;
}

// set a scale matrix for points
vector<vector<double>> Matrix::setScaleMatrix(vector<vector<double>> values)  {
    vector<vector<double>> scaleMatrix = {
        {values[0][0], 0, 0},
        {0, values[0][1], 0},
        {0, 0, 1}
    };

    return scaleMatrix;
}

// receive points in a matrix and return translation matrix for this point
vector<vector<double>> Matrix::setTranslationMatrix(vector<vector<double>> values)   {
    vector<vector<double>>translationMatrix = {
        {1, 0, 0},
        {0, 1, 0},
        {values[0][0], values[0][1], 1}
    };

    return translationMatrix;
}

// get the center point of a figure
vector<vector<double>> Matrix::pointCenter(vector<Points> points) {
    double c_x = 0;
    double c_y = 0;

    for(int i = 0; i < points.size(); i++) {
        c_x += points[i].get_firstPoint();
        c_y += points[i].get_secondPoint();
    }

    vector<vector<double>> center = {
        {
            round(c_x / points.size()),
            round(c_y / points.size())
        }
    };

    return center;
}

vector<double> Matrix::pointCenterWindow(double xmin, double xmax, double ymin, double ymax) {
    double xcenter = (xmin + xmax) /2;
    double ycenter = (ymin + ymax) /2;

    return {xcenter, ycenter};
}

// receive points and convert to matrix
vector<vector<double>> Matrix::pointToVector(Points points) {
    vector<vector<double>> vec = {
        { points.get_firstPoint(), points.get_secondPoint(), 1}
    };

    return vec;
}


// receive matrix and convert to points
Points Matrix::vectorToPoint(vector<vector<double>> vec) {
    Points points(vec[0][0], vec[0][1]);

    return points;
}
