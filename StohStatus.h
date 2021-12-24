#ifndef STOHSTATUS_H
#define STOHSTATUS_H

#include "MethodStatus.h"

class StohStatus : public MethodStatus
{
protected:
    size_t niter_after_improve_;
    void swap(StohStatus& other) noexcept;
public:
    StohStatus(size_t niter, size_t iter_after_improve);
    StohStatus(StohStatus&& other);
    StohStatus(const StohStatus& other);
    StohStatus& operator=(StohStatus other) noexcept;
    size_t get_niter_after_improve() const;
};

#endif // STOHSTATUS_H
