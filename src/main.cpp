#include <vector>
#include <fstream>
#include <string>
#include <ML-CPP/data_importer/import_csv.hpp>
#include <ML-CPP/data_structure/matrix.hpp>

int main()
{

    Matrix mat = data_importer::import_csv("Salary_dataset.csv");
    mat.print();

    return 0;
}
