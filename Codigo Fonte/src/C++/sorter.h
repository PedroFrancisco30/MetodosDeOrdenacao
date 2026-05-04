#pragma once
#include <vector>

class Sorter {
public:
    virtual void ordenar(std::vector<int>& vetor, int inicio, int fim) = 0;
    virtual ~Sorter() = default;
};