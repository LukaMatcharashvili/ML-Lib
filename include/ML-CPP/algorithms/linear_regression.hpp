#ifndef ALG_LIN_REG_H
#define ALG_LIN_REG_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "../data_structures/matrix.hpp"
#include "../data_structures/vector.hpp"
#include "gradient_descent.hpp"
#include "prediction.hpp"

namespace algorithms
{
    class LinearRegression
    {
    private:
        data_structures::Matrix<double> x_;
        data_structures::Vector<double> y_;
        data_structures::Vector<double> w_;
        double b_ = 0;
        double lr_;
        t_trainF trainF_;

    public:
        ~LinearRegression() = default;
        LinearRegression(
            const data_structures::Matrix<double> &x,
            const data_structures::Vector<double> &y,
            const double lr = 0.001,
            const std::vector<double> &w = std::vector<double>(),
            const t_trainF &trainF = batch_gd::train)
            : x_(x),
              y_(y),
              w_(w.empty() ? data_structures::Vector<double>(x.shape().second) : data_structures::Vector<double>(w)),
              lr_(lr),
              trainF_(trainF) {}

        data_structures::Vector<double> get_weights() const
        {
            return w_;
        }

        double get_bias() const
        {
            return b_;
        }

        void print_weights() const
        {
            w_.print();
            std::cout << "b_: " << b_ << '\n';
        }

        void train()
        {
            trainF_(x_, y_, w_, b_, lr_, static_predictions::linear_predict);
        }

        inline double predict(const data_structures::Vector<double> &x) const
        {
            return x.dot(w_) + b_;
        }
    };
}

#endif // ALG_LIN_REG_H
