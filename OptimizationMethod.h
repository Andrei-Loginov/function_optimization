#ifndef OPTIMIZATIONMETHOD_H
#include "SingletonGenerator.h"
#include "BoxArea.h"
#include "function.cpp"
#include "StopCriterion.h"
#define OPTIMIZATIONMETHOD_H

class OptimizationMethod
{
protected:
    OptimizationMethod();
    Function target_func_;
    BoxArea area_;
    friend class StopCriterion;
public:
    virtual void make_iter() = 0;

};

#endif // OPTIMIZATIONMETHOD_H
