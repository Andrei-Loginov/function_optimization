#ifndef STOHASTICOPTIMIZATION_H
#define STOHASTICOPTIMIZATION_H

#include "OptimizationMethod.h"
#include "StohIterStop.h"

class StohasticOptimization : public OptimizationMethod
{
protected:
    double p_;
    double delta_;
    double curr_y_;
    std::vector<double> first_point_;
    void make_iter();
    size_t niter_after_improvment_ = 0;
public:
    StohasticOptimization(Function* func, BoxArea* area, StopCriterion* crit, double p = 0.5, double delta = 0.5,
                          const std::vector<double>& first_point = std::vector<double>());

    bool set_first_point(const std::vector<double>& point);
    Result optimize();
    MethodStatus* get_status() const;

};

#endif // STOHASTICOPTIMIZATION_H
