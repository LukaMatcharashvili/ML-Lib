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
    const std::string weights_and_biases_file_name = "weights_and_biases";

    void export_weights_and_biases(const data_structures::Vector<double> &w, const double b)
    {
        std::ofstream output_file(weights_and_biases_file_name);
        if (!output_file.is_open())
        {
            std::cerr << "Error opening the file!" << '\n';
            exit(1);
        }

        for (size_t i = 0; i < w.size(); i++)
            output_file << w.get(i) << ",";

        output_file << "\n";

        output_file << b;
        output_file.close();
    }

    std::pair<data_structures::Vector<double>, double> import_weights_and_biases()
    {
        std::ifstream input_file(weights_and_biases_file_name);
        if (!input_file.is_open())
        {
            std::cerr << "Error opening the file!" << '\n';
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

        return std::make_pair(data_structures::Vector<double>(weights), std::stod(bias_str));
    }
}

#endif // DATA_IMP_EXP_WEIGHTS_H
