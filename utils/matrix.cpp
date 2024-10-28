#include "matrix.h"
#include "../points.h"

using namespace std;

Matrix::Matrix() {}

vector<vector<int>> Matrix::multiply(vector<vector<int>> a, vector<vector<int>> b){
    vector<vector<int>> c(a.size(), vector<int>(b[0].size(), 0));

    for(int i = 0; i < a.size(); i++) {
        for(int j = 0; j < b[0].size(); j++) {
            for(int k = 0; k <  a[0].size(); k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return c;
}

vector<vector<int>> Matrix::negative(vector<vector<int>> a){
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a[0].size(); ++j) {
            a[i][j] = a[i][j] * -1;
        }
    }

    return a;
}

vector<vector<int>> Matrix::negativeVec(vector<vector<int>> a){
    for (int i = 0; i < a.size(); i++) {
        for(int j = 0 ;j < a[0].size(); j++) {
            a[i][j] = a[i][j] * -1;
        }
    }

    return a;
}


vector<vector<int>> Matrix::setRotationMatrix(double tetah){
    vector<vector<int>> rotationMatrix = {
        {floor(cos(tetah)), -floor(sin(tetah)), 0},
        {floor(sin(tetah)), floor(cos(tetah)), 0},
        {0, 0, 1}
    };

    return rotationMatrix;
}

vector<vector<int>> Matrix::setScaleMatrix(vector<vector<int>> values)  {
    vector<vector<int>> scaleMatrix = {
        {values[0][0], 0, 0},
        {0, values[0][1], 0},
        {0, 0, 1}
    };

    return scaleMatrix;
}

vector<vector<int>> Matrix::setTranslationMatrix(vector<vector<int>> values)   {
    vector<vector<int>> translationMatrix = {
        {1, 0, 0},
        {0, 1, 0},
        {values[0][0], values[0][1], 1}
    };

    return translationMatrix;
}


vector<vector<int>> Matrix::pointToVector(Points points) {
    vector<vector<int>> vec = {
        { points.get_firstPoint(), points.get_secondPoint(), 1}
    };

    return vec;
}

vector<vector<int>> Matrix::pointCenter(vector<Points> points) {
    int c_x = 0;
    int c_y = 0;

    for(int i = 0; i < points.size(); i++) {
        c_x += points[i].get_firstPoint();
        c_y += points[i].get_secondPoint();
    }

    vector<vector<int>>center = {
        {
            round(c_x / points.size()),
             round(c_y / points.size())
        }
    };

    return center;
}


Points Matrix::vectorToPoint(vector<vector<int>> vec) {
    Points points(vec[0][0], vec[0][1]);

    return points;
}
