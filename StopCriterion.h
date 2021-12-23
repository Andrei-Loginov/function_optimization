#pragma once
#ifndef STOPCRITERION_H
#include <vector>
#include <string>
#include "MethodStatus.h"
#define STOPCRITERION_H

class OptimizationMethod;

class StopCriterion
{
protected:
    std::string name;
    void swap(StopCriterion& other) noexcept;
    StopCriterion();
    StopCriterion(size_t max_n_iter);
    StopCriterion(const StopCriterion& other);
    StopCriterion(StopCriterion&& other) noexcept;
    size_t max_iter = 100;
public:
    virtual bool criterion(MethodStatus*) = 0;
    bool operator()(MethodStatus*);
};

#endif
