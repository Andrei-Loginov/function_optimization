#pragma once
#ifndef OPTIMIZATIONMETHOD_H
#define OPTIMIZATIONMETHOD_H
#include "SingletonGenerator.h"
#include "BoxArea.h"
#include "function.h"
#include "StopCriterion.h"
#include <iostream>
#include <array>

struct Result{
    std::vector<double> x;
    double y;
    size_t niter;
    Result(std::vector<double> point, double value, size_t iterations) : x(point), y(value), niter(iterations){}
};

class OptimizationMethod
{
protected:
    OptimizationMethod();
    OptimizationMethod(const OptimizationMethod& other);
    OptimizationMethod(OptimizationMethod&& other);
    OptimizationMethod(Function* func, BoxArea* area, StopCriterion* crit);


    void swap(OptimizationMethod& other);
    Function *target_func_ = nullptr;
    BoxArea *area_ = nullptr;
    StopCriterion *stop_crit_ = nullptr;
    size_t ndim_;
    size_t niter_ = 0;
    std::vector<std::vector<double>> x_trajectory_;

    virtual void make_iter() = 0;
    void search();


    double get_unif(double lower = 0, double upper = 1);
    friend class StopCriterion;
public:
    virtual Result optimize() = 0;
};

#endif // OPTIMIZATIONMETHOD_H
