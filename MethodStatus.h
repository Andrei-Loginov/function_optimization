#ifndef METHODSTATUS_H
#include <stddef.h>
#include <stdexcept>
#define METHODSTATUS_H


class MethodStatus{
public:
    MethodStatus();
    MethodStatus(const MethodStatus& other);
    MethodStatus(MethodStatus&& other) noexcept;
    void swap(MethodStatus& other) noexcept;
    MethodStatus& operator=(MethodStatus other);
    size_t get_n_iter() const;
protected:
    size_t n_iter_;

};

#endif // METHODSTATUS_H
