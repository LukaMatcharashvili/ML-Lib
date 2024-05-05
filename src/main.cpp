#include <vector>
#include <fstream>
#include <string>
#include <ML-CPP/data_import_export/csv.hpp>
#include <ML-CPP/data_import_export/weights.hpp>
#include <ML-CPP/data_structure/matrix.hpp>
#include <ML-CPP/algorithms/linear_regression.hpp>
#include <ML-CPP/algorithms/feature_scaling.hpp>

int main()
{

    Matrix mat = data_import_export::import_csv("Salary_dataset.csv");

    feature_scaling::FeatureScaling f_scaling(mat, feature_scaling::ScalingType::max_abs);

    Matrix scaled_mat = f_scaling.scale(mat);

    Matrix X = scaled_mat.sub_matrix(0, scaled_mat.shape().first, 0, scaled_mat.shape().second - 1);
    Vector y = scaled_mat.get_col(scaled_mat.shape().second - 1);

    LinearRegression lr(X, y, 0.001f);

    lr.train();

    lr.print_weights();

    data_import_export::export_weights_and_biases("weights", lr.get_weights(), lr.get_bias());

    Vector train(std::vector<double>{3});
    Vector scaled_train = f_scaling.scale(train);

    double pred = lr.predict(scaled_train);

    std::cout << "Prediction: " << f_scaling.reverse_scale(pred, 1) << std::endl;

    return 0;
}
