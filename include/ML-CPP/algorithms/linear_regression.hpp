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
    double b = 0;
    double lr;

public:
    LinearRegression(const Matrix &X, const Vector &y, const double lr) : X(X), y(y), w(Vector(X.shape().second)), lr(lr) {}
    LinearRegression(const Matrix &X, const Vector &y) : X(X), y(y), w(Vector(X.shape().second)), lr(0.01) {}

    Vector get_weights() const
    {
        return w;
    }

    double get_bias() const
    {
        return b;
    }

    void print_weights() const
    {
        w.print();
        std::cout << "b: " << b << std::endl;
    }

    void train()
    {
        while (true)
        {
            Vector dw = w_cost();
            double db = b_cost();

            Vector dw_step = dw * lr;
            double db_step = db * lr;

            std::cout << "Step size: " << db << std::endl;

            if (std::abs(db) < 0.001)
                break;

            w = w - dw_step;
            b = b - db_step;
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
            double error = y.get(i) - predict(row);
            sum = (row * -2 * error) + sum;
        }

        return sum;
    }

    double b_cost() const
    {
        const std::pair<int, int> shape = X.shape();
        double sum = 0;
        for (int i = 0; i < shape.first; i++)
            sum += -2 * (y.get(i) - predict(X.get_row(i)));

        return sum;
    }

    double predict(const Vector &x) const
    {
        return x.dot(w) + b;
    }
};