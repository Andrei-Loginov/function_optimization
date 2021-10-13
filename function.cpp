#include "function.h"

Function::Function() {

}

Function::Function(int dim, double (*func)(std::vector<double>)) : ndim(dim), function(func){

}

Function::Function(const Function& other) : ndim(other.ndim), function(other.function){

}

Function::Function(Function&& other) noexcept : ndim(other.ndim), function(other.function){
    other.ndim = 0;
    other.function = nullptr;
}

double Function::eval(const std::vector<double>& args) const{
    return function(args);
}

double Function::operator()(const std::vector<double>& args) const{
    return eval(args);
}

void Function::swap(Function& other) noexcept{
    std::swap(ndim, other.ndim);
    std::swap(function, other.function);
}

Function& Function::operator=(Function other){
    this->swap(other);
    return *this;
}

size_t Function::dim() const {
    return ndim;
}

void Function::set_func(int new_dim, double (*new_func)(std::vector<double>)){
    ndim = new_dim;
    function = new_func;
}
