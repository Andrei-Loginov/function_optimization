#ifndef STOPCRITERION_H
#include <vector>
#include <string>
#define STOPCRITERION_H

class OptimizationMethod;

class StopCriterion
{
protected:
    const std::string name;
public:
    StopCriterion();
    virtual bool criterion(OptimizationMethod*) = 0;
};

#endif
