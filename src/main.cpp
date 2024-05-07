#include <vector>
#include <fstream>
#include <string>

#include <ML-CPP/data_import_export/csv.hpp>
#include <ML-CPP/data_import_export/weights.hpp>

#include <ML-CPP/data_structures/vector.hpp>
#include <ML-CPP/data_structures/matrix.hpp>

#include <ML-CPP/algorithms/linear_regression.hpp>
#include <ML-CPP/algorithms/gradient_descent.hpp>
#include <ML-CPP/algorithms/gradient_descent.hpp>

#include <ML-CPP/features/scaling.hpp>

int main()
{
    // Example of using the linear regression algorithm: Years of experience, Salary
    // This example is using: https://www.kaggle.com/datasets/abhishek14398/salary-dataset-simple-linear-regression
    data_structures::Matrix mat = data_import_export::import_csv("Salary_dataset.csv");

    features::Scaling f_scaling(mat, features::ScalingType::max_abs);

    data_structures::Matrix scaled_mat = f_scaling.scale(mat);

    data_structures::Matrix X = scaled_mat.sub_matrix(0, scaled_mat.shape().first, 0, scaled_mat.shape().second - 1);
    data_structures::Vector y = scaled_mat.get_col(scaled_mat.shape().second - 1);

    algorithms::LinearRegression lr(X, y, 0.001f, algorithms::stochastic_gd::train);

    lr.train();

    lr.print_weights();

    data_import_export::export_weights_and_biases(lr.get_weights(), lr.get_bias());

    data_structures::Vector train(std::vector<double>{3});
    data_structures::Vector scaled_train = f_scaling.scale(train);

    double pred = lr.predict(scaled_train);

    std::cout << "Prediction: " << f_scaling.reverse_scale(pred, 1) << '\n';

    return 0;
}
