#ifndef NELDERMEAD_H
#define NELDERMEAD_H
#include "OptimizationMethod.h"
#include "NMStatus.h"
/** \file */
/**
 * @brief Класс NelderMead содержит в себе реализацию алгоритма Нелдера-Мида поиска минимума функции, заданной объектом Function, в области
 * заданной объектом BoxArea.
 */

class NelderMead : public OptimizationMethod{
protected:
    std::vector<std::vector<double>> simplex_; //!< Точки симплекса
    std::vector<double> simplex_fun_value_; //!< Значения функции в вершинах симплекса
    std::vector<double> curr_point_; //!< Центр масс текщуего симплекса
    size_t index_h, index_l, index_g; //!< Индексы точек $x_h$, $x_l$, $x_g$ симплекса
    void init_simplex(); //!< Инициализация симлпекса случайными точками
    void evaluate_fun_simplex(); //!<Метод, вычисляющий значения simplex_fun_value_ в точках simplex_
    void make_iter(); //!< Метод, совершающий итерацию алгоритмма Нелдера-Мида
    void find_indices(); //!< Метод поиска индексов точек $x_h$, $x_l$, $x_g$
    MethodStatus* get_status() const; //!< Метод, создающий указатель на объект типа MethodStatus (NMStatus), содержащий информацию о текущем состоянии алгоритма
    std::vector<double> update_trajectory(); //!< Метод вычисляет центр масс точек симплекса за исключением точки $x_h$
    double alpha_ = 1, beta_ = 0.5, gamma_ = 2; //!< Коэффициенты отражения, сжатия и растяжения.
    bool out_of_area_flg_ = false; //!< Флаг выхода за пределы области. В случае, если он принимает значение true, алгоритм останавливается.

public:
    //! Конструктор по умолчанию
    NelderMead();
    /**! Конструктор, задающий функцию, которую нужно оптимизировать, область, критерий остановки, коэффициенты сжатия, отражения, растяжения и начальный симплекс.
    *
    * Если simplex является пустым вектором, то симплекс инициализируется случайными точками.
    **/
    NelderMead(Function* func, BoxArea* area, StopCriterion* crit,
               double alpha = 1, double beta = 0.5, double gamma = 2,
               const std::vector<std::vector<double>>& simplex = std::vector<std::vector<double>>());
    //! Констуктор перемещения
    NelderMead(NelderMead&& other);
    //! Конструктор копирования
    NelderMead(const NelderMead& other);
    //! Метод обмена noexcept
    void swap(NelderMead& other) noexcept;
    //! noexcept оператор присваивания
    NelderMead& operator=(NelderMead other) noexcept;
    //! Метод, осуществляющий поиск точки минимума и вовращающий результат работы алгоритма.
    Result optimize();
};

#endif // NELDERMEAD_H
