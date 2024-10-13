#ifndef POINTS_H
#define POINTS_H

class Points
{
public:
    Points(int point_one, int point_two);
    int get_firstPoint();
    int get_secondPoint();
private:
    int point_one;
    int point_two;
};

#endif // POINTS_H
