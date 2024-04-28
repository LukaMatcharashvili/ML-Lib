#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <vector>
#include <algorithm>

class Vector
{
private:
    std::vector<float> vector;

public:
    explicit Vector(const std::vector<float> &vector) : vector(vector) {}
    explicit Vector(size_t size)
    {
        vector.resize(size);
    }

    Vector operator+(const float scalar) const
    {
        Vector result(*this);
        std::transform(result.vector.begin(), result.vector.end(), result.vector.begin(), [scalar](float x)
                       { return x + scalar; });
        return result;
    }

    Vector operator+(Vector &other) const
    {
        Vector result(*this);
        std::transform(result.vector.begin(), result.vector.end(), other.vector.begin(), result.vector.begin(), std::plus<float>());
        return result;
    }

    Vector operator-(const float scalar) const
    {
        Vector result(*this);
        std::transform(result.vector.begin(), result.vector.end(), result.vector.begin(), [scalar](float x)
                       { return x - scalar; });
        return *this;
    }

    Vector operator-(const Vector &other) const
    {
        Vector result(*this);
        std::transform(result.vector.begin(), result.vector.end(), other.vector.begin(), result.vector.begin(), std::minus<float>());
        return result;
    }

    Vector operator*(const float scalar) const
    {
        Vector result(*this);
        std::transform(result.vector.begin(), result.vector.end(), result.vector.begin(), [scalar](float x)
                       { return x * scalar; });
        return *this;
    }

    Vector operator*(const Vector &other) const
    {
        Vector result(*this);
        std::transform(result.vector.begin(), result.vector.end(), other.vector.begin(), result.vector.begin(), std::multiplies<float>());
        return result;
    }

    Vector operator/(const float scalar) const
    {
        Vector result(*this);
        std::transform(result.vector.begin(), result.vector.end(), result.vector.begin(), [scalar](float x)
                       { return x / scalar; });
        return *this;
    }

    Vector operator/(const Vector &other) const
    {
        Vector result(*this);
        std::transform(result.vector.begin(), result.vector.end(), other.vector.begin(), result.vector.begin(), std::divides<float>());
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

    float sum() const
    {
        float sum = 0;
        for (const float &element : vector)
        {
            sum += element;
        }

        return sum;
    }

    float get(const size_t i) const
    {
        return vector[i];
    }

    float dot(const Vector &other) const
    {
        Vector result(*this);
        std::transform(result.vector.begin(), result.vector.end(), other.vector.begin(), result.vector.begin(), std::multiplies<float>());
        return result.sum();
    }

    void print() const
    {
        for (const float &element : vector)
        {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
};

#endif // VECTOR_HPP
