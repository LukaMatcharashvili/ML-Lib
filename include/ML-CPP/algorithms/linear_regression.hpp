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
        data_structures::Matrix X;
        data_structures::Vector y;
        data_structures::Vector w;
        double b = 0;
        double lr = 0.01;
        t_trainF trainF; // TODO: Change this to mini_batch_gd::train when implemented

    public:
        LinearRegression(const data_structures::Matrix &X, const data_structures::Vector &y, const double lr, const t_trainF &trainF = batch_gd::train)
            : X(X),
              y(y),
              w(data_structures::Vector(X.shape().second)),
              lr(lr),
              trainF(trainF)
        {
        }
        LinearRegression(const data_structures::Matrix &X, const data_structures::Vector &y, const t_trainF &trainF = batch_gd::train)
            : X(X),
              y(y),
              w(data_structures::Vector(X.shape().second)),
              trainF(trainF) {}

        data_structures::Vector get_weights() const
        {
            return w;
        }

        double get_bias() const
        {
            return b;
        }

        void print_weights() const
        {
            w.print();
            std::cout << "b: " << b << '\n';
        }

        void train()
        {
            trainF(X, y, w, b, lr, static_predictions::linear_predict);
        }

        inline double predict(const data_structures::Vector &x) const
        {
            return x.dot(w) + b;
        }
    };
}

#endif // ALG_LIN_REG_H
