#pragma once
#ifndef STOPCRITERION_H
#include <vector>
#include <string>
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

    virtual bool criterion(OptimizationMethod*) = 0;
    bool operator()(OptimizationMethod*);
};

#endif
