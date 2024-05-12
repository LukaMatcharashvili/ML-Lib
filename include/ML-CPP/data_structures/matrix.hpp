#ifndef DATA_STRUCTURES_MATRIX_H
#define DATA_STRUCTURES_MATRIX_H

#include <iostream>
#include <vector>
#include "vector.hpp"

namespace data_structures
{
    class Matrix
    {
    private:
        std::vector<double> matrix_;
        size_t rows_;
        size_t cols_;

    public:
        ~Matrix() = default;
        explicit Matrix(const size_t rows, const size_t cols) : rows_(rows), cols_(cols)
        {
            // Initialize matrix with zeros
            matrix_.resize(rows_ * cols_);
        }
        explicit Matrix(const std::vector<double> &matrix, size_t rows, size_t cols) : matrix_(matrix), rows_(rows), cols_(cols) {}
        explicit Matrix(std::vector<std::vector<double>> matrix) : rows_(matrix_.size()), cols_(matrix[0].size())
        {
            matrix_.reserve(rows_ * cols_);
            for (const std::vector<double> &row : matrix)
                for (double value : row)
                    this->matrix_.push_back(value);
        }

        static Matrix zeros(const size_t rows, const size_t cols)
        {
            return Matrix(rows, cols);
        }

        static Matrix ones(const size_t rows, const size_t cols)
        {
            Matrix result(rows, cols);
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    result.matrix_[i * cols + j] = 1;
            return result;
        }

        Matrix operator+(const double scalar) const
        {
            Matrix result(*this);
            for (int i = 0; i < rows_; i++)
                for (int j = 0; j < cols_; j++)
                    result.matrix_[i * cols_ + j] += scalar;
            return result;
        }

        Matrix operator+(const Matrix &other) const
        {
            Matrix result(*this);
            for (int i = 0; i < rows_; i++)
                for (int j = 0; j < cols_; j++)
                    result.matrix_[i * cols_ + j] += other.matrix_[i * cols_ + j];
            return result;
        }

        Matrix operator-(const double scalar) const
        {
            Matrix result(*this);
            for (int i = 0; i < rows_; i++)
                for (int j = 0; j < cols_; j++)
                    result.matrix_[i * cols_ + j] -= scalar;
            return result;
        }

        Matrix operator-(const Matrix &other) const
        {
            Matrix result(*this);
            for (int i = 0; i < rows_; i++)
                for (int j = 0; j < cols_; j++)
                    result.matrix_[i * cols_ + j] -= other.matrix_[i * cols_ + j];
            return result;
        }

        Matrix operator*(const double scalar) const
        {
            Matrix result(*this);
            for (int i = 0; i < rows_; i++)
                for (int j = 0; j < cols_; j++)
                    result.matrix_[i * cols_ + j] *= scalar;
            return result;
        }

        Matrix operator*(const Matrix &other) const
        {
            Matrix result(*this);
            for (int i = 0; i < rows_; i++)
                for (int j = 0; j < cols_; j++)
                    result.matrix_[i * cols_ + j] *= other.matrix_[i * cols_ + j];
            return result;
        }

        Matrix operator/(const double scalar) const
        {
            Matrix result(*this);
            for (int i = 0; i < rows_; i++)
                for (int j = 0; j < cols_; j++)
                    result.matrix_[i * cols_ + j] /= scalar;
            return result;
        }

        Matrix operator/(const Matrix &other) const
        {
            Matrix result(*this);
            for (int i = 0; i < rows_; i++)
                for (int j = 0; j < cols_; j++)
                    result.matrix_[i * cols_ + j] /= other.matrix_[i * cols_ + j];
            return result;
        }

        Matrix multiply(const Matrix &other) const
        {
            Matrix result(rows_, other.cols_);
            for (int i = 0; i < rows_; i++)
                for (int k = 0; k < cols_; k++)
                    for (int j = 0; j < other.cols_; j++)
                        result.matrix_[i * other.cols_ + j] += matrix_[i * cols_ + k] * other.matrix_[k * other.cols_ + j];
            return result;
        }

        Matrix transpose() const
        {
            Matrix result(*this);
            for (int i = 0; i < rows_; i++)
                for (int j = 0; j < cols_; j++)
                    result.matrix_[j * rows_ + i] = matrix_[i * cols_ + j];
            return result;
        }

        void print() const
        {
            for (int i = 0; i < rows_; i++)
                for (int j = 0; j < cols_; j++)
                    std::cout << matrix_[i * cols_ + j] << " ";
        }

        std::pair<int, int> shape() const
        {
            return std::make_pair(rows_, cols_);
        }

        data_structures::Vector get_row(const size_t i) const
        {
            std::vector<double> row(rows_);
            for (int j = 0; j < cols_; j++)
                row[j] = matrix_[i * cols_ + j];
            return data_structures::Vector(row);
        }

        data_structures::Vector get_col(const size_t i) const
        {
            std::vector<double> col;
            for (int j = 0; j < rows_; j++)
                col.push_back(matrix_[j * cols_ + i]);
            return data_structures::Vector(col);
        }

        double get_value(const size_t i, const size_t j) const
        {
            return matrix_[i * cols_ + j];
        }

        void set_value(const size_t i, const size_t j, const double value)
        {
            matrix_[i * cols_ + j] = value;
        }

        void add_row(const std::vector<double> &v)
        {
            for (double value : v)
                matrix_.push_back(value);
        }

        void set_shape(const size_t n_rows, const size_t n_cols)
        {
            this->rows_ = n_rows;
            this->cols_ = n_cols;
        }

        Matrix sub_matrix(const size_t row_start, const size_t row_end, const size_t col_start, const size_t col_end) const
        {
            Matrix result(row_end - row_start, col_end - col_start);
            for (size_t i = row_start; i < row_end; i++)
                for (size_t j = col_start; j < col_end; j++)
                    result.matrix_[(i - row_start) * (col_end - col_start) + (j - col_start)] = matrix_[i * cols_ + j];
            return result;
        }

        void set_row(const size_t i, const data_structures::Vector &v)
        {
            for (int j = 0; j < cols_; j++)
                matrix_[i * cols_ + j] = v.get(j);
        }
    };
}

#endif // DATA_STRUCTURES_MATRIX_H
