#ifndef POINTS_H
#define POINTS_H

class Points
{
public:
    Points();
    Points(double point_one, double point_two);
    double get_firstPoint();
    double get_secondPoint();
    void set_x(double newX);
    void set_y(double newY);
private:
    double point_one;
    double point_two;
};

#endif // POINTS_H
