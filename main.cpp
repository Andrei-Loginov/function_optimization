#include <iostream>
#include <cmath>
#include <string>
#include <cctype>
#include <cstdio>
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

double Beale(std::vector<double> x){
    double x_ = x[0], y_ = x[1];
    return (pow((1.5 - x_ + x_ * y_), 2) + pow(2.25 - x_ +x_ * pow(y_, 2), 2) + pow(2.625 - x_ + x_ * pow(y_, 3), 2));
}

double Bukin_N6(std::vector<double> x){  //https://youtu.be/Nm44Wpy7jlU
    double x_ = x[0], y_ = x[1];
    return(100 * sqrt(abs(y_ - 0.01 * pow(x_,2))) + 0.01 * (x_ + 10));
}

double Matyas(std::vector<double> x){
    return(0.26 * (x[0] * x[0] + x[1] * x[1]) - 0.48 * x[0] * x[1]);
}

double sum_of_abs(std::vector<double> x){
    return abs(x[0]) + abs(x[1]) + abs(x[2]);
}

bool is_str_double(const std::string& str){
    if (!str.size()) return false;
    size_t first_digit = (str[0] == '-') ? 1 : 0;
    for (size_t i = first_digit; i < str.size(); ++i)
        if (!isdigit(str[i])) return false;
    return true;
}




