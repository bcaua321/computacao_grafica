#include "windowviewport.h"

WindowViewport::WindowViewport() {}

vector<Points> WindowViewport::duplicateCoordinates(vector<Points> points) {
    for (auto& point : points) {
        float x = point.get_firstPoint();
        float y = point.get_secondPoint();

        point.set_x(x * 2);
        point.set_y(y * 2);
    }

    return points;
}

vector<Points> WindowViewport::getNewCoordinates(vector<Points> points) {
    auto pointsDuplicates = this->duplicateCoordinates(points);
    auto pointsScn = this->transformToScn(pointsDuplicates, 0, 250, 0, 250);
    auto pointsView = this->transformToViewport(pointsScn, 0, 1000, 0, 700);

    return pointsView;
}

vector<Points> WindowViewport::transformToScn(vector<Points> points, float min_x, float max_x, float min_y, float max_y) {
    for (auto& point : points) {
        float x = point.get_firstPoint();
        float y = point.get_secondPoint();

        float x_scn = 2 * (x - min_x) / (max_x - min_x) - 1;
        float y_scn = 2 * (y - min_y) / (max_y - min_y) - 1;

        point.set_x(x_scn);
        point.set_y(y_scn * -1);
    }

    return points;
}

vector<Points> WindowViewport::transformToViewport(vector<Points> points, float min_x, float max_x, float min_y, float max_y) {
    for (auto& point : points) {
        float x_scn = point.get_firstPoint();
        float y_scn = point.get_secondPoint();

        float x_view = ((x_scn + 1) / 2) * (max_x - min_x) + min_x;
        float y_view = ((1 - y_scn) / 2) * (max_y - min_y) + min_y;

        point.set_x(x_view);
        point.set_y(y_view);
    }

    return points;
}
