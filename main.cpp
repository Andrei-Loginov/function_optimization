#include <iostream>
#include <cmath>
#include "Function.h"

double sqr(std::vector<double> x){
    return x[0]*x[0];
}

double my_sqrt(std::vector<double> x){
    return sqrt(x[0]);
}

double my_func(std::vector<double> x){
    return x[0] + x[1] * x[0];
}

int main(){
    Function f1(1, sqr);
    Function f2(f1);
    Function f3(2, my_func);
    std::vector<double> x = {2.5}, y = {4, 5};
    std::cout << "Check the copy constructor: " << f1(x) << " " << f2(x) << "\n";
    f2 = f3;
    std::cout << "Check the assignment operator: " << f3(y) << " " << f2(y) << "\n";
    Function f4(std::move(f3));
    std::cout << "Check the move constructor:\n\tNew function: " << f4(y) << "\n";

    f4.set_func(1, sqr);
    std::cout << "Check set_func: " << f4(x) << "\n";
    return 0;
}
