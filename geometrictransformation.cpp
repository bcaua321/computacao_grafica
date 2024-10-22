#include "geometrictransformation.h"
#include <cmath>
#include <vector>

const double teta = std::acos(-1) / 10;

GeometricTransformation::GeometricTransformation() {}


void GeometricTransformation::Translation(vector<Points> coordinates, int size) {
    coordinates[0].set_x(coordinates[0].get_firstPoint() + size);
    coordinates[0].set_x(coordinates[0].get_secondPoint() + size);
}

// GeometricTransformation::Translation(vector<Points> coordinates){
//     int x = coordinates[0].get_firstPoint();
//     int y = coordinates[0].get_secondPoint();

//     int arr[3][3] = {
//         { cos(pi), -sin(pi),  x*(1 - cos(pi)) + y * sin(pi)},
//         { sin(pi), cos(pi),  y*(1 - cos(pi)) + x * sin(pi)},
//         { 0, 0, 1}
//     };
// }
