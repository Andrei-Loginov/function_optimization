#ifndef NMSTATUS_H
#define NMSTATUS_H
#include<vector>
#include "MethodStatus.h"

class NMStatus : public MethodStatus
{
    const std::vector<double>* value;
    void swap(NMStatus& other) noexcept;
public:
    NMStatus();
    NMStatus(const NMStatus& other);
    NMStatus(NMStatus&& other);
    NMStatus(size_t niter, const std::vector<double>* values);
    NMStatus& operator=(NMStatus other);
    double get_value(size_t ind);
    size_t get_npoints() noexcept;
};

#endif // NMSTATUS_H
