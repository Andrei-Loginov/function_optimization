#ifndef NELDERMEAD_H
#define NELDERMEAD_H
#include "OptimizationMethod.h"
#include "NMStatus.h"

class NelderMead : public OptimizationMethod{
protected:
    std::vector<std::vector<double>> simplex_;
    std::vector<double> simplex_fun_value_;
    std::vector<double> curr_point_;
    size_t index_h, index_l, index_g;
    void init_simplex();
    void evaluate_fun_simplex();
    void make_iter();
    void find_indices();
    MethodStatus* get_status() const;
    std::vector<double> update_trajectory();
    double alpha_ = 1, beta_ = 0.5, gamma_ = 2;

public:
    NelderMead();
    NelderMead(Function* func, BoxArea* area, StopCriterion* crit,
               double alpha = 1, double beta = 0.5, double gamma = 2,
               const std::vector<std::vector<double>>& simplex = std::vector<std::vector<double>>());
    NelderMead(NelderMead&& other);
    NelderMead(const NelderMead& other);
    void swap(NelderMead& other) noexcept;
    NelderMead& operator=(NelderMead other);
    Result optimize();
};

#endif // NELDERMEAD_H
