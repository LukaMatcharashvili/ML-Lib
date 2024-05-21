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

    class AbstractScaler
    {
    public:
        virtual data_structures::Matrix<double> scale(const data_structures::Matrix<double> &mat) = 0;
        virtual data_structures::Vector<double> scale(const data_structures::Vector<double> &vec) = 0;
        virtual double reverse_scale(const double value, size_t i) = 0;

        virtual ~AbstractScaler() = default;
    };

    class MinMaxScaler : public AbstractScaler
    {
    private:
        std::vector<double> min_values_;
        std::vector<double> max_values_;

        void set_scaling_parameters(const data_structures::Matrix<double> &mat)
        {
            auto [n_rows, n_cols] = mat.shape();
            min_values_ = std::vector<double>(n_cols, 0);
            max_values_ = std::vector<double>(n_cols, 0);

            for (size_t i = 0; i < n_rows; i++)
                for (size_t j = 0; j < n_cols; j++)
                {
                    min_values_[j] = std::min(min_values_[j], mat.get_value(i, j));
                    max_values_[j] = std::max(max_values_[j], mat.get_value(i, j));
                }
        };

    public:
        ~MinMaxScaler() override = default;
        explicit MinMaxScaler(const data_structures::Matrix<double> &mat)
        {
            set_scaling_parameters(mat);
        }

        data_structures::Matrix<double> scale(const data_structures::Matrix<double> &mat) override
        {
            auto [n_rows, n_cols] = mat.shape();

            data_structures::Matrix<double> result(n_rows, n_cols);
            for (size_t i = 0; i < n_rows; i++)
                for (size_t j = 0; j < n_cols; j++)
                    result.set_value(i, j, (mat.get_value(i, j) - min_values_[j]) / (max_values_[j] - min_values_[j]));

            return result;
        }

        data_structures::Vector<double> scale(const data_structures::Vector<double> &vec) override
        {
            size_t n_cols = vec.size();
            data_structures::Vector<double> result(n_cols);
            for (size_t i = 0; i < n_cols; i++)
                result.set(i, (vec.get(i) - min_values_[i]) / (max_values_[i] - min_values_[i]));
            return result;
        }

        double reverse_scale(const double value, size_t i) override
        {
            return value * (max_values_[i] - min_values_[i]) + min_values_[i];
        }
    };

    class MaxAbsScaler : public AbstractScaler
    {
    private:
        std::vector<double> max_values_;

        void set_scaling_parameters(const data_structures::Matrix<double> &mat)
        {
            auto [n_rows, n_cols] = mat.shape();
            max_values_ = std::vector<double>(n_cols, 0);

            for (size_t i = 0; i < n_rows; i++)
                for (size_t j = 0; j < n_cols; j++)
                    max_values_[j] = std::max(max_values_[j], mat.get_value(i, j));
        };

    public:
        ~MaxAbsScaler() override = default;
        explicit MaxAbsScaler(const data_structures::Matrix<double> &mat)
        {
            set_scaling_parameters(mat);
        }

        data_structures::Matrix<double> scale(const data_structures::Matrix<double> &mat) override
        {
            auto [n_rows, n_cols] = mat.shape();

            data_structures::Matrix<double> result(n_rows, n_cols);
            for (size_t i = 0; i < n_rows; i++)
                for (size_t j = 0; j < n_cols; j++)
                    result.set_value(i, j, mat.get_value(i, j) / max_values_[j]);

            return result;
        }

        data_structures::Vector<double> scale(const data_structures::Vector<double> &vec) override
        {
            size_t n_cols = vec.size();
            data_structures::Vector<double> result(n_cols);
            for (size_t i = 0; i < n_cols; i++)
                result.set(i, vec.get(i) / max_values_[i]);
            return result;
        }

        double reverse_scale(const double value, size_t i) override
        {
            return value * max_values_[i];
        }
    };

}

#endif // FEATURES_SCALING_H
