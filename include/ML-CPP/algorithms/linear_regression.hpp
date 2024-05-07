#ifndef ALG_LIN_REG_H
#define ALG_LIN_REG_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "../data_structures/matrix.hpp"
#include "../data_structures/vector.hpp"

namespace algorithms
{
    class BatchLinearRegression
    {
    private:
        data_structures::Matrix X;
        data_structures::Vector y;
        data_structures::Vector w;
        double b = 0;
        double lr;

    public:
        BatchLinearRegression(const data_structures::Matrix &X, const data_structures::Vector &y, const double lr) : X(X), y(y), w(data_structures::Vector(X.shape().second)), lr(lr) {}
        BatchLinearRegression(const data_structures::Matrix &X, const data_structures::Vector &y) : X(X), y(y), w(data_structures::Vector(X.shape().second)), lr(0.01) {}

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
            while (true)
            {
                auto dw = w_cost();
                auto db = b_cost();

                data_structures::Vector dw_step = dw * lr;
                double db_step = db * lr;

                if (std::abs(db) < 0.001)
                    break;

                w = w - dw_step;
                b = b - db_step;
            }
        }

        data_structures::Vector w_cost() const
        {
            const std::pair<int, int> shape = X.shape();
            data_structures::Vector sum(shape.second);

            for (int i = 0; i < shape.first; i++)
            {
                data_structures::Vector row = X.get_row(i);
                double error = y.get(i) - predict(row);
                sum = (row * -2 * error) + sum;
            }

            return sum;
        }

        double b_cost() const
        {
            const std::pair<int, int> shape = X.shape();
            double sum = 0;
            for (int i = 0; i < shape.first; i++)
                sum += -2 * (y.get(i) - predict(X.get_row(i)));

            return sum;
        }

        double predict(const data_structures::Vector &x) const
        {
            return x.dot(w) + b;
        }
    };

    class StochasticLinearRegression
    {
    private:
        data_structures::Matrix X;
        data_structures::Vector y;
        data_structures::Vector w;
        double b = 0;
        double lr;

    public:
        StochasticLinearRegression(const data_structures::Matrix &X, const data_structures::Vector &y, const double lr) : X(X), y(y), w(data_structures::Vector(X.shape().second)), lr(lr) {}
        StochasticLinearRegression(const data_structures::Matrix &X, const data_structures::Vector &y) : X(X), y(y), w(data_structures::Vector(X.shape().second)), lr(0.01) {}

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
            for (size_t i = 0;; i++)
            {
                auto dw = w_cost(i % X.shape().first);
                auto db = b_cost(i % X.shape().first);

                data_structures::Vector dw_step = dw * lr;
                double db_step = db * lr;

                if (std::abs(db) < 0.001)
                    break;

                w = w - dw_step;
                b = b - db_step;
            }
        }

        data_structures::Vector w_cost(const size_t row_idx) const
        {
            const std::pair<int, int> shape = X.shape();
            data_structures::Vector sum(shape.second);
            sum.zeros();

            data_structures::Vector row = X.get_row(row_idx);
            double error = y.get(row_idx) - predict(row);
            sum = (row * -2 * error) + sum;

            return sum;
        }

        double b_cost(const size_t row_idx) const
        {
            double sum = 0;
            sum += -2 * (y.get(row_idx) - predict(X.get_row(row_idx)));
            return sum;
        }

        double predict(const data_structures::Vector &x) const
        {
            return x.dot(w) + b;
        }
    };

}

#endif // ALG_LIN_REG_H
