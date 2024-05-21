#ifndef DATA_STRUCTURES_VECTOR_H
#define DATA_STRUCTURES_VECTOR_H

#include <iostream>
#include <vector>

namespace data_structures
{

    template <typename T>
    class Vector
    {
    private:
        std::vector<T> vector_;

    public:
        ~Vector() = default;
        explicit Vector(const std::vector<T> &vector) : vector_(vector) {}
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
            for (T &element : result.vector_)
                element = 1;
            return result;
        }

        std::vector<T> get_vector() const
        {
            return vector_;
        }

        Vector operator+(const T scalar) const
        {
            Vector result(*this);
            for (size_t i = 0; i < result.size(); i++)
                result.vector_[i] += scalar;
            return result;
        }

        Vector operator+(Vector &other) const
        {
            Vector result(*this);
            for (size_t i = 0; i < result.size(); i++)
                result.vector_[i] += other.vector_[i];
            return result;
        }

        Vector operator-(const T scalar) const
        {
            Vector result(*this);
            for (size_t i = 0; i < result.size(); i++)
                result.vector_[i] -= scalar;
            return result;
        }

        Vector operator-(const Vector &other) const
        {
            Vector result(*this);
            for (size_t i = 0; i < result.size(); i++)
                result.vector_[i] -= other.vector_[i];
            return result;
        }

        Vector operator*(const T scalar) const
        {
            Vector result(*this);
            for (size_t i = 0; i < result.size(); i++)
                result.vector_[i] *= scalar;
            return result;
        }

        Vector operator*(const Vector &other) const
        {
            Vector result(*this);
            for (size_t i = 0; i < result.size(); i++)
                result.vector_[i] *= other.vector_[i];
            return result;
        }

        Vector operator/(const T scalar) const
        {
            Vector result(*this);
            for (size_t i = 0; i < result.size(); i++)
                result.vector_[i] /= scalar;
            return result;
        }

        Vector operator/(const Vector &other) const
        {
            Vector result(*this);
            for (size_t i = 0; i < result.size(); i++)
                result.vector_[i] /= other.vector_[i];
            return result;
        }

        size_t size() const
        {
            return vector_.size();
        }

        T sum() const
        {
            T sum = 0;
            for (const T &element : vector_)
                sum += element;
            return sum;
        }

        T get(const size_t i) const
        {
            return vector_[i];
        }

        void set(const size_t i, const T value)
        {
            vector_[i] = value;
        }

        T dot(const Vector &other) const
        {
            Vector result(*this);
            for (size_t i = 0; i < result.size(); i++)
                result.vector_[i] *= other.vector_[i];
            return result.sum();
        }

        void print() const
        {
            for (const T &element : vector_)
                std::cout << element << " ";
            std::cout << '\n';
        }
    };
}

#endif // DATA_STRUCTURES_VECTOR_H
