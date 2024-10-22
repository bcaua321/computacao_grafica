#include "points.h"

Points::Points(int point_one, int point_two) {
    this->point_one = point_one;
    this->point_two = point_two;
}

int Points::get_firstPoint() {
    return this->point_one;
}

int Points::get_secondPoint() {
    return this->point_two;
}

void Points::set_x(int newX) {
    this->point_one = newX;
}


void Points::set_y(int newY) {
    this->point_one = newY;
}
