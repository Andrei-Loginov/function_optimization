#include <iostream>
#include <cmath>
#include "function.h"
#include "NelderMead.h"
#include "NMSDstop.h"

double sqr(std::vector<double> x){
    return x[0]*x[0];
}

double my_sqrt(std::vector<double> x){
    return sqrt(x[0]);
}

double my_func(std::vector<double> x){
    return x[0] + x[1] * x[0];
}

double parabolic(std::vector<double> x){
    return x[0]*x[0] + x[1]*x[1];
}

double Rosenbrock_2d(std::vector<double> x){
    return pow(1- x[0], 2) + 100 * pow(x[1] - pow(x[0],2), 2);
}

double Rosenbrock_3d(std::vector<double> x){
    return pow(1 - x[0], 2) + 100* pow(x[1] - pow(x[0], 2), 2) + pow(1 - x[1], 2) + 100* pow(x[2] - pow(x[1], 2), 2);
}

int main(){
    SingletonGenerator::get_mt().seed(15995);
    Function f(2, parabolic);
    std::vector<dimension_limits> lim = {dimension_limits(-3, 3), dimension_limits(-3, 3)};
    NelderMead optimizer(&f, new BoxArea(2, lim), new NMSDstop(1000));
    //Result res = optimizer.optimize();
    //std::cout << res.x[0] << " " << res.x[1] << " " << res.y << "\n";
    //std::cout << "Finished!\n";
    Function ros(2, Rosenbrock_2d);
    std::vector<double> arg = {1, 1};
    std::cout << "Evaluate ros at (1, 1): " << ros.eval(arg) << "\n\n";
    std::vector<std::vector<double>> init_simplex(3);
    init_simplex[0] = {0, 0}; init_simplex[1] = {-1, -1}; init_simplex[2] = {1.5, 1.5};
    NelderMead optimRos(&ros, new BoxArea(2, lim), new NMSDstop(100), 1, 0.5, 2);
    Result res = optimRos.optimize();
    std::cout << res.x[0] << " " << res.x[1] << " " << res.y << "\n";
    std::vector<dimension_limits> lim3 = {dimension_limits(-3, 3), dimension_limits(-3, 3), dimension_limits(-3, 3)};
    Function ros3(3, Rosenbrock_3d);
    NelderMead optimRos3(&ros3, new BoxArea(3, lim3), new NMSDstop(100), 1, 0.5, 2);
    res = optimRos3.optimize();
    std::cout << res.x[0] << " " << res.x[1] << " " << res.x[2] << " " << res.y << "\n";
    return 0;
}
