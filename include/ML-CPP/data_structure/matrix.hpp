#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include "vector.hpp"

class Matrix
{
private:
    std::vector<std::vector<double>> matrix;
    size_t rows;
    size_t cols;

public:
    explicit Matrix(const std::vector<std::vector<double>> &matrix) : matrix(matrix), rows(matrix.size()), cols(matrix[0].size()) {}

    explicit Matrix(size_t rows, size_t cols) : rows(rows), cols(cols)
    {
        matrix.resize(rows);
        for (std::vector<double> &row : matrix)
        {
            row.resize(cols);
        }
    }

    Matrix operator+(const double scalar) const
    {
        Matrix result(*this);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                result.matrix[i][j] += scalar;
            }
        }
        return result;
    }

    Matrix operator+(const Matrix &other) const
    {
        Matrix result(*this);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                result.matrix[i][j] += other.matrix[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const double scalar) const
    {
        Matrix result(*this);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                result.matrix[i][j] -= scalar;
            }
        }
        return result;
    }

    Matrix operator-(const Matrix &other) const
    {
        Matrix result(*this);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                result.matrix[i][j] -= other.matrix[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const double scalar) const
    {
        Matrix result(*this);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                result.matrix[i][j] *= scalar;
            }
        }
        return result;
    }

    Matrix operator*(const Matrix &other) const
    {
        Matrix result(*this);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                result.matrix[i][j] *= other.matrix[i][j];
            }
        }
        return result;
    }

    Matrix operator/(const double scalar) const
    {
        Matrix result(*this);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                result.matrix[i][j] /= scalar;
            }
        }
        return result;
    }

    Matrix operator/(const Matrix &other) const
    {
        Matrix result(*this);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                result.matrix[i][j] /= other.matrix[i][j];
            }
        }
        return result;
    }

    Matrix multiply(const Matrix &other) const
    {
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) // TODO: Parallelize this loop
            for (int k = 0; k < cols; k++)
                for (int j = 0; j < other.cols; j++)
                    result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
        return result;
    }

    Matrix transpose() const
    {
        Matrix result(*this);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                result.matrix[j][i] = matrix[i][j];
            }
        }
        return result;
    }

    void print() const
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    std::pair<int, int> shape() const
    {
        return std::make_pair(rows, cols);
    }

    Vector get_row(const size_t i) const
    {
        return Vector(matrix[i]);
    }

    Vector get_col(const size_t i) const
    {
        std::vector<double> col;
        for (int j = 0; j < rows; j++)
        {
            col.push_back(matrix[j][i]);
        }
        return Vector(col);
    }

    double get_value(const size_t i, const size_t j) const
    {
        return matrix[i][j];
    }

    void set_value(const size_t i, const size_t j, const double value)
    {
        matrix[i][j] = value;
    }

    void add_row(const std::vector<double> &v)
    {
        matrix.push_back(v);
    }

    void set_shape(const size_t nrows, const size_t ncols)
    {
        this->rows = nrows;
        this->cols = ncols;
    }

    Matrix sub_matrix(const size_t row_start, const size_t row_end, const size_t col_start, const size_t col_end) const
    {
        Matrix result(row_end - row_start, col_end - col_start);
        for (size_t i = row_start; i < row_end; i++)
        {
            for (size_t j = col_start; j < col_end; j++)
            {
                result.matrix[i - row_start][j - col_start] = matrix[i][j];
            }
        }
        return result;
    }

    void set_row(const size_t i, const Vector &v)
    {
        matrix[i] = v.get_vector();
    }
};

#endif // MATRIX_HPP