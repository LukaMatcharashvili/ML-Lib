#include <vector>
#include <fstream>
#include <string>
#include <ML-CPP/data_importer/import_csv.hpp>
#include <ML-CPP/data_structure/matrix.hpp>
#include <ML-CPP/algorithms/linear_regression.hpp>

int main()
{

    Matrix mat = data_importer::import_csv("Salary_dataset.csv");
    std::cout << std::endl;

    Matrix X = mat.submatrix(0, mat.shape().first, 0, mat.shape().second - 1);
    Vector y = mat.get_col(mat.shape().second - 1);

    LinearRegression lr(X, y, 750000);

    lr.train();

    lr.print_weights();

    double pred = lr.predict(Vector(std::vector<double>{3}));
    std::cout << "Prediction: " << pred << std::endl;

    return 0;
}
