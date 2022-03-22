#include <iostream>
#include <cmath>
#include "function.h"
#include "NelderMead.h"
#include "NMSDstop.h"
#include "StohasticOptimization.h"
#include "StohIterStop.h"
/** \file */

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
    SingletonGenerator::get_mt().seed(475);
    Function f(2, parabolic);
    std::vector<dimension_limits> lim = {dimension_limits(-10, 10), dimension_limits(-10, 10)};
    NelderMead optimizer(&f, new BoxArea(2, lim), new NMSDstop(1000));
    //Result res = optimizer.optimize();
    //std::cout << res.x[0] << " " << res.x[1] << " " << res.y << "\n";
    //std::cout << "Finished!\n";
    Function ros(2, Rosenbrock_2d);
    std::vector<double> arg = {1, 1};
    std::cout << "Evaluate ros at (1, 1): " << ros.eval(arg) << "\n\n";
    std::vector<std::vector<double>> init_simplex(3), init_simplex3d(4);
    init_simplex[0] = {0, 0}; init_simplex[1] = {-1, -1}; init_simplex[2] = {1.5, 1.5};
    NelderMead optimRos(&ros, new BoxArea(2, lim), new NMSDstop(100), 1, 0.5, 2, init_simplex);
    Result res = optimRos.optimize();
    if (res.out_of_area_flg)
        std::cout << "The method was stopped becuase one of points has gone outside the are. The lsast iteration: ";
    std::cout << "Iterations: " << res.niter << "\n";
    std::cout << "f(" << res.x[0] << ", " << res.x[1] << ") = " << res.y << "\n";
    std::vector<dimension_limits> lim3 = {dimension_limits(-10, 10), dimension_limits(-10, 10), dimension_limits(-10, 10)};
    Function ros3(3, Rosenbrock_3d);
    init_simplex3d[0] = {0, 0, 0}; init_simplex3d[1] = {-1, -1, -1}; init_simplex3d[2] = {1.5, 1.5, 1.5};
    init_simplex3d[3] = {2, 2, 2};
    NelderMead optimRos3(&ros3, new BoxArea(3, lim3), new NMSDstop(100), 1, 0.5, 2, init_simplex3d);
    res = optimRos3.optimize();
    std::cout << "Iterations: " << res.niter << "\n";
    std::cout << res.out_of_area_flg << " " << res.x[0] << " " << res.x[1] << " " << res.x[2] << " " << res.y << "\n";

    StohasticOptimization random_optim(&ros, new BoxArea(2, lim), new StohIterStop(1000000, 100000));
    res = random_optim.optimize();
    std::cout << "Ierations: " << res.niter << "\n";
    std::cout << res.x[0] << " " << res.x[1] << " " << res.y << "\n";
    return 0;
}
