#ifndef FEATURES_SCALING_H
#define FEATURES_SCALING_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "../data_structures/matrix.hpp"
#include "../data_structures/vector.hpp"

namespace features
{
    enum class ScalingType
    {
        min_max,
        max_abs,
    };

    class Scaling
    {
    private:
        ScalingType scaling_type;
        std::vector<double> min_values;
        std::vector<double> max_values;
        std::vector<double> mean_values;

        void set_min_max_scaling_parameters(const data_structures::Matrix &mat)
        {
            std::pair<size_t, size_t> shape = mat.shape();
            min_values = std::vector<double>(shape.second, 0);
            max_values = std::vector<double>(shape.second, 0);

            for (size_t i = 0; i < shape.first; i++)
                for (size_t j = 0; j < shape.second; j++)
                {
                    min_values[j] = std::min(min_values[j], mat.get_value(i, j));
                    max_values[j] = std::max(max_values[j], mat.get_value(i, j));
                }
        };

        void set_max_abs_scaling_parameters(const data_structures::Matrix &mat)
        {
            std::pair<size_t, size_t> shape = mat.shape();
            max_values = std::vector<double>(shape.second, 0);

            for (size_t i = 0; i < shape.first; i++)
                for (size_t j = 0; j < shape.second; j++)
                    max_values[j] = std::max(max_values[j], mat.get_value(i, j));
        };

        data_structures::Matrix min_max_scaling(const data_structures::Matrix &mat, const size_t start, const size_t end)
        {
            std::pair<size_t, size_t> shape = mat.shape();

            data_structures::Matrix result(shape.first, end - start);
            for (size_t i = 0; i < shape.first; i++)
                for (size_t j = start; j < end; j++)
                    result.set_value(i, j, (mat.get_value(i, j) - min_values[j]) / (max_values[j] - min_values[j]));

            return result;
        };

        data_structures::Matrix max_abs_scaling(const data_structures::Matrix &mat, const size_t start, const size_t end)
        {
            std::pair<size_t, size_t> shape = mat.shape();

            data_structures::Matrix result(shape.first, end - start);
            for (size_t i = 0; i < shape.first; i++)
                for (size_t j = start; j < end; j++)
                    result.set_value(i, j, mat.get_value(i, j) / max_values[j]);

            return result;
        };

    public:
        explicit Scaling(const data_structures::Matrix &mat, ScalingType scaling_type = ScalingType::max_abs) : scaling_type(scaling_type)
        {
            switch (scaling_type)
            {
            case ScalingType::min_max:
                set_min_max_scaling_parameters(mat);
                break;
            case ScalingType::max_abs:
                set_max_abs_scaling_parameters(mat);
                break;
            }
        }

        data_structures::Matrix scale(const data_structures::Matrix &mat, size_t start, size_t end)
        {
            switch (scaling_type)
            {
            case ScalingType::min_max:
                return min_max_scaling(mat, start, end);
            case ScalingType::max_abs:
                return max_abs_scaling(mat, start, end);
            }
        }

        data_structures::Matrix scale(const data_structures::Matrix &mat)
        {
            size_t n_cols = mat.shape().second;
            switch (scaling_type)
            {
            case ScalingType::min_max:
                return min_max_scaling(mat, 0, n_cols);
            case ScalingType::max_abs:
                return max_abs_scaling(mat, 0, n_cols);
            default:
                exit(1);
            }
        }

        data_structures::Vector scale(const data_structures::Vector &vec, size_t start, size_t end)
        {
            switch (scaling_type)
            {
            case ScalingType::min_max:
            {
                data_structures::Vector result(end - start);
                for (size_t i = start; i < end; i++)
                    result.set(i, (vec.get(i) - min_values[i]) / (max_values[i] - min_values[i]));
                return result;
            }
            case ScalingType::max_abs:
            {
                data_structures::Vector result(end - start);
                for (size_t i = start; i < end; i++)
                    result.set(i, vec.get(i) / max_values[i]);
                return result;
            }
            }
        }

        data_structures::Vector scale(const data_structures::Vector &vec)
        {
            size_t n_cols = vec.size();
            switch (scaling_type)
            {
            case ScalingType::min_max:
            {
                data_structures::Vector result(n_cols);
                for (size_t i = 0; i < n_cols; i++)
                    result.set(i, (vec.get(i) - min_values[i]) / (max_values[i] - min_values[i]));
                return result;
            }
            case ScalingType::max_abs:
            {
                data_structures::Vector result(n_cols);
                for (size_t i = 0; i < n_cols; i++)
                    result.set(i, vec.get(i) / max_values[i]);
                return result;
            }
            default:
                exit(1);
            }
        }

        double reverse_scale(const double value, size_t i)
        {
            switch (scaling_type)
            {
            case ScalingType::min_max:
                return value * (max_values[i] - min_values[i]) + min_values[i];
            case ScalingType::max_abs:
                return value * max_values[i];
            default:
                exit(1);
            }
        }
    };
}

#endif // FEATURES_SCALING_H
