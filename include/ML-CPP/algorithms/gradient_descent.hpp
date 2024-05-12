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
        const data_structures::Matrix &x,
        const data_structures::Vector &y,
        data_structures::Vector &w,
        double &b,
        const double lr,
        const t_predictionF &predictF)>;

    namespace batch_gd
    {

        static std::pair<data_structures::Vector, double> cost(
            const data_structures::Matrix &x,
            const data_structures::Vector &y,
            const data_structures::Vector &w,
            const double b,
            const t_predictionF &predictF)
        {
            auto [n_rows, n_cols] = x.shape();
            data_structures::Vector w_sum(n_cols);
            double b_sum = 0;

            for (int i = 0; i < n_rows; i++)
            {
                auto row = x.get_row(i);
                double error = y.get(i) - predictF(row, w, b);

                w_sum = (row * -2 * error) + w_sum;
                b_sum += -2 * error;
            }

            return std::make_pair(w_sum, b_sum);
        }

        static void train(
            const data_structures::Matrix &x,
            const data_structures::Vector &y,
            data_structures::Vector &w,
            double &b,
            const double lr,
            const t_predictionF &predictF)
        {
            while (true)
            {
                auto [dw, db] = cost(x, y, w, b, predictF);

                auto dw_step = dw * lr;
                double db_step = db * lr;

                std::cout << " Cost: " << db << '\n';
                if (std::abs(db_step) < 0.001)
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
            const data_structures::Matrix &x,
            const data_structures::Vector &y,
            data_structures::Vector &w,
            double &b,
            const double lr,
            const t_predictionF &predictF)
        {
            for (size_t i = 0;; i++)
            {
                int random_row = rand() % x.shape().first;
                auto [dw, db] = cost(x.get_row(random_row), y.get(random_row), w, b, predictF);

                data_structures::Vector dw_step = dw * lr;
                double db_step = db * lr;

                if (std::abs(db_step) < 0.001)
                    break;

                w = w - dw_step;
                b = b - db_step;
            }
        }
    };

    namespace mini_batch_gd
    {
        static std::pair<data_structures::Vector, double> cost(
            const data_structures::Matrix &x,
            const data_structures::Vector &y,
            const data_structures::Vector &w,
            const double b,
            const t_predictionF &predictF)
        {
            auto [n_rows, n_cols] = x.shape();
            data_structures::Vector w_sum(n_cols);
            double b_sum = 0;

            for (int i = 0; i < n_rows; i++)
            {
                auto row = x.get_row(i);
                double error = y.get(i) - predictF(row, w, b);

                w_sum = (row * -2 * error) + w_sum;
                b_sum += -2 * error;
            }

            return std::make_pair(w_sum, b_sum);
        }

        static void train(
            const data_structures::Matrix &x,
            const data_structures::Vector &y,
            data_structures::Vector &w,
            double &b,
            const double lr,
            const t_predictionF &predictF)
        {
            size_t batch_size = x.shape().first / 10;
            batch_size = batch_size <= 0 ? 1 : batch_size;

            while (true)
            {
                data_structures::Matrix random_rows_matrix(batch_size, x.shape().second);
                for (size_t j = 0; j < batch_size; j++)
                    random_rows_matrix.set_row(j, x.get_row(rand() % x.shape().first));

                auto [dw, db] = cost(random_rows_matrix, y, w, b, predictF);

                data_structures::Vector dw_step = dw * lr;
                double db_step = db * lr;

                std::cout << " Cost: " << db << '\n';
                if (std::abs(db_step) < 0.001)
                    break;

                w = w - dw_step;
                b = b - db_step;
            }
        }

    };
}
#endif // ALG_GRAD_DESC_H
