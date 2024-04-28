#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include "vector.hpp"

class Matrix
{
private:
    std::vector<std::vector<float>> matrix;
    size_t rows;
    size_t cols;

public:
    explicit Matrix(const std::vector<std::vector<float>> &matrix) : matrix(matrix), rows(matrix.size()), cols(matrix[0].size()) {}

    explicit Matrix(size_t rows, size_t cols) : rows(rows), cols(cols)
    {
        matrix.resize(rows);
        for (std::vector<float> &row : matrix)
        {
            row.resize(cols);
        }
    }

    Matrix operator+(const float scalar) const
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

    Matrix operator-(const float scalar) const
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

    Matrix operator*(const float scalar) const
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

    Matrix operator/(const float scalar) const
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
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < other.cols; j++)
            {
                for (int k = 0; k < cols; k++)
                {
                    result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
                }
            }
        }
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

    Vector getRow(const size_t i) const
    {
        return Vector(matrix[i]);
    }

    Vector getCol(const size_t i) const
    {
        std::vector<float> col;
        for (int j = 0; j < rows; j++)
        {
            col.push_back(matrix[j][i]);
        }
        return Vector(col);
    }
};

#endif // MATRIX_HPP