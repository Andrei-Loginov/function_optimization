#ifndef NELDERMEAD_H
#define NELDERMEAD_H
#include "OptimizationMethod.h"

class NelderMead : public OptimizationMethod{
    double **curr_simplex, **prev_simplex;
public:
    NelderMead();
    NelderMead(Function* func, BoxArea* area, StopCriterion* crit);

    void swap(NelderMead& other) noexcept;
};

#endif // NELDERMEAD_H
