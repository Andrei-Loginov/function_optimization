#ifndef NELDERMEAD_H
#define NELDERMEAD_H
#include "OptimizationMethod.h"

class NelderMead : public OptimizationMethod{
    std::vector<std::vector<double>> curr_simplex_, prev_iter_simplex_, start_simplex_;

    void init_simplex();
    void make_iter();
public:
    NelderMead();
    NelderMead(Function* func, BoxArea* area, StopCriterion* crit,
               const std::vector<std::vector<double>>& start_simplex = std::vector<std::vector<double>>());

    void swap(NelderMead& other) noexcept;

    Result optimize();
};

#endif // NELDERMEAD_H
