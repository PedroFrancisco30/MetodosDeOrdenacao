#pragma once
#include "sorter.h"
#include <vector>
#include <string>

struct BenchmarkResult {
    int entradas;
    std::string nome;
    double media;
};

class Benchmark {
public:
    explicit Benchmark(int execucoes);
    BenchmarkResult executar(Sorter& sorter,
                             const std::vector<int>& vetor_base,
                             const std::string& nome,
                             int entradas);
private:
    int execucoes_;
};