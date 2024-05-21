#ifndef FEATURES_ENCODING_H
#define FEATURES_ENCODING_H

#include <iostream>
#include <vector>
#include "../data_structures/vector.hpp"
#include "../data_structures/matrix.hpp"
#include <algorithm>
#include <string>

namespace features::encoding
{
    enum class Encoding
    {
        NUMERICAL,
        LABEL,
    };

    std::vector<double> parse_numerical_column(const std::vector<std::string> &column)
    {
        std::vector<double> transformed_column(column.size());
        for (size_t i = 0; i < column.size(); i++)
        {
            transformed_column[i] = std::stod(column[i]);
        }
        return transformed_column;
    }

    std::vector<double> parse_label_column(const std::vector<std::string> &column)
    {
        std::vector<double> transformed_column(column.size());
        std::vector<std::string> unique_values;
        for (size_t i = 0; i < column.size(); i++)
        {
            if (std::find(unique_values.begin(), unique_values.end(), column[i]) == unique_values.end())
            {
                unique_values.push_back(column[i]);
            }
        }

        for (size_t i = 0; i < column.size(); i++)
        {
            transformed_column[i] = std::distance(unique_values.begin(), std::find(unique_values.begin(), unique_values.end(), column[i]));
        }
        return transformed_column;
    }

    data_structures::Matrix<double> parse(const data_structures::Matrix<std::string> &mat, const std::vector<Encoding> &data_types)
    {
        auto [n_rows, n_cols] = mat.shape();
        data_structures::Matrix<double> transformed_matrix(n_rows, n_cols);

        for (size_t i = 0; i < n_cols; i++)
        {
            switch (data_types[i])
            {
            case Encoding::NUMERICAL:
                transformed_matrix.set_column(i, parse_numerical_column(mat.get_column(i).get_vector()));
                break;
            case Encoding::LABEL:
                transformed_matrix.set_column(i, parse_label_column(mat.get_column(i).get_vector()));
                break;
            default:
                break;
            }
        }

        return transformed_matrix;
    }
}

#endif // FEATURES_ENCODING_H
