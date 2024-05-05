#ifndef FEATURES_ACTIVATIONS_H
#define FEATURES_ACTIVATIONS_H

#include <iostream>
#include <vector>
#include <algorithm>

#include <cmath>

namespace features
{
    namespace activations
    {
        double sigmoid(const double x)
        {
            return 1 / (1 + std::exp(-x));
        }
    }
}

#endif // FEATURES_ACTIVATIONS_H
