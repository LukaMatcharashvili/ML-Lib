#ifndef DATA_IMP_EXP_WEIGHTS_H
#define DATA_IMP_EXP_WEIGHTS_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

#include "../data_structures/vector.hpp"

namespace data_import_export
{
    void export_weights_and_biases(const std::string &filename, const data_structures::Vector &w, const double b)
    {
        std::ofstream output_file(filename);
        if (!output_file.is_open())
        {
            std::cerr << "Error opening the file!" << std::endl;
            exit(1);
        }

        for (int i = 0; i < w.size(); i++)
            output_file << w.get(i) << ",";

        output_file << "\n";

        output_file << b;
        output_file.close();
    }

    std::pair<data_structures::Vector, double> import_weights_and_biases(const std::string &filename)
    {
        std::ifstream input_file(filename);
        if (!input_file.is_open())
        {
            std::cerr << "Error opening the file!" << std::endl;
            exit(1);
        }

        std::string line;

        std::vector<double> weights;
        std::string bias_str;

        getline(input_file, line);
        size_t start_ptr = 0;

        for (char c : line)
        {
            if (c == ',')
            {
                std::string weight = line.substr(start_ptr, line.find(c));
                weights.push_back(std::stod(weight));
                start_ptr = line.find(c) + 1;
            }
        }

        getline(input_file, bias_str);

        input_file.close();

        return std::make_pair(data_structures::Vector(weights), std::stod(bias_str));
    }
}

#endif // DATA_IMP_EXP_WEIGHTS_H
