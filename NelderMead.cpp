#include "NelderMead.h"
//#define debug_nm

/** \file */

NelderMead::NelderMead(){

}

NelderMead::NelderMead(Function* func, BoxArea* area, StopCriterion* crit,
                       double alpha, double beta, double gamma,
                       const std::vector<std::vector<double>>& simplex) : OptimizationMethod(func, area, crit), simplex_(simplex),
                       alpha_(alpha), beta_(beta), gamma_(gamma){
    assert(simplex_.size() ==0 || (simplex_.size() == area_->dim() + 1 && simplex_[0].size() == area_->dim()));
    curr_point_ = update_trajectory();
}

NelderMead::NelderMead(const NelderMead& other) : OptimizationMethod(other), simplex_(other.simplex_),
                                                  simplex_fun_value_(other.simplex_fun_value_), curr_point_(other.curr_point_),
                                                  index_h(other.index_h), index_l(other.index_l), index_g(other.index_g),
                                                  alpha_(other.alpha_), beta_(other.beta_), gamma_(other.gamma_),
                                                  out_of_area_flg_(other.out_of_area_flg_) {
}

NelderMead::NelderMead(NelderMead&& other) : OptimizationMethod(other), simplex_(std::move(other.simplex_)),
                                             simplex_fun_value_(std::move(other.simplex_fun_value_)),
                                               curr_point_(std::move(other.curr_point_)),
                                               index_h(other.index_h), index_l(other.index_l), index_g(other.index_g),
                                               alpha_(other.alpha_), beta_(other.beta_), gamma_(other.gamma_),
                                                out_of_area_flg_(other.out_of_area_flg_) {
    other.index_h = 0;
    other.index_l = 0;
    other.index_g = 0;
    other.alpha_ = 0;
    other.beta_ = 0;
    other.gamma_ = 0;
    other.out_of_area_flg_ = 0;
}

void NelderMead::swap(NelderMead &other) noexcept {
    OptimizationMethod::swap(other);
    std::swap(simplex_, other.simplex_);
    std::swap(simplex_fun_value_, other.simplex_fun_value_);
    std::swap(curr_point_, other.curr_point_);
    std::swap(index_h, other.index_h);
    std::swap(index_l, other.index_l);
    std::swap(index_g, other.index_g);
    std::swap(alpha_, other.alpha_);
    std::swap(beta_, other.beta_);
    std::swap(gamma_, other.gamma_);
    std::swap(out_of_area_flg_, other.out_of_area_flg_);
}

NelderMead& NelderMead::operator=(NelderMead other) noexcept {
    this->swap(other);
    return *this;
}

void NelderMead::init_simplex(){
    simplex_.resize(ndim_ + 1);
    for (size_t i = 0; i < ndim_ + 1; ++i){
        simplex_[i].resize(ndim_);
        for (size_t j = 0; j < ndim_; ++j)
            simplex_[i][j] = get_unif(area_->get_limits(j).lower, area_->get_limits(j).upper);
    }
    niter_ = 0;
    x_trajectory_.resize(0);


}

Result NelderMead::optimize(){
    if (simplex_.size() == 0)
        init_simplex();
    evaluate_fun_simplex();
    search();
    return Result(x_trajectory_.back(), target_func_->eval(x_trajectory_.back()), niter_, out_of_area_flg_);
}


void NelderMead::evaluate_fun_simplex(){
    if (simplex_fun_value_.size() != ndim_ + 1)
        simplex_fun_value_.resize(ndim_ + 1);
    for (size_t i = 0; i < ndim_ + 1; ++i)
        simplex_fun_value_[i] = target_func_->eval(simplex_[i]);
}

