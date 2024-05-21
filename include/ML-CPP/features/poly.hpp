#ifndef FEATURES_POLY_H
#define FEATURES_POLY_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "../data_structures/vector.hpp"
#include "../data_structures/matrix.hpp"

#include <cmath>

namespace features::poly
{
    data_structures::Matrix<double> transform(const data_structures::Matrix<double> &x, const int degree)
    {
        auto [n_rows, n_cols] = x.shape();
        data_structures::Matrix<double> transformed_matrix(n_rows, n_cols);

        for (size_t i = 0; i < n_rows; i++)
        {
            std::vector<double> new_row = {1};
            std::vector<double> curr_row = x.get_row(i).get_vector();

            for (size_t j = 1; j <= degree; j++)
                new_row.push_back(std::pow(curr_row[0], j));

            for (double val : curr_row)
                for (size_t j = 1; j <= n_cols; j++)
                    new_row.push_back(std::pow(val, curr_row[j]));

            transformed_matrix.set_row(i, data_structures::Vector<double>(new_row));
        }

        return transformed_matrix;
    }
}

#endif // FEATURES_POLY_H
