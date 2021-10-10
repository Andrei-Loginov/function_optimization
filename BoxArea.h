#ifndef BOXAREA_H
#include <vector>
#include <cassert>
#define BOXAREA_H

struct dimension_limits{
    double lower = -1, upper = 1;
    dimension_limits() {}
    dimension_limits(double low, double up) : lower(low), upper(up) {}
    explicit dimension_limits(std::pair<double, double> lim) : lower(lim.first), upper(lim.second) {}
};

class BoxArea
{
    int ndim_ = 0;
    std::vector<dimension_limits> limits_;
public:
    BoxArea();
    BoxArea(int dim, const std::vector<dimension_limits>& lim);
    BoxArea(const BoxArea& other);
    BoxArea(BoxArea&& other);

    bool is_in(const std::vector<double>& point) const;
};

#endif // BOXAREA_H
