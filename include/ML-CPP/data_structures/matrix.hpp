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
        std::vector<double> matrix;
        size_t rows;
        size_t cols;

    public:
        explicit Matrix(size_t rows, size_t cols) : rows(rows), cols(cols)
        {
            matrix.resize(rows * cols);
        }

        Matrix operator+(const double scalar) const
        {
            Matrix result(*this);
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    result.matrix[i * cols + j] += scalar;
            return result;
        }

        Matrix operator+(const Matrix &other) const
        {
            Matrix result(*this);
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    result.matrix[i * cols + j] += other.matrix[i * cols + j];
            return result;
        }

        Matrix operator-(const double scalar) const
        {
            Matrix result(*this);
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    result.matrix[i * cols + j] -= scalar;
            return result;
        }

        Matrix operator-(const Matrix &other) const
        {
            Matrix result(*this);
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    result.matrix[i * cols + j] -= other.matrix[i * cols + j];
            return result;
        }

        Matrix operator*(const double scalar) const
        {
            Matrix result(*this);
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    result.matrix[i * cols + j] *= scalar;
            return result;
        }

        Matrix operator*(const Matrix &other) const
        {
            Matrix result(*this);
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    result.matrix[i * cols + j] *= other.matrix[i * cols + j];
            return result;
        }

        Matrix operator/(const double scalar) const
        {
            Matrix result(*this);
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    result.matrix[i * cols + j] /= scalar;
            return result;
        }

        Matrix operator/(const Matrix &other) const
        {
            Matrix result(*this);
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    result.matrix[i * cols + j] /= other.matrix[i * cols + j];
            return result;
        }

        Matrix multiply(const Matrix &other) const
        {
            Matrix result(rows, other.cols);
            for (int i = 0; i < rows; i++)
                for (int k = 0; k < cols; k++)
                    for (int j = 0; j < other.cols; j++)
                        result.matrix[i * other.cols + j] += matrix[i * cols + k] * other.matrix[k * other.cols + j];
            return result;
        }

        Matrix transpose() const
        {
            Matrix result(*this);
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    result.matrix[j * rows + i] = matrix[i * cols + j];
            return result;
        }

        void print() const
        {
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    std::cout << matrix[i * cols + j] << " ";
        }

        std::pair<int, int> shape() const
        {
            return std::make_pair(rows, cols);
        }

        data_structures::Vector get_row(const size_t i) const
        {
            std::vector<double> row(rows);
            for (int j = 0; j < cols; j++)
                row[j] = matrix[i * cols + j];
            return data_structures::Vector(row);
        }

        data_structures::Vector get_col(const size_t i) const
        {
            std::vector<double> col;
            for (int j = 0; j < rows; j++)
                col.push_back(matrix[j * cols + i]);
            return data_structures::Vector(col);
        }

        double get_value(const size_t i, const size_t j) const
        {
            return matrix[i * cols + j];
        }

        void set_value(const size_t i, const size_t j, const double value)
        {
            matrix[i * cols + j] = value;
        }

        void add_row(const std::vector<double> &v)
        {
            for (double value : v)
                matrix.push_back(value);
        }

        void set_shape(const size_t n_rows, const size_t n_cols)
        {
            this->rows = n_rows;
            this->cols = n_cols;
        }

        Matrix sub_matrix(const size_t row_start, const size_t row_end, const size_t col_start, const size_t col_end) const
        {
            Matrix result(row_end - row_start, col_end - col_start);
            for (size_t i = row_start; i < row_end; i++)
            {
                for (size_t j = col_start; j < col_end; j++)
                {
                    result.matrix[(i - row_start) * (col_end - col_start) + (j - col_start)] = matrix[i * cols + j];
                }
            }
            return result;
        }

        void set_row(const size_t i, const data_structures::Vector &v)
        {
            for (int j = 0; j < cols; j++)
                matrix[i * cols + j] = v.get(j);
        }
    };
}

#endif // DATA_STRUCTURES_MATRIX_H
