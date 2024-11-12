#ifndef WINDOWVIEWPORT_H
#define WINDOWVIEWPORT_H

#include <vector>
#include "../points.h"

using namespace std;

class WindowViewport
{
public:
    WindowViewport();
    vector<Points> duplicateCoordinates(vector<Points> points);
    vector<Points> getNewCoordinates(vector<Points> points);
    vector<Points> transformToScn(vector<Points> points, float min_x, float max_x, float min_y, float max_y);
    vector<Points> transformToViewport(vector<Points> points, float min_x, float max_x, float min_y, float max_y);
};

#endif // WINDOWVIEWPORT_H
