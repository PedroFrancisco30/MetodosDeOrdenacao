#pragma once
#include "sorter.h"

class MergeSort : public Sorter {
public:
    void ordenar(std::vector<int>& vetor, int inicio, int fim) override;
private:
    void mesclar(std::vector<int>& vetor, int inicio, int meio, int fim);
};