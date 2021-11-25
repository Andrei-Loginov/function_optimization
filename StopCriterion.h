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
    StopCriterion(const StopCriterion& other);
    StopCriterion(StopCriterion&& other) noexcept;
public:

    virtual bool criterion(MethodStatus*) = 0;
    bool operator()(MethodStatus*);
};

#endif
