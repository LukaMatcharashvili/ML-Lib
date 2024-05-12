#ifndef ALG_GRAD_DESC_H
#define ALG_GRAD_DESC_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

#include "../data_structures/matrix.hpp"
#include "../data_structures/vector.hpp"

namespace algorithms
{

    using t_predictionF = std::function<double(const data_structures::Vector &x, const data_structures::Vector &w, double b)>;

    using t_trainF = std::function<void(
        const data_structures::Matrix &X,
        const data_structures::Vector &y,
        data_structures::Vector &w,
        double &b,
        const double lr,
        const t_predictionF &predictF)>;

    namespace batch_gd
    {

        static std::pair<data_structures::Vector, double> cost(
            const data_structures::Matrix &X,
            const data_structures::Vector &y,
            const data_structures::Vector &w,
            const double b,
            const t_predictionF &predictF)
        {
            auto [n_rows, n_cols] = X.shape();
            data_structures::Vector w_sum(n_cols);
            double b_sum = 0;

            for (int i = 0; i < n_rows; i++)
            {
                auto row = X.get_row(i);
                double error = y.get(i) - predictF(row, w, b);

                w_sum = (row * -2 * error) + w_sum;
                b_sum += -2 * error;
            }

            return std::make_pair(w_sum, b_sum);
        }

        static void train(
            const data_structures::Matrix &X,
            const data_structures::Vector &y,
            data_structures::Vector &w,
            double &b,
            const double lr,
            const t_predictionF &predictF)
        {
            while (true)
            {
                auto [dw, db] = cost(X, y, w, b, predictF);

                auto dw_step = dw * lr;
                double db_step = db * lr;

                if (std::abs(db) < 0.001)
                    break;

                w = w - dw_step;
                b = b - db_step;
            }
        }
    };

    namespace stochastic_gd
    {
        static std::pair<data_structures::Vector, double> cost(
            const data_structures::Vector &row,
            const double &y,
            const data_structures::Vector &w,
            const double b,
            const t_predictionF &predictF)
        {
            data_structures::Vector w_sum(row.size());
            double b_sum = 0;

            double error = y - predictF(row, w, b);

            w_sum = (row * -2 * error) + w_sum;
            b_sum += -2 * error;

            return std::make_pair(w_sum, b_sum);
        }

        static void train(
            const data_structures::Matrix &X,
            const data_structures::Vector &y,
            data_structures::Vector &w,
            double &b,
            const double lr,
            const t_predictionF &predictF)
        {
            for (size_t i = 0;; i++)
            {
                int row_idx = i % X.shape().first;
                auto [dw, db] = cost(X.get_row(row_idx), y.get(row_idx), w, b, predictF);

                data_structures::Vector dw_step = dw * lr;
                double db_step = db * lr;

                if (std::abs(db) < 0.001)
                    break;

                w = w - dw_step;
                b = b - db_step;
            }
        }

    };

}

#endif // ALG_GRAD_DESC_H
