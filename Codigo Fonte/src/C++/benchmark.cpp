#include "benchmark.h"
#include <chrono>

Benchmark::Benchmark(int execucoes) : execucoes_(execucoes) {}

BenchmarkResult Benchmark::executar(Sorter& sorter,
                                    const std::vector<int>& vetor_base,
                                    const std::string& nome,
                                    int entradas) {
    double tempo_total = 0.0;
    for (int i = 0; i < execucoes_; i++) {
        std::vector<int> copia(vetor_base);
        long descartado = 0;
        auto inicio = std::chrono::high_resolution_clock::now();
        sorter.ordenar(copia, 0, (int)copia.size() - 1, descartado);
        auto fim = std::chrono::high_resolution_clock::now();
        tempo_total += std::chrono::duration<double>(fim - inicio).count();
    }

    long mem_bytes = 0;
    {
        std::vector<int> copia(vetor_base);
        sorter.ordenar(copia, 0, (int)copia.size() - 1, mem_bytes);
    }
    double memoria_kb = mem_bytes / 1024.0;

    return { entradas, nome, tempo_total / execucoes_, memoria_kb };
}