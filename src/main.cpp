#include <vector>
#include <fstream>
#include <string>

#include <ML-CPP/data_import_export/csv.hpp>
#include <ML-CPP/data_import_export/weights.hpp>

#include <ML-CPP/data_structures/vector.hpp>
#include <ML-CPP/data_structures/matrix.hpp>

#include <ML-CPP/algorithms/linear_regression.hpp>
#include <ML-CPP/algorithms/gradient_descent.hpp>

#include <ML-CPP/features/scaling.hpp>
#include <ML-CPP/features/encoding.hpp>

int main()
{
    // Example of using the linear regression algorithm
    // This example is using: https://www.kaggle.com/datasets/abhishek14398/salary-dataset-simple-linear-regression
    // Columns: NRow, YearsExperience, Salary

    auto inp = data_import_export::import_csv("Salary_dataset.csv");
    inp = inp.sub_matrix(1, inp.shape().first, 1, inp.shape().second);

    auto mat = features::encoding::parse(inp, {features::encoding::DataType::NUMERICAL, features::encoding::DataType::NUMERICAL});

    features::MaxAbsScaler f_scaling(mat);

    data_structures::Matrix<double> scaled_mat = f_scaling.scale(mat);

    data_structures::Matrix<double> x = scaled_mat.sub_matrix(0, scaled_mat.shape().first, 0, scaled_mat.shape().second - 1);
    data_structures::Vector<double> y = scaled_mat.get_column(scaled_mat.shape().second - 1);

    algorithms::LinearRegression lr(x, y, 0.001f);

    lr.train();

    lr.print_weights();

    data_import_export::export_weights_and_biases(lr.get_weights(), lr.get_bias());

    data_structures::Vector<double> train(std::vector<double>{3});
    data_structures::Vector<double> scaled_train = f_scaling.scale(train);

    double pred = lr.predict(scaled_train);

    std::cout << "Prediction: " << f_scaling.reverse_scale(pred, 1) << '\n';

    return 0;
}
