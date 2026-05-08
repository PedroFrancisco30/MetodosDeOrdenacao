#include "benchmark.h"
#include <chrono>

Benchmark::Benchmark(int execucoes) : execucoes_(execucoes) {}

BenchmarkResult Benchmark::executar(Sorter& sorter,
                                     const std::vector<int>& vetor_base,
                                     const std::string& nome,
                                     int entradas) {
    double tempo_total = 0.0;
    long memoria_pico_kb = ((long)vetor_base.size() * sizeof(int) + 1023) / 1024;

    for (int i = 0; i < execucoes_; i++) {
        std::vector<int> copia(vetor_base);

        auto inicio = std::chrono::high_resolution_clock::now();
        sorter.ordenar(copia, 0, (int)copia.size() - 1);
        auto fim = std::chrono::high_resolution_clock::now();

        tempo_total += std::chrono::duration<double>(fim - inicio).count();
    }

    return { entradas, nome, tempo_total / execucoes_, memoria_pico_kb };
}