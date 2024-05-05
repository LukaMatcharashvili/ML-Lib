#ifndef FEATURES_POLY_H
#define FEATURES_POLY_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "../data_structures/vector.hpp"
#include "../data_structures/matrix.hpp"

#include <cmath>

namespace features
{
    namespace poly
    {
        data_structures::Matrix transform(const data_structures::Matrix &X, const int degree)
        {
            std::pair<int, int> shape = X.shape();
            data_structures::Matrix transformed_matrix(shape.first, shape.second);

            for (int i = 0; i < shape.first; i++)
            {
                std::vector<double> new_row = {1};
                std::vector<double> curr_row = X.get_row(i).get_vector();

                for (int j = 1; j <= degree; j++)
                    new_row.push_back(std::pow(curr_row[0], j));

                for (double val : curr_row)
                    for (int j = 1; j <= shape.second; j++)
                        new_row.push_back(std::pow(val, curr_row[j]));

                transformed_matrix.set_row(i, data_structures::Vector(new_row));
            }

            return transformed_matrix;
        }
    }
}

#endif // FEATURES_POLY_H
