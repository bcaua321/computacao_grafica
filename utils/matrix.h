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

    vector<vector<int>> negative(vector<vector<int>> a);
    vector<vector<int>> negativeVec(vector<vector<int>> a);
    vector<vector<int>> multiply(vector<vector<int>> a, vector<vector<int>> b);
    vector<vector<int>> setRotationMatrix(double tetah);
    vector<vector<int>> setScaleMatrix(vector<vector<int>> values);
    vector<vector<int>> setTranslationMatrix(vector<vector<int>> values);
    vector<vector<int>> pointCenter(vector<Points> points);
    vector<vector<int>> pointToVector(Points points);
    Points vectorToPoint(vector<vector<int>> vec);
};

#endif // MATRIX_H
