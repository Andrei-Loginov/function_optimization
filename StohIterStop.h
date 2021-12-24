#ifndef STOHITERSTOP_H
#define STOHITERSTOP_H

#include "StopCriterion.h"
#include "StohStatus.h"

class StohIterStop : public StopCriterion
{
protected:
    size_t max_iter_after_improvment = 10000;
public:
    StohIterStop();
    StohIterStop(size_t max_iter, size_t max_after_improve = 10000);
    StohIterStop(StohIterStop&& other);
    StohIterStop(const StohIterStop& other);
    void swap(StohIterStop& other) noexcept;
    StohIterStop& operator=(StohIterStop other) noexcept;

    bool criterion(MethodStatus* status);
};

#endif // STOHITERSTOP_H
