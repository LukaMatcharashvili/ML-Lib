#ifndef DATA_IMP_EXP_CSV_H
#define DATA_IMP_EXP_CSV_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

#include "../data_structures/matrix.hpp"

namespace data_import_export
{
    data_structures::Matrix<std::string> import_csv(const std::string &filename)
    {
        std::ifstream input_file(filename);
        if (!input_file.is_open())
        {
            std::cerr << "Error opening the file!" << '\n';
            exit(1);
        }

        std::string line;

        size_t rows = 0;
        size_t cols = 0;
        data_structures::Matrix<std::string> matrix(0, 0);

        while (getline(input_file, line))
        {
            if (line.empty())
                continue;

            std::vector<std::string> row;
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
                    row.push_back(col);
                    current_cols++;
                    start_ptr += col_length;
                    col_length = 0;
                }
            }

            std::string col = line.substr(start_ptr, col_length);
            row.push_back(col);

            cols = std::max(cols, current_cols);
            matrix.add_row(row);
        }

        matrix.set_shape(rows, cols);
        input_file.close();

        return matrix;
    }
}

#endif // DATA_IMP_EXP_CSV_H
