#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <vector>
#include <algorithm>

class Vector
{
private:
    std::vector<double> vector;

public:
    explicit Vector(const std::vector<double> &vector) : vector(vector) {}
    explicit Vector(size_t size)
    {
        vector.resize(size);
    }

    Vector operator+(const double scalar) const
    {
        Vector result(*this);
        std::transform(result.vector.begin(), result.vector.end(), result.vector.begin(), [scalar](double x)
                       { return x + scalar; });
        return result;
    }

    Vector operator+(Vector &other) const
    {
        Vector result(*this);
        std::transform(result.vector.begin(), result.vector.end(), other.vector.begin(), result.vector.begin(), std::plus<double>());
        return result;
    }

    Vector operator-(const double scalar) const
    {
        Vector result(*this);
        std::transform(result.vector.begin(), result.vector.end(), result.vector.begin(), [scalar](double x)
                       { return x - scalar; });
        return *this;
    }

    Vector operator-(const Vector &other) const
    {
        Vector result(*this);
        std::transform(result.vector.begin(), result.vector.end(), other.vector.begin(), result.vector.begin(), std::minus<double>());
        return result;
    }

    Vector operator*(const double scalar) const
    {
        Vector result(*this);
        std::transform(result.vector.begin(), result.vector.end(), result.vector.begin(), [scalar](double x)
                       { return x * scalar; });
        return *this;
    }

    Vector operator*(const Vector &other) const
    {
        Vector result(*this);
        std::transform(result.vector.begin(), result.vector.end(), other.vector.begin(), result.vector.begin(), std::multiplies<double>());
        return result;
    }

    Vector operator/(const double scalar) const
    {
        Vector result(*this);
        std::transform(result.vector.begin(), result.vector.end(), result.vector.begin(), [scalar](double x)
                       { return x / scalar; });
        return *this;
    }

    Vector operator/(const Vector &other) const
    {
        Vector result(*this);
        std::transform(result.vector.begin(), result.vector.end(), other.vector.begin(), result.vector.begin(), std::divides<double>());
        return result;
    }

    size_t size() const
    {
        return vector.size();
    }

    void zeros()
    {
        std::fill(vector.begin(), vector.end(), 0);
    }

    double sum() const
    {
        double sum = 0;
        for (const double &element : vector)
        {
            sum += element;
        }

        return sum;
    }

    double get(const size_t i) const
    {
        return vector[i];
    }

    double dot(const Vector &other) const
    {
        Vector result(*this);
        std::transform(result.vector.begin(), result.vector.end(), other.vector.begin(), result.vector.begin(), std::multiplies<double>());
        return result.sum();
    }

    void print() const
    {
        for (const double &element : vector)
        {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
};

#endif // VECTOR_HPP
