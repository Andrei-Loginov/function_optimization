#include "NelderMead.h"

NelderMead::NelderMead()
{

}

NelderMead::NelderMead(Function* func, BoxArea* area, StopCriterion* crit,
                       const std::vector<std::vector<double>>& start_simplex) : OptimizationMethod(func, area, crit),
                                                                                start_simplex_(start_simplex){
    assert(start_simplex_.size() ==0 || (start_simplex_.size() == area_->dim() + 1 && start_simplex_[0].size() == area_->dim()));

}

void NelderMead::swap(NelderMead &other) noexcept {
    OptimizationMethod::swap(other);
    std::swap(curr_simplex_, other.curr_simplex_);
    std::swap(prev_iter_simplex_, other.prev_iter_simplex_);
    std::swap(start_simplex_, other.start_simplex_);
}

void NelderMead::init_simplex(){
    start_simplex_.resize(ndim_ + 1);
    for (size_t i = 0; i < ndim_ + 1; ++i){
        start_simplex_[i].resize(ndim_);
        for (size_t j = 0; j < ndim_; ++j)
            start_simplex_[i][j] = get_unif(area_->get_limits(j).lower, area_->get_limits(j).upper);
    }
    for (size_t i = 0; i < ndim_ + 1; ++i){
        for (size_t j = 0; j < ndim_; ++j)
            std::cout << start_simplex_[i][j] << "\n";
        std::cout << "\n";
    }

}

Result NelderMead::optimize(){
    if (start_simplex_.size() == 0)
        init_simplex();
    curr_simplex_ = start_simplex_;

    search();
    return Result(x_trajectory_.back(), target_func_->eval(x_trajectory_.back()), niter_);
}

void NelderMead::make_iter(){

}
