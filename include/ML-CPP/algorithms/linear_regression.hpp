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
    Vector weights;
    size_t epochs;
    double b = 0;
    double lr = 0.01f;

public:
    LinearRegression(const Matrix &X, const Vector &y, const size_t epochs) : X(X), y(y), weights(Vector(y.size())), epochs(epochs) {}

    void train()
    {
        for (size_t i = 0; i < epochs; i++)
        {
            Vector dw = x_cost();
            double db = b_cost();
            Vector lrdw = dw * lr;
            weights = weights - lrdw;
            b = b - lr * db;

            std::cout << "Epoch: " << i << " Cost: " << db << std::endl;
        }
    }

    Vector x_cost() const
    {
        const std::pair<int, int> shape = X.shape();
        Vector sum(shape.second);
        sum.zeros();
        for (int i = 0; i < shape.first; i++)
        {
            Vector row = X.get_row(i);
            double prediction = row.dot(weights);
            double error = prediction - y.get(i);
            Vector v = row * error;
            sum = sum + v;
        }

        return sum;
    }

    double b_cost() const
    {
        const std::pair<int, int> shape = X.shape();
        double sum = 0;
        for (int i = 0; i < shape.first; i++)
        {
            Vector row = X.get_row(i);
            double prediction = row.dot(weights);
            double error = prediction - y.get(i);
            sum += error;
        }

        return (1.0f / (double)shape.first) * sum;
    }

    double predict(const Vector &x) const
    {
        return x.dot(weights);
    }
};