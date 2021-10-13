#include "OptimizationMethod.h"

OptimizationMethod::OptimizationMethod(){
}

OptimizationMethod::OptimizationMethod(const OptimizationMethod& other) : target_func_(other.target_func_), area_(other.area_){
}

OptimizationMethod::OptimizationMethod(OptimizationMethod&& other) : target_func_(std::move(other.target_func_)),
                                                                     area_(std::move(other.area_)) {
}

OptimizationMethod::OptimizationMethod(Function* func, BoxArea* area, StopCriterion* crit) : target_func_(func),
                                                                                             area_(area),
                                                                                             stop_crit_(crit){
    assert(area->dim() == func->dim());
}

void OptimizationMethod::swap(OptimizationMethod& other){
     std::swap(other.target_func_, target_func_);
     std::swap(area_, other.area_);
}

OptimizationMethod& OptimizationMethod::operator=(OptimizationMethod &other){
    this->swap(other);
    return *this;
}
