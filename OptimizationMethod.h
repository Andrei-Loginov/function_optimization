#pragma once
#ifndef OPTIMIZATIONMETHOD_H
#define OPTIMIZATIONMETHOD_H
#include "SingletonGenerator.h"
#include "BoxArea.h"
#include "function.h"
#include "StopCriterion.h"

class OptimizationMethod
{
protected:
    OptimizationMethod();
    OptimizationMethod(const OptimizationMethod& other);
    OptimizationMethod(OptimizationMethod&& other);
    OptimizationMethod(Function* func, BoxArea* area, StopCriterion* crit);

    OptimizationMethod& operator=(OptimizationMethod& other);

    void swap(OptimizationMethod& other);
    Function *target_func_ = nullptr;
    BoxArea *area_ = nullptr;
    StopCriterion *stop_crit_ = nullptr;
    friend class StopCriterion;
public:
    virtual void make_iter() = 0;

};

#endif // OPTIMIZATIONMETHOD_H
