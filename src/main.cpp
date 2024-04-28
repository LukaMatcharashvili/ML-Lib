#include <vector>
#include <ML-CPP/data_structure/vector.hpp>

int main()
{
    std::vector<float> v1 = {1, 2, 3, 4, 5};
    std::vector<float> v2 = {6, 7, 8, 9, 10};

    Vector vector1(v1);
    Vector vector2(v2);

    Vector result = vector1 + vector2;
    result.print();
    return 0;
}
