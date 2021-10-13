#include "NelderMead.h"

NelderMead::NelderMead()
{

}

NelderMead::NelderMead(Function* func, BoxArea* area, StopCriterion* crit) : OptimizationMethod(func, area, crit) {
    curr_simplex = new double*[area_->dim() + 1];
    for (size_t i = 0; i < area_->dim() + 1; ++i)
        curr_simplex[i] = new double[area_->dim()];
}

void NelderMead::swap(NelderMead &other) noexcept {
    OptimizationMethod::swap(other);

}