void NelderMead::make_iter(){
    /*if (!simplex_.size()){
        init_simplex();
        evaluate_fun_simplex();
    }*/
    find_indices();
    curr_point_ = update_trajectory();
    for (size_t i = 0; i < simplex_.size(); ++i)
        if (!area_->is_in(simplex_[i])){
            out_of_area_flg_ = true;
            std::cout << "Point outside area: " << simplex_[i] << "\n";
            return;
        }
    evaluate_fun_simplex();
    std::vector<double> x_r, x_e, x_c;
    double f_r, f_e, f_c;

    x_r = -alpha_ * simplex_[index_h] + (1+alpha_) * x_trajectory_[niter_];
    //std::cout << "x_r:" << x_r << "\n";
    if (!area_->is_in(x_r)){
        out_of_area_flg_ = true;
        //std::cout << "x_h: " << simplex_[index_h] << "\n";
        //std::cout << "x_0: " << x_trajectory_[niter_] << "\n";
        //std::cout << "Point outside area x_r: " << x_r << "\n";
        return;
    }
    f_r = target_func_->eval(x_r);

    if (f_r < simplex_fun_value_[index_l]){
        x_e = (1 - gamma_) * x_trajectory_[niter_] + gamma_ * x_r;
        if (!area_->is_in(x_e)){
            out_of_area_flg_ = true;
            //std::cout << "Point outside area x_e: " << x_e << "\n";
            return;
        }
        f_e = target_func_->eval(x_e);
        if (f_e < f_r){
            simplex_[index_h] = x_e;
            simplex_fun_value_[index_h] = f_e;
            return;
        } else {
            simplex_[index_h] = x_r;
            simplex_fun_value_[index_h] = f_r;
            return;
        }
    } else {
        if (simplex_fun_value_[index_l] < f_r && f_r < simplex_fun_value_[index_g]){
            simplex_[index_h] = x_r;
            simplex_fun_value_[index_h] = f_r;
            evaluate_fun_simplex();
            return;
        }
        if (simplex_fun_value_[index_g] < f_r && f_r < simplex_fun_value_[index_h]){
            std::swap(simplex_[index_h], x_r);
            std::swap(simplex_fun_value_[index_h], f_r);
        }
        x_c = beta_ * simplex_[index_h] + (1 - beta_) * x_trajectory_[niter_];
        if (!area_->is_in(x_c)){
            //std::cout << "Point outside area x_c: " << x_c << "\n";
            out_of_area_flg_ = true;
            return;
        }
        f_c = target_func_->eval(x_c);
        if (f_c < simplex_fun_value_[index_h]) {
            simplex_[index_h] = x_c;
            simplex_fun_value_[index_h] = f_c;
            evaluate_fun_simplex();
            return;
        } else {
            for (size_t i = 0; i < simplex_.size(); ++i)
                if (i != index_l){
                    simplex_[i] = simplex_[index_l] + (simplex_[i] - simplex_[index_l]) * 0.5;
                    evaluate_fun_simplex();
                }
        }
    }
}

MethodStatus* NelderMead::get_status() const{
    //std::cout << "\n";
    return new NMStatus(niter_, &simplex_fun_value_, out_of_area_flg_);
}

std::vector<double> NelderMead::update_trajectory(){
    std::vector<double> sum(ndim_, 0);
    for (size_t i = 0; i < simplex_.size(); ++i)
        if (i != index_h) sum = sum + simplex_[i];
    x_trajectory_.push_back(sum / ndim_);
    return sum / ndim_;
}

void NelderMead::find_indices(){
    index_h = simplex_.size()  + 1;
        index_g = simplex_.size() + 1;
        index_l = simplex_.size() + 1;
        for (size_t i = 0; i < ndim_ + 1; ++i){
            if (index_h == simplex_.size() + 1 || simplex_fun_value_[i] > simplex_fun_value_[index_h]){
                index_g = index_h;
                index_h = i;
            } else if (index_g == simplex_.size() + 1 || simplex_fun_value_[i] > simplex_fun_value_[index_g])
                index_g = i;
            if (index_l == simplex_.size() + 1 || simplex_fun_value_[i] < simplex_fun_value_[index_l])
                index_l = i;
        }
    /*
    index_h = simplex_.size() + 1;
    index_g = simplex_.size() + 1;


    for (size_t i = 0; i < ndim_ + 1; ++ i)
        if (index_h == simplex_.size() + 1 || simplex_fun_value_[i] > simplex_fun_value_[index_h])
            index_h = i;

    for (size_t i = 0; i < ndim_ + 1; ++ i)
        if (index_l == simplex_.size() + 1 || simplex_fun_value_[i] < simplex_fun_value_[index_l])
            index_l = i;
    index_g = index_l;
    for (size_t i = 0; i < ndim_ + 1; ++i)
        if (i != index_h and simplex_fun_value_[i] > simplex_fun_value_[index_g])
            index_h = i;
            */
}
