#include "benchmark.h"
#include <chrono>
using namespace std;

Benchmark::Benchmark(int execucoes) : execucoes_(execucoes) {}

BenchmarkResult Benchmark::executar(Sorter& sorter,
                                    const vector<int>& vetor_base,
                                    const string& nome,
                                    int entradas) {
    double total = 0;

    for (int i = 0; i < execucoes_; i++) {
        vector<int> copia = vetor_base;
        auto inicio = chrono::high_resolution_clock::now();
        sorter.ordenar(copia, 0, copia.size() - 1);
        auto fim = chrono::high_resolution_clock::now();
        total += chrono::duration<double>(fim - inicio).count();
    }

    return { entradas, nome, total / execucoes_ };
}