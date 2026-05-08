#pragma once
#include "sorter.h"
#include <vector>

class MergeSort : public Sorter {
public:
    void ordenar(std::vector<int>& vetor, int inicio, int fim, long& mem_bytes) override;
private:
    void mesclar(std::vector<int>& vetor, int inicio, int meio, int fim, long& mem_bytes);
};