int main(){
    std::cout << Matyas({0, 0}) << "\n";

    SingletonGenerator::get_mt().seed(475);
    OptimizationMethod* optimizer = nullptr;
    Function f;
    BoxArea area;
    StopCriterion* crit = nullptr;
    Result res;
    std::vector<dimension_limits> limits;
    double lower, upper, delta, p, alpha, beta, gamma, epsilon;
    std::vector<std::vector<double>> init_simplex;
    std::cout << "Function optimization\n";
    int action_index = -1, func_index = -1, method_index = -1,  param_index, stop_index, point_index, simplex_index;
    size_t max_iter, max_iter_after;
    std::vector<double> first_point;
    bool fl;

    try {
        bool flg = true;
        while (action_index != 0){
            std::cout << "0 --- exit\nany other number --- set function, method, area, etc.\n";
            if (!scanf("%Iu", &action_index)) throw std::invalid_argument("Wrong format!"); //action_index
            if (action_index) {
                func_index = -1;
                while (func_index < 1 || func_index > 7){
                    std::cout << "Set function:\n\t1 --- Rosenbrock 2d\n\t2 --- Rosenbrock 3d\n\t";
                    std::cout << "3 --- sum of abs 3d\n\t4 --- parabola 2d\n\t5 - Beale function\n\t";
                    std::cout << "6 --- Bukin function N6\n\t7 --- Matyas function\n";
                    if (!scanf("%Iu", &func_index)) throw std::invalid_argument("Wrong format!");
                }
                switch(func_index) {
                case 1:
                    f =  Function(2,Rosenbrock_2d);
                    break;
                case 2:
                    f = Function(3, Rosenbrock_3d);
                    break;
                case 3:
                    f = Function(3, sum_of_abs);
                    break;
                case 4:
                    f = Function(2, parabolic);
                    break;
                case 5:
                    f = Function(2, Beale);
                    break;
                case 6:
                    f = Function(2, Bukin_N6);
                    break;
                case 7:
                    f = Function(2, Matyas);
                    break;
                }

                //Set area
                std::cout << "Set area of search:\n";
                limits.resize(f.dim());
                for (size_t i = 0; i < f.dim(); ++i){
                    flg = true;
                    while (flg || lower >= upper){
                        flg = false;
                        std::cout << "\tSet coordinate " << i + 1 << " bounds: ";
                        //std::cin >> lower >> upper;
                        if (!scanf("%lf", &lower)) throw std::invalid_argument("Wrong format!");
                        if (!scanf("%lf", &upper)) throw std::invalid_argument("Wrong format!");
                    }
                    limits[i] = dimension_limits(lower, upper);
                }
                area = BoxArea(f.dim(), limits);

                //Set method
                std::cout << "Set optimization method.";
                method_index = -1;
                while (method_index < 1 || method_index > 2){
                    std::cout << "\n\t1 --- Stohastic\n\t2 --- Nelder-Mead\n";
                    //std::cin >> method_index;
                    if (!scanf("%Iu", &method_index)) throw std::invalid_argument("Wrong format!");
                }
                std::cout << "Parameters of algorithm.";
                std::cout << "\n\t0 --- default\n\tany other number --- manual\n";
                //std::cin >> param_index;
                if (!scanf("%Iu", &param_index)) throw std::invalid_argument("Wrong format!");

                switch (method_index) {
                case 1:
                    if (param_index) {
                        p = -1;
                        while (p <= 0){
                            std::cout << "Set p: ";
                            //std::cin >> p;
                            if (!scanf("%ld", &p)) throw std::invalid_argument("Wrong format!");
                        }
                        delta = -2;
                        while (delta <= 0) {
                            std::cout << "Set delta: ";
                            //std::cin >> delta;
                            if (!scanf("%lf", &delta)) throw std::invalid_argument("Wrong format!");
                        }
                    } else {
                        p = 0.5;
                        delta = 0.5;
                    }
                    std::cout << "Stop criterion parameters.";
                    std::cout << "\n\t0 --- default\n\tany other number --- manual\n";
                    //std::cin >> stop_index;
                    if (!scanf("%Iu", &stop_index)) throw std::invalid_argument("Wrong format!");

                    if (stop_index){
                        max_iter = -1;
                        while (max_iter <= 0) {
                            std::cout << "Maximal number of iterations: ";
                            //std::cin >> max_iter;
                            if (!scanf("%Iu", &max_iter)) throw std::invalid_argument("Wrong format!");
                        }
                        max_iter_after = 0;
                        while (max_iter_after <= 0){
                            std::cout << "Maximal number of iterations after the last improvment: ";
                            //std::cin >> max_iter_after;
                            if (!scanf("%Iu", &max_iter_after)) throw std::invalid_argument("Wrong format!");
                        }
                    } else {
                        max_iter = 10000;
                        max_iter_after = 1000;
                    }

                    std::cout << "First point\n";
                    std::cout << "\n\t0 --- default\n\tany other number --- manual\n";
                    std::cin >> point_index;
                    if (point_index){
                        while (first_point.size() == 0 || !area.is_in(first_point)){
                            if (first_point.size() == 0) first_point.resize(f.dim());
                            std::cout << "Enter " << f.dim() << " coordinates: \n";
                            for (size_t i = 0; i < f.dim(); ++i)
                                //std::cin >> first_point[i];
                                if (!scanf("%lf", &first_point[i])) throw std::invalid_argument("Wrong format!");
                        }
                    } else {
                        first_point.resize(0);
                    }
                    if (crit) delete crit;
                    crit = new StohIterStop(max_iter, max_iter_after);
                    if (optimizer) delete optimizer;
                    optimizer = new StohasticOptimization(&f, &area, crit, p, delta, first_point);
                    break;
                case 2:
                    if (param_index){
                       alpha = -1;
                       while (alpha <= 0) {
                           std::cout << "Enter alpha > 0 : ";
                           //std::cin >> alpha;
                           if (!scanf("%lf", &alpha)) throw std::invalid_argument("Wrong format!");
                       }
                       beta = -1;
                       while (beta <= 0) {
                           std::cout << "Enter beta > 0: ";
                           //std::cin >> beta;
                           if (!scanf("%lf", &beta)) throw std::invalid_argument("Wrong format!");
                       }
                       gamma = -1;
                       while (gamma <= 0){
                           std::cout << "Enter gamma > 0: ";
                           //std::cin >> gamma;
                           if (!scanf("%lf", &gamma)) throw std::invalid_argument("Wrong format!");
                       }
                    } else {
                        alpha = 1;
                        beta = 0.5;
                        gamma = 2;
                    }

                    std::cout << "Stop criterion parameters.";
                    std::cout << "\n\t0 --- default\n\tany other number --- manual\n";
                    std::cin >> stop_index;
                    if (stop_index){
                        max_iter = -1;
                        while (max_iter <= 0) {
                            std::cout << "Maximal number of iterations: ";
                            //std::cin >> max_iter;
                            if (!scanf("%Iu", &max_iter)) throw std::invalid_argument("Wrong format!");
                        }
                        epsilon = -1;
                        while (epsilon <= 0){
                            std::cout << "Enter epsilon for Standart Deviation stop criterion: ";
                            //std::cin >> epsilon;
                            if (!scanf("%lf", &epsilon)) throw std::invalid_argument("Wrong format!");
                        }
                    } else {
                        max_iter = 10000;
                        epsilon = 1e-8;
                    }

                    init_simplex.clear();
                    std::cout << "Start simplex.";
                    std::cout << "\n\t0 --- random points\n\tany other number --- set manualy\n";
                    //std::cin >> simplex_index;
                    if (!scanf("%Iu", &simplex_index)) throw std::invalid_argument("Wrong format!");

                    if (simplex_index) {
                        std::cout << "Set " << f.dim() + 1 << " points.";
                        init_simplex.resize(f.dim() + 1);
                        for (size_t i = 0; i < f.dim() + 1; ++i){
                            while (fl || !area.is_in(init_simplex[i])){
                                fl = false;
                                if (init_simplex.size() != f.dim())
                                    init_simplex[i].resize(f.dim());

                                std::cout << "Point " << i + 1;
                                for (size_t j = 0; j < f.dim(); ++j){
                                    std::cout << "\n\tCoordinate " << j + 1 << ": ";
                                    //std::cin >> init_simplex[i][j];
                                    if (!scanf("%lf", &init_simplex[i][j])) throw std::invalid_argument("Wrong format!");
                                }
                            }
                        }
                    }

                    if (crit) delete crit;
                    if (optimizer) delete optimizer;
                    crit = new NMSDstop(max_iter, epsilon);
                    optimizer = new NelderMead(&f, &area, crit, alpha, beta, gamma, init_simplex);
                    break;
                }
                res = optimizer->optimize();
                if (res.out_of_area_flg)
                    std::cout << "The method was stopped becuase one of points has gone outside the area.";
                std::cout << "Iterations: " << res.niter << "\n";
                std::cout << "f(" << res.x[0] << ", " << res.x[1];
                if (f.dim() == 3) std::cout << ", " << res.x[2];
                std::cout << ") = " << res.y << "\n";
            }
        }

    }
    catch (std::exception& e){
        std::cout << e.what() << "\n";
    }
    if (optimizer) delete optimizer;
    if (crit) delete crit;
    /****************************/

}
/*
void sth(){
Function parab(2, parabolic);
std::vector<dimension_limits> lim = {dimension_limits(-20, 20), dimension_limits(-20, 20)};
std::vector<std::vector<double>> init_simplex(3);
init_simplex[0] = {1, 1}; init_simplex[1] = {2, 2}; init_simplex[2] = {2, 3};
std::vector<double> arg = {0, 0};
std::cout << "Evaluate parabolic at (0, 0): " << parab.eval(arg) << "\n\n";
NelderMead optimParab(&parab, new BoxArea(2, lim), new NMSDstop(100), 1, 0.5, 2, init_simplex);
Result res = optimParab.optimize();
if (res.out_of_area_flg)
    std::cout << "The method was stopped becuase one of points has gone outside the are. The lsast iteration: ";
std::cout << "Iterations: " << res.niter << "\n";
std::cout << "f(" << res.x[0] << ", " << res.x[1] << ") = " << res.y << "\n";
}

int old_main(){
    SingletonGenerator::get_mt().seed(475);
    Function f(2, parabolic);
    std::vector<dimension_limits> lim = {dimension_limits(-10, 10), dimension_limits(-10, 10)};
    Function ros(2, Rosenbrock_2d);
    std::vector<double> arg = {1, 1};
    std::cout << "Evaluate ros at (1, 1): " << ros.eval(arg) << "\n\n";
    std::vector<std::vector<double>> init_simplex(3), init_simplex3d(4);
    init_simplex[0] = {0, 0}; init_simplex[1] = {-1, -1}; init_simplex[2] = {1.5, 1.5};
    NelderMead optimRos(&ros, new BoxArea(2, lim), new NMSDstop(100), 1, 0.5, 2, init_simplex);
    Result res = optimRos.optimize();
    if (res.out_of_area_flg)
        std::cout << "The method was stopped becuase one of points has gone outside the are. The last iteration: ";
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
*/
