#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

#include "../data_structure/matrix.hpp"

namespace data_importer
{
    Matrix import_csv(const std::string &filename)
    {
        std::ifstream inputFile(filename);
        if (!inputFile.is_open())
        {
            std::cerr << "Error opening the file!" << std::endl;
            exit(1);
        }

        std::string line;

        size_t rows = 0;
        size_t cols = 0;
        Matrix matrix(0, 0);

        while (getline(inputFile, line))
        {
            if (line.empty())
                continue;

            std::vector<double> row;
            size_t start_ptr = 0;
            size_t col_length = 0;
            size_t current_cols = 1;
            rows++;

            for (char c : line)
            {
                col_length++;
                if (c == ',')
                {
                    std::string col = line.substr(start_ptr, col_length - 1);
                    row.push_back(std::stod(col));
                    current_cols++;
                    start_ptr += col_length;
                    col_length = 0;
                }
            }

            std::string col = line.substr(start_ptr, col_length);
            row.push_back(std::stof(col));

            std::cout << std::endl;

            cols = std::max(cols, current_cols);
            matrix.add_row(row);
        }

        matrix.set_shape(rows, cols);
        inputFile.close();

        return matrix;
    }
}
