#ifndef ALG_LOG_REG_H
#define ALG_LOG_REG_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "../data_structures/matrix.hpp"
#include "../data_structures/vector.hpp"
#include "../features/activations.hpp"
#include "gradient_descent.hpp"
#include "prediction.hpp"

namespace algorithms
{
    class LogisticRegression
    {
    private:
        data_structures::Matrix x_;
        data_structures::Vector y_;
        data_structures::Vector w_;
        double b_ = 0;
        double lr_;
        t_trainF trainF_; // TODO: Change this to mini_batch_gd::train when implemented

    public:
        ~LogisticRegression() = default;
        LogisticRegression(const data_structures::Matrix &x, const data_structures::Vector &y, const data_structures::Vector &w = data_structures::Vector(0), const double lr = 0.01, const t_trainF &trainF = batch_gd::train)
            : x_(x),
              y_(y),
              w_(w.size() == 0 ? data_structures::Vector(x.shape().second) : w),
              lr_(lr),
              trainF_(trainF) {}

        data_structures::Vector get_weights() const
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
            trainF_(x_, y_, w_, b_, lr_, static_predictions::logistic_predict);
        }

        inline double predict(const data_structures::Vector &x) const
        {
            return features::activations::sigmoid(x.dot(w_) + b_);
        }
    };

}

#endif // ALG_LOG_REG_H
