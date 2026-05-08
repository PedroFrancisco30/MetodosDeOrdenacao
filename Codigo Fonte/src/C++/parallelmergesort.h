#pragma once
#include "sorter.h"
#include <vector>

class ParallelMergeSort : public Sorter {
public:
    ParallelMergeSort(int profundidade_max);
    void ordenar(std::vector<int>& vetor, int inicio, int fim, long& mem_bytes) override;
private:
    int profundidade_max_;
    void executar(std::vector<int>& vetor, int inicio, int fim, int profundidade, long& mem_bytes);
    void unir(std::vector<int>& vetor, int inicio, int meio, int fim, long& mem_bytes);
};