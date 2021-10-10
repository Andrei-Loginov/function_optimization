#include "BoxArea.h"

BoxArea::BoxArea(){
}

BoxArea::BoxArea(int ndim, const std::vector<dimension_limits>& lim) : ndim_(ndim), limits_(lim){
    assert(limits_.size() == size_t(ndim));
}

BoxArea::BoxArea(const BoxArea& other) : ndim_(other.ndim_), limits_(other.limits_){
}

BoxArea::BoxArea(BoxArea&& other) : ndim_(other.ndim_), limits_(other.limits_) {
    other.ndim_ = 0;
    other.limits_.resize(0);
}

bool BoxArea::is_in(const std::vector<double>& point) const{
    if (point.size() != limits_.size()) return false;
    for (size_t i = 0; i < point.size(); ++i)
        if (point[i] < limits_[i].lower || point[i] > limits_[i].upper) return false;
    return true;
}
