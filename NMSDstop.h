#ifndef NMSDSTOP_H
#define NMSDSTOP_H
#include "NMStatus.h"
#include "StopCriterion.h"
#include <cmath>

class NMSDstop : public StopCriterion
{
    double val_mean(NMStatus* status) noexcept;
    double val_sd(NMStatus*status) noexcept;
    double epsilon = 1e-8;
    void swap(NMSDstop& other) noexcept;
public:
    NMSDstop();
    NMSDstop(size_t niter);
    NMSDstop(const NMSDstop& other);
    NMSDstop(NMSDstop&& other);
    NMSDstop& operator=(NMSDstop other) noexcept;
    bool criterion(MethodStatus* status);
};

#endif // NMSDSTOP_H
