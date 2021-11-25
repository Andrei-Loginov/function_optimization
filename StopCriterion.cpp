#include "StopCriterion.h"

StopCriterion::StopCriterion(){

}

StopCriterion::StopCriterion(const StopCriterion& other) : name(other.name){}

StopCriterion::StopCriterion(StopCriterion&& other) noexcept : name(std::move(other.name)){}

void StopCriterion::swap(StopCriterion& other) noexcept {
    std::swap(name, other.name);
}

bool StopCriterion::operator()(MethodStatus* method){
    return criterion(method);
}
