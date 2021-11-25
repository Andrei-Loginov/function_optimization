#pragma once
#ifndef OPTIMIZATIONMETHOD_H
#define OPTIMIZATIONMETHOD_H
#include "SingletonGenerator.h"
#include "BoxArea.h"
#include "function.h"
#include "MethodStatus.h"
#include "StopCriterion.h"
#include <iostream>
#include <stdexcept>
#include <cmath>

#define eps 1e-5

struct Result{
    std::vector<double> x;
    double y;
    size_t niter;
    Result(std::vector<double> point, double value, size_t iterations) : x(point), y(value), niter(iterations){}
};

std::vector<double> operator+(const std::vector<double>& lhs, const std::vector<double>& rhs);
std::vector<double> operator*(const std::vector<double>& v, double a);
std::vector<double> operator*(double a, const std::vector<double>& v);
std::vector<double> operator/(const std::vector<double>&v, double a);

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

    virtual MethodStatus* get_status() = 0;
    virtual void make_iter() = 0;
    void search();

    double get_unif(double lower = 0, double upper = 1);

public:
    virtual Result optimize() = 0;
};

#endif // OPTIMIZATIONMETHOD_H
