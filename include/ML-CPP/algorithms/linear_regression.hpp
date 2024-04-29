#include <iostream>
#include <vector>
#include <algorithm>

#include "../data_structure/matrix.hpp"
#include "../data_structure/vector.hpp"

class LinearRegression
{
private:
    Matrix X;
    Vector y;
    Vector w;
    size_t epochs;
    double b = 0;
    double lr;

public:
    LinearRegression(const Matrix &X, const Vector &y, const size_t epochs, const double lr) : X(X), y(y), w(Vector(X.shape().second)), epochs(epochs), lr(lr) {}
    LinearRegression(const Matrix &X, const Vector &y, const size_t epochs) : X(X), y(y), w(Vector(X.shape().second)), epochs(epochs), lr(0.01) {}

    void print_weights() const
    {
        w.print();
        std::cout << "b: " << b << std::endl;
    }

    void train()
    {
        for (size_t i = 0; i < epochs; i++)
        {
            Vector dw = w_cost();
            double db = b_cost();
            w = w - (dw * lr);
            b = b - lr * db;
        }
    }

    Vector w_cost() const
    {
        const std::pair<int, int> shape = X.shape();
        Vector sum(shape.second);
        sum.zeros();

        for (int i = 0; i < shape.first; i++)
        {
            Vector row = X.get_row(i);
            double error = predict(row) - y.get(i);
            sum = (row * error) + sum;
        }

        return sum * (1.0f / (float)shape.first);
    }

    double b_cost() const
    {
        const std::pair<int, int> shape = X.shape();
        double sum = 0;
        for (int i = 0; i < shape.first; i++)
            sum += predict(X.get_row(i)) - y.get(i);

        return sum * (1.0f / (float)shape.first);
    }

    double predict(const Vector &x) const
    {
        return x.dot(w) + b;
    }
};