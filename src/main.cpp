#include <vector>
#include <fstream>
#include <string>
#include <ML-CPP/data_importer/import_csv.hpp>
#include <ML-CPP/data_structure/matrix.hpp>
#include <ML-CPP/algorithms/linear_regression.hpp>
#include <ML-CPP/algorithms/feature_scaling.hpp>

int main()
{

    Matrix mat = data_importer::import_csv("Salary_dataset.csv");
    std::cout << std::endl;

    feature_scaling::FeatureScaling f_scaling(mat, feature_scaling::ScalingType::max_abs);

    Matrix scaled_mat = f_scaling.scale(mat);

    Matrix X = scaled_mat.sub_matrix(0, scaled_mat.shape().first, 0, scaled_mat.shape().second - 1);
    Vector y = scaled_mat.get_col(scaled_mat.shape().second - 1);

    LinearRegression lr(X, y, 1000);

    lr.train();

    lr.print_weights();

    Vector train(std::vector<double>{3});
    Vector scaled_train = f_scaling.scale(train);

    double pred = lr.predict(scaled_train);

    std::cout << "Prediction: " << f_scaling.reverse_scale(pred, 1) << std::endl;

    return 0;
}
