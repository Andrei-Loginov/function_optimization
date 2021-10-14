#include "OptimizationMethod.h"

OptimizationMethod::OptimizationMethod(){
}

OptimizationMethod::OptimizationMethod(const OptimizationMethod& other) : target_func_(other.target_func_), area_(other.area_),
                                                                        stop_crit_(other.stop_crit_)
{
}

OptimizationMethod::OptimizationMethod(OptimizationMethod&& other) : target_func_(std::move(other.target_func_)),
                                                                     area_(std::move(other.area_)),
                                                                    stop_crit_(std::move(other.stop_crit_)),
                                                                    ndim_(other.ndim_)
{
    other.ndim_ = 0;
}

OptimizationMethod::OptimizationMethod(Function* func, BoxArea* area, StopCriterion* crit) : target_func_(func),
                                                                                             area_(area),
                                                                                             stop_crit_(crit),
                                                                                             ndim_(area_->dim()){
    assert(area->dim() == func->dim());
}

void OptimizationMethod::swap(OptimizationMethod& other){
     std::swap(other.target_func_, target_func_);
     std::swap(area_, other.area_);
     std::swap(stop_crit_, other.stop_crit_);
     std::swap(ndim_, other.ndim_);
}


double OptimizationMethod::get_unif(double lower, double upper){
    std::uniform_real_distribution<double> unif_real(lower, upper);
    return unif_real(SingletonGenerator::get_mt());
}

void OptimizationMethod::search(){
    while (!stop_crit_->criterion(this)){
        make_iter();
    }
}
