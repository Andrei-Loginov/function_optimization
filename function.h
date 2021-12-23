#pragma once
#ifndef FUNCTION_H
#include <vector>
#define FUNCTION_H

#define debug

class Function
{
    int ndim = 0;
    double (*function)(std::vector<double>) = nullptr;

public:
    Function();
    Function(int dim, double (*func)(std::vector<double>));
    Function(const Function& other);
    Function(Function&& other) noexcept;

    void swap(Function& other) noexcept;
    Function& operator=(Function other);
    double operator()(const std::vector<double>& args) const;

    double eval(const std::vector<double>& args) const;

    void set_func(int new_dim, double (*new_func)(std::vector<double>));
    size_t dim() const;
};

#endif // FUNCTION_H
