#ifndef FUNCTION_H
#include <vector>
#define FUNCTION_H


class Function
{
    int ndim = 0;
    double (*function)(std::vector<double>) = nullptr;
    void swap(Function& other) noexcept;

public:
    Function();
    Function(int dim, double (*func)(std::vector<double>));
    Function(const Function& other);
    Function(Function&& other) noexcept;

    Function& operator=(Function other);
    double operator()(const std::vector<double>& args) const;

    double eval(const std::vector<double>& args) const;

    void set_func(int new_dim, double (*new_func)(std::vector<double>));

    int dim() const;
};

#endif // FUNCTION_H
