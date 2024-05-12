#ifndef DATA_STRUCTURES_VECTOR_H
#define DATA_STRUCTURES_VECTOR_H

#include <iostream>
#include <vector>

namespace data_structures
{
    class Vector
    {
    private:
        std::vector<double> vector_;

    public:
        ~Vector() = default;
        explicit Vector(const std::vector<double> &vector) : vector_(vector) {}
        explicit Vector(size_t size)
        {
            // Initialize vector_ with zeros
            vector_.resize(size);
        }

        static inline Vector zeros(size_t size)
        {
            return Vector(size);
        }

        static inline Vector ones(size_t size)
        {
            Vector result(size);
            for (double &element : result.vector_)
                element = 1;
            return result;
        }

        std::vector<double> get_vector() const
        {
            return vector_;
        }

        Vector operator+(const double scalar) const
        {
            Vector result(*this);
            for (int i = 0; i < result.size(); i++)
                result.vector_[i] += scalar;
            return result;
        }

        Vector operator+(Vector &other) const
        {
            Vector result(*this);
            for (int i = 0; i < result.size(); i++)
                result.vector_[i] += other.vector_[i];
            return result;
        }

        Vector operator-(const double scalar) const
        {
            Vector result(*this);
            for (int i = 0; i < result.size(); i++)
                result.vector_[i] -= scalar;
            return result;
        }

        Vector operator-(const Vector &other) const
        {
            Vector result(*this);
            for (int i = 0; i < result.size(); i++)
                result.vector_[i] -= other.vector_[i];
            return result;
        }

        Vector operator*(const double scalar) const
        {
            Vector result(*this);
            for (int i = 0; i < result.size(); i++)
                result.vector_[i] *= scalar;
            return result;
        }

        Vector operator*(const Vector &other) const
        {
            Vector result(*this);
            for (int i = 0; i < result.size(); i++)
                result.vector_[i] *= other.vector_[i];
            return result;
        }

        Vector operator/(const double scalar) const
        {
            Vector result(*this);
            for (int i = 0; i < result.size(); i++)
                result.vector_[i] /= scalar;
            return result;
        }

        Vector operator/(const Vector &other) const
        {
            Vector result(*this);
            for (int i = 0; i < result.size(); i++)
                result.vector_[i] /= other.vector_[i];
            return result;
        }

        size_t size() const
        {
            return vector_.size();
        }

        double sum() const
        {
            double sum = 0;
            for (const double &element : vector_)
                sum += element;
            return sum;
        }

        double get(const size_t i) const
        {
            return vector_[i];
        }

        void set(const size_t i, const double value)
        {
            vector_[i] = value;
        }

        double dot(const Vector &other) const
        {
            Vector result(*this);
            for (int i = 0; i < result.size(); i++)
                result.vector_[i] *= other.vector_[i];
            return result.sum();
        }

        void print() const
        {
            for (const double &element : vector_)
                std::cout << element << " ";
            std::cout << '\n';
        }
    };
}

#endif // DATA_STRUCTURES_VECTOR_H
