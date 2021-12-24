#ifndef STOHRANDITERSTOP_H
#define STOHRANDITERSTOP_H

#include "StopCriterion.h"

class StohRandIterStop : public StopCriterion
{
protected:
    size_t max_iter_after_improvment = 10000;
public:
    StohRandIterStop();
    StohRandIterStop(size_t max_iter, size_t max_after_improve = 10000);
    StohRandIterStop(StohRandIterStop&& other);
    StohRandIterStop(const StohRandIterStop& other);

    bool criterion(MethodStatus* status);
};

#endif // STOHRANDITERSTOP_H
