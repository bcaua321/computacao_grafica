#include "points.h"

Points::Points(double point_one, double point_two) {
    this->point_one = point_one;
    this->point_two = point_two;
}

double Points::get_firstPoint() {
    return this->point_one;
}

double Points::get_secondPoint() {
    return this->point_two;
}

void Points::set_x(double newX) {
    this->point_one = newX;
}

void Points::set_y(double newY) {
    this->point_two = newY;
}
