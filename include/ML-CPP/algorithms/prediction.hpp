#ifndef ALG_PREDICTIONS_H
#define ALG_PREDICTIONS_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "../data_structures/matrix.hpp"
#include "../data_structures/vector.hpp"
#include "../features/activations.hpp"

namespace algorithms
{
    namespace static_predictions
    {
        static inline double logistic_predict(const data_structures::Vector &x, const data_structures::Vector &w, double b)
        {
            return features::activations::sigmoid(x.dot(w) + b);
        }

        static inline double linear_predict(const data_structures::Vector &x, const data_structures::Vector &w, double b)
        {
            return x.dot(w) + b;
        }
    }
}
#endif // ALG_PREDICTIONS_H
