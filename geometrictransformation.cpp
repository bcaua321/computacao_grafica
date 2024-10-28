#include "primitiveobject.h"
#include "geometrictransformation.h"
#include "points.h"
#include "./utils/matrix.h"
#include <cmath>
#include <vector>

GeometricTransformation::GeometricTransformation() {}

Matrix matrix;

double degreesToRadians(double degrees) {
    return degrees * (M_PI / 180.0);
}

void GeometricTransformation::Translation(vector<Points>& points, vector<int> values) {
    for(int i = 0; i < points.size(); i++) {
        points[i].set_x(points[i].get_firstPoint() + values[0]);
        points[i].set_y(points[i].get_secondPoint() + values[1]);
    }
}

void GeometricTransformation::Escalation(vector<Points>& points, vector<vector<double>> values) {
    auto pointCenter = matrix.pointCenter(points);
    auto escalationMatrix = matrix.setScaleMatrix(values);
    auto translationMatrix = matrix.setTranslationMatrix(pointCenter);
    auto translationMatrixNegative = matrix.setTranslationMatrix(matrix.negative(pointCenter));

    for(int i = 0; i < points.size(); i++) {
        auto point = matrix.pointToVector(points[i]);
        point = matrix.multiply(point, translationMatrixNegative); // Move para a origem
        point = matrix.multiply(point, escalationMatrix); // Aplica a escala
        point = matrix.multiply(point, translationMatrix); // Retorna à posição original

        points[i] = matrix.vectorToPoint(point);
    }
}

void GeometricTransformation::Rotation(vector<Points>& points, double tetah, int pointIndex) {
    vector<vector<double>> pointReference = matrix.pointToVector(points[pointIndex]);

    auto rotationMatrix = matrix.setRotationMatrix(degreesToRadians(tetah));
    auto translationMatrix = matrix.setTranslationMatrix(pointReference);
    auto translationMatrixNegative = matrix.setTranslationMatrix(matrix.negative(pointReference));

    for(int i = 0; i < points.size(); i++) {
        auto point = matrix.pointToVector(points[i]);
        point = matrix.multiply(point, translationMatrixNegative); // Move para a origem
        point = matrix.multiply(point, rotationMatrix); // Aplica a rotação
        point = matrix.multiply(point, translationMatrix); // Retorna à posição original

        points[i] = matrix.vectorToPoint(point);
    }
}
