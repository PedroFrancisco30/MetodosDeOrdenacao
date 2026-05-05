#pragma once
#include "sorter.h"

class ParallelMergeSort : public Sorter {
public:
    explicit ParallelMergeSort(int profundidade_max = 1);
    void ordenar(std::vector<int>& vetor, int inicio, int fim) override;

private:
    int profundidade_max_;
    void unir(std::vector<int>& vetor, int inicio, int meio, int fim);
    void executar(std::vector<int>& vetor, int inicio, int fim, int profundidade);
};