#include "NMStatus.h"

NMStatus::NMStatus(){

}

NMStatus::NMStatus(const NMStatus& other) : MethodStatus(other), value(other.value){

}

NMStatus::NMStatus(size_t niter, const std::vector<double>* values) : MethodStatus(niter), value(values){

}


void NMStatus::swap(NMStatus& other) noexcept{
    MethodStatus::swap(other);
    std::swap(value, other.value);
}

NMStatus& NMStatus::operator=(NMStatus other){
    this->swap(other);
    return *this;
}

double NMStatus::get_value(size_t ind){
    return value->at(ind);
}

size_t NMStatus::get_npoints() noexcept{
    return value->size();
}
