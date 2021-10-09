#ifndef BOXAREA_H
#define BOXAREA_H


class BoxArea
{
    double upper = 1, lower = -1, left = -1, right = 1;
public:
    BoxArea();
    BoxArea(double up, double low, double lft, double rght);
    BoxArea(const BoxArea& other);
    BoxArea(BoxArea&& other);

    bool is_in(double x, double y) const;
};

#endif // BOXAREA_H